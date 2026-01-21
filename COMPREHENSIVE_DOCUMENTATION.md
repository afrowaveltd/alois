# Alois - Complete Documentation

## Obsah
1. [Úvod a vize](#úvod-a-vize)
2. [Architektura](#architektura)
3. [Konfigurace](#konfigurace)
4. [Rozhraní sinků](#rozhraní-sinků)
5. [Model událostí](#model-událostí)
6. [Viewer](#viewer)
7. [Plán vývoje](#plán-vývoje)
8. [Specifikace](#specifikace)

---

## Úvod a vize

Alois je modulární logovací engine postavený kolem inteligentních sinků a strukturovaných log událostí.

### Klíčové principy
- **C-first a přenositelnost**: minimální závislosti, stabilní ABI rozhraní
- **Strukturované události**: vlastnosti jsou prvotřídní, text je pouze pohled
- **Skládání**: uživatel může "postavit logger" z částí
- **Fail-soft**: logování nikdy nesmí shodit hostitelskou aplikaci
- **Pozorovatelnost**: uložené logy mohou být přečteny přes viewer pokud sink podporuje

### Co Alois není
- Profiler nebo crash reporter
- UI framework (viewery jsou samostatné nástroje)

### Vztah k ostatním nástrojům
- **APEP**: konzolový renderer a budoucí UI pro prohlížení logů
- **Probe**: testovací/mockovací prostředí

---

## Architektura

### Přehled
Alois = Jádro + Sinky (+ volitelné Filtry/Obohacovače) + (volitelné Viewer)

- **Jádro** vytváří události, aplikuje filtry/obohacení a směruje do sinků
- **Sinky** zapisují události někam (konzole, soubor, sqlite, syslog, ...)
- Některé sinky umí také **číst** události zpět (viewer/nástroje)
- **Viewer** je klientem *sinků s podporou čtení*

### Odpovědnosti jádra
- Vytváření událostí (časová značka, úroveň, tag, šablona/zpráva, vlastnosti)
- Pipeline filtrů/obohacovačů
- Směrování (které sinky přijímají které události)
- Zásady zpětného tlaku (MVP: synchronní; později: volitelná asynchronní fronta)
- Bezpečnostní politika (nikdy nespadnout; hlásit chyby sinků kontrolovaným způsobem)

### Odpovědnosti sinků
- Implementovat ABI-stabilní rozhraní pro přijímání událostí
- Formátovat/zapisovat nebo ukládat události
- Zpracovávat chyby interně (žádné výjimky unikající hostiteli)
- Poskytovat sémantiku flush/close
- Volitelně poskytovat read/query API pokud sink je také úložiště

### Volitelné odpovědnosti vieweru
- Objevit konfigurované sinky s podporou čtení
- Dotazovat se na časový rozsah / úroveň / tag / fulltextové vyhledávání
- Renderovat pohledy událostí (surové strukturované, formátovaný text, diagnostický pohled)

### Model vláken
- MVP: synchronní dispatch na vlákně volajícího
- Volitelná budoucnost: asynchronní fronta (single worker, omezená fronta)

### ABI hranice
- **Jádro ↔ Sink**: stabilní C ABI (verzované)
- **Jádro ↔ Viewer**: stabilní C API (může znovu použít store/query ABI)

---

## Konfigurace

Alois lze konfigurovat přes:
- Konfigurační soubor (AJIS jako kanonický formát)
- CLI argumenty (přepsání)
- Proměnné prostředí (volitelně později)

### Priorita
1) CLI přepsání
2) Proměnné prostředí (pokud povoleny)
3) Konfigurační soubor (zdroj pravdy)
4) Výchozí hodnoty

### Kanonický konfigurační model

#### core
- `minLevel`: řetězcový enum (`trace|debug|info|warn|error|fatal`)
- `deterministic`: bool (když true: stabilní časové značky/řazení pro testy)
- `timestamps`: enum (`utc|local|none`)
- `internalDiagnostics`: bool (extra chyby o sinkech/konfiguraci)

#### sinks[] (pole)
Každá položka sinku:
- `id`: řetězec (jedinečný, stabilní pro CLI přepsání)
- `type`: řetězec (známý typ sinku)
- `enabled`: bool
- `minLevel`: volitelné přepsání
- `capabilitiesExpected`: volitelná bitová maska (bezpečnost: selhat pokud sink neodpovídá)
- `options`: objekt (specifické pro sink)

#### routing (volitelné)
MVP výchozí: broadcast na všechny povolené sinky.
Budoucnost: pravidla jako:
- podle tagu
- podle úrovně
- podle přítomnosti vlastnosti

### CLI přepsání (příklady)
- `--debug` → nastaví `core.minLevel = debug` a povolí extra interní diagnostiku
- `--trace` → nastaví `core.minLevel = trace`
- `--quiet` → nastaví `core.minLevel = warn`
- `--sink +file` → povolí sink podle id/typu
- `--sink -syslog` → zakáže sink podle id/typu

CLI by měl umět přepsat bez přepsání konfiguračního souboru.

---

## Rozhraní sinků

### Plánované sinky
- `apep_console` (APEP-powered terminal output) — **pouze zápis**
- `file` (append-only; rotace později) — **zápis + čtení**
- `memory` (ring buffer pro testy / live probe) — **zápis + čtení**
- `sqlite` (strukturované ukládání, batch insert) — **zápis + čtení + query**
- `syslog` (Linux/BSD) — **pouze zápis**
- `eventlog` (Windows) — **pouze zápis** (volitelný build)

### Schopnosti sinků
Sink může být:
- **Pouze zápis**: konzole/syslog, atd.
- **Čtení/Ukládání**: soubor/sqlite/memory, atd.
- **Dotazovatelné**: pokročilé dotazování (sql-like) když dostupné

Jádro nesmí hádat. Každý sink reportuje své schopnosti přes bitovou masku.

### Bitová maska schopností
- `ALOIS_SINK_CAP_WRITE` (0x01)
- `ALOIS_SINK_CAP_READ` (0x02)
- `ALOIS_SINK_CAP_QUERY` (0x04)
- `ALOIS_SINK_CAP_RW` (WRITE|READ)

> Pravidlo: pokud sink inzeruje schopnost, příslušné funkční ukazatele musí být non-null.

### Pravidla sinků
- musí být bezpečné při selhání
- nesmí alokovat nadměrně v hot path
- měly by podporovat deterministický režim výstupu když požadováno

---

## Model událostí

### Termíny
- **Událost**: strukturovaný log záznam
- **Sink**: cíl který zapisuje události
- **Store sink**: sink který umí také číst/dotazovat (podpora vieweru)
- **Filter**: rozhoduje zda je událost emitována
- **Enricher**: přidává vlastnosti k událostem

### Úrovně (ordered od nejpodrobnější po nejméně)
`trace`, `debug`, `info`, `warn`, `error`, `fatal`

### Tagy / kategorie
Krátké řetězce jako `NET`, `IO`, `DB`, `AUTH`.

Tag by měly být levné:
- statické ukazatele řetězců když možné
- volitelně internované řetězce

### Identita události
Každá událost má:
- časovou značku
- úroveň
- tag
- šablonu NEBO zprávu
- vlastnosti (klíč/hodnota)
- volitelnou exception-like payload (MVP: řetězec; později: strukturovaná)

### Renderování
Textové renderování je pohled:
- sink rozhoduje jak formátovat, nebo
- jádro může poskytnout "výchozí renderer" (volitelné)

---

## Viewer (AloisView)

### Proč viewer patří do Alois
- Soubor/sqlite/memory sinky již ukládají data
- Viewer dělá tato úložiště užitečnými: vyhledávání, filtrování, export, sdílení

### Designové cíle
- Funguje na nízkopříručových systémech (TUI první, volitelné GUI později)
- Čte z jakéhokoli sinku který inzeruje `READ` nebo `QUERY`
- Nikdy nevyžaduje aby hostitelská aplikace linkovala těžké UI závislosti

### Režimy vieweru
- **TUI** (primární): curses-like, keyboard-first
- **CLI**: export, grep-like search, dump JSON/AJIS
- **GUI** (volitelně později): pouze pokud se rozhodneme

### Minimální schopnosti dotazování (MVP)
- časový rozsah (od/do)
- rozsah úrovní (minLevel)
- filtr tagů/kategorií
- fulltextové vyhledávání (pokud sink podporuje; jinak viewer může dělat client-side)

### Výstupní formáty
- formátovaný text (rendrovaná šablona)
- strukturovaný dump (AJIS / JSON)
- kompaktní "jeden řádek na událost" (pro pipes)

### Vztah k sinkům
Viewer si "neotvírá soubory sám" pokud sink explicitně neposkytuje store rozhraní.
Místo toho:
- `file` sink poskytuje read implementaci (zná formát souboru)
- `sqlite` sink poskytuje query implementaci
- `memory` sink poskytuje read pro živý probe/testování

---

## Plán vývoje

### Fáze 0 (nyní)
- Kostra repo + dokumentace + specifikace
- Rozhodnout naming konvence a ABI hranice
- Dohodnout kanonický konfigurační model + AJIS mapování
- Formalizovat schopnosti sinků (write/read/query)

### Fáze 1 (MVP: logging core)
- Core event model (úrovně, časová značka, tag, šablona + vlastnosti)
- Sink rozhraní (stabilní C ABI) + verzování
- Vestavěný `memory` sink (RW) pro testy
- Vestavěný `apep_console` sink (W) používající APEP renderer
- Základní config loader (AJIS) + CLI přepsání (`--debug`, `--trace`, `--quiet`)

### Fáze 2 (formáty úložiště + viewer CLI)
- `file` sink (RW): append-only, jednoduchý formát, plus reader
- Viewer CLI: list, tail, export, filter (client-side když potřebováno)
- Filtry/obohacovače MVP (např. minLevel, tag allow/deny)

### Fáze 3 (databázové úložiště + bohatší dotazování)
- `sqlite` sink (RWQ): strukturované ukládání + batch insert
- Viewer query: časový rozsah, úroveň, tagy, textové vyhledávání (sink-side)

### Fáze 4 (platformní sinky + volitelný async)
- `syslog` sink (W) Linux/BSD
- `eventlog` sink (W) Windows (volitelný build)
- Volitelný async queue mode (omezená, drop policy, backpressure metriky)

### Fáze 5 (dokončení)
- Rotace politik, komprese (volitelné)
- Plugin sink loading (volitelné)
- Profilování výkonu + benchmark suite

---

## Specifikace

### Spec 0001: Core Concepts
- Definice základních termínů a konceptů

### Spec 0002: Sink Interface (C ABI)
- Stabilní ABI rozhraní mezi jádrem a sinky
- Verzování a schopnosti

### Spec 0003: Configuration Schema
- Kanonický konfigurační model

### Spec 0004: Event Model
- Reprezentace log události v paměti

### Spec 0005: Store Query API
- Jak sink který je také úložiště vystavuje read/query funkcionalitu

### Spec 0006: AJIS Config Examples
- Příklady konfigurací používající AJIS formát

## License
TBD (placeholder)

---
*Tento dokument spojuje a konsoliduje všechny zdroje dokumentace z projektu Alois.*