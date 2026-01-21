# Spec 0002: Sink Interface (C ABI)

This spec defines the stable ABI surface between Alois core and sinks.

## Goals
- minimal surface
- portable calling conventions
- explicit initialization and shutdown
- fail-soft behavior
- discoverable capabilities (write/read/query)

## Versioning
- Core exposes `alois_core_abi_version()`.
- Sink exposes `alois_sink_abi_version()`.
- Core rejects sinks with incompatible major versions.

## Capabilities
Sinks report a bitmask:

- `ALOIS_SINK_CAP_WRITE`  (0x01)
- `ALOIS_SINK_CAP_READ`   (0x02)
- `ALOIS_SINK_CAP_QUERY`  (0x04)

If a capability is set, the corresponding vtable functions must be non-null.

## Draft vtable (shape)
The sink exposes a struct of function pointers, for example:

- `init(config_blob)`
- `write(event)`
- `flush()`
- `close()`
- optional: `read(iteration_cursor, out_event)`
- optional: `query(query_object, out_iterator)`

The exact signatures are defined in the header once we finalize the event representation.

## Fail-soft rule
No sink function may crash the host.
If an error happens:
- return an error code
- store diagnostics internally (optional)
- core may route sink-failure diagnostics to a dedicated internal sink (optional)
