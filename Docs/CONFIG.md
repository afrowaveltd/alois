# Configuration

Alois should be configurable via:
- config file (AJIS as the canonical file format in this project)
- CLI args (overrides)
- environment variables (optional later)

## Precedence
1) CLI overrides  
2) Environment overrides (if enabled)  
3) Config file (source of truth)  
4) Defaults

## Goals
- easy to generate configs
- deterministic mode for tests
- explicit sinks and routing
- per-sink options remain namespaced to the sink

## Canonical config model (summary)
- `core`
  - `minLevel`
  - `deterministic`
  - `timestamps` (utc/local/none)
  - `routing` rules (optional in MVP: broadcast-to-all)
- `sinks[]`
  - `id` (unique)
  - `type` (apep_console/file/memory/sqlite/...)
  - `enabled`
  - `minLevel` (optional override per sink)
  - `options` (sink-specific object)

## CLI overrides (examples)
- `--debug`       -> sets `core.minLevel = debug` and enables extra internal diagnostics
- `--trace`       -> sets `core.minLevel = trace`
- `--quiet`       -> sets `core.minLevel = warn`
- `--sink +file`  -> enable sink by id/type
- `--sink -syslog`-> disable sink by id/type

CLI should be able to override without rewriting the config file.
