# Viewer (AloisView)

Alois includes (or will include) a viewer that can **read back stored logs**.

## Why a viewer belongs in Alois
- File/sqlite/memory sinks already store data.
- The viewer makes those stores useful: search, filter, export, share.

## Design goals
- Works on low-resource systems (TUI first, optional GUI later).
- Reads from any sink that advertises `READ` or `QUERY`.
- Never requires the host app to link heavy UI dependencies.

## Viewer modes
- **TUI** (primary): curses-like, keyboard-first.
- **CLI**: export, grep-like search, dump JSON/AJIS.
- **GUI** (optional later): only if we decide to.

## Minimal query capabilities (MVP)
- time range (from/to)
- level range (minLevel)
- tag/category filter
- free-text search (if sink supports it; otherwise viewer can do client-side search when it can read raw events)

## Output formats
- formatted text (template rendered)
- structured dump (AJIS / JSON)
- compact “one line per event” (for pipes)

## Relationship to sinks
The viewer does not “open files itself” unless a sink explicitly provides a store interface.
Instead:
- `file` sink provides read implementation (it knows the file format)
- `sqlite` sink provides query implementation
- `memory` sink provides read for live probe/testing
