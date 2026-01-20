# Sinks

## Planned sinks
- `apep_console` (APEP-powered terminal output)
- `file` (append-only + rotation later)
- `memory` (ring buffer for tests / Probe)
- `sqlite` (structured storage, batch insert)
- `syslog` (Linux/BSD)
- `eventlog` (Windows, optional)

## Sink rules
- must be safe under failure
- must not allocate excessively in hot path (policy-based)
- should support deterministic output mode when requested
