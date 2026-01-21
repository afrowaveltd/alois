# Spec 0004: Event Model

This spec defines the in-memory representation of a log event and the ABI-safe view passed to sinks.

## Requirements
- Cheap to create (hot path)
- Supports structured properties
- Supports template + rendered message separation
- ABI-safe: explicit lengths; no hidden ownership

## Draft fields
- `timestamp_ns` (int64) OR split fields (seconds + nanos)
- `level` (uint8)
- `tag` (string view)
- `template` (string view, optional)
- `message` (string view, optional)
- `properties` (array of key/value pairs; values are typed union)
- `thread_id` (optional)
- `process_id` (optional)

## Property value types (draft)
- null
- bool
- int64 / uint64
- double
- string view
- bytes view (optional later)

## Ownership
Core owns the event memory for the duration of the `write()` call.
Sinks must copy if they need to persist data asynchronously.

## Deterministic mode
When `core.deterministic=true`:
- timestamp can be provided by the host or a deterministic clock
- ordering rules are explicit for tests
