# Sinks

## Planned sinks
- `apep_console` (APEP-powered terminal output) — **write-only**
- `file` (append-only; rotation later) — **write + read**
- `memory` (ring buffer for tests / live probe) — **write + read**
- `sqlite` (structured storage, batch insert) — **write + read + query**
- `syslog` (Linux/BSD) — **write-only**
- `eventlog` (Windows) — **write-only** (optional build)

## Sink capabilities (why we need them)
A sink can be:
- **Write-only**: console/syslog, etc.
- **Read/Store**: file/sqlite/memory, etc.
- **Queryable**: advanced querying (sql-like) when available.

The core must not guess. Each sink reports its capabilities via a bitmask.

### Capability bitmask (draft)
- `ALOIS_SINK_CAP_WRITE`  (0x01)
- `ALOIS_SINK_CAP_READ`   (0x02)
- `ALOIS_SINK_CAP_QUERY`  (0x04)  (read with filtering/search; optional)
- `ALOIS_SINK_CAP_RW`     (WRITE|READ)

> Rule: if a sink advertises a capability, the corresponding function pointers must be non-null.

## Sink rules
- must be safe under failure
- must not allocate excessively in hot path (policy-based)
- should support deterministic output mode when requested
