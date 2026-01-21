# Spec 0003: Configuration Schema (Canonical Model)

This spec defines the canonical configuration model.
File formats may vary, but the model stays stable.

## Canonical model

### core
- `minLevel`: string enum (`trace|debug|info|warn|error|fatal`)
- `deterministic`: bool (when true: stable timestamps/ordering options for tests)
- `timestamps`: enum (`utc|local|none`)
- `internalDiagnostics`: bool (extra errors about sinks/config)

### sinks[] (array)
Each sink entry:
- `id`: string (unique, stable for CLI overrides)
- `type`: string (known sink type)
- `enabled`: bool
- `minLevel`: optional override
- `capabilitiesExpected`: optional bitmask (safety: fail if sink doesn't match)
- `options`: object (sink-specific)

### routing (optional)
MVP default: broadcast to all enabled sinks.
Future: rules such as:
- by tag
- by level
- by property presence

## AJIS mapping (initial)
AJIS is the initial canonical file format.
See Spec 0006 for examples.

(TBD: finalize when AJIS test grammar is locked.)
