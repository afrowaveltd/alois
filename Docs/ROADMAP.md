# Roadmap

## Phase 0 (now)
- Repo skeleton + docs + specs
- Decide naming conventions and ABI boundaries
- Agree on canonical config model + AJIS mapping
- Formalize sink capabilities (write/read/query)

## Phase 1 (MVP: logging core)
- Core event model (levels, timestamp, tag, template + properties)
- Sink interface (stable C ABI) + versioning
- Built-in `memory` sink (RW) for tests
- Built-in `apep_console` sink (W) using APEP renderer
- Basic config loader (AJIS) + CLI overrides (`--debug`, `--trace`, `--quiet`)

## Phase 2 (store formats + viewer CLI)
- `file` sink (RW): append-only, simple format, plus reader
- Viewer CLI: list, tail, export, filter (client-side when needed)
- Filters/enrichers MVP (e.g., minLevel, tag allow/deny)

## Phase 3 (database store + richer querying)
- `sqlite` sink (RWQ): structured storage + batch insert
- Viewer query: time range, level, tags, text search (sink-side)

## Phase 4 (platform sinks + optional async)
- `syslog` sink (W) Linux/BSD
- `eventlog` sink (W) Windows (optional build)
- Optional async queue mode (bounded, drop policy, backpressure metrics)

## Phase 5 (polish)
- Rotation policies, compression (optional)
- Plugin sink loading (optional)
- Perf profiling + benchmark suite
