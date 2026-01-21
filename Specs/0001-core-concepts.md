# Spec 0001: Core Concepts

## Terms
- **Event**: a structured log record.
- **Sink**: a destination that writes events.
- **Store sink**: a sink that can also read/query (viewer support).
- **Filter**: decides whether an event is emitted.
- **Enricher**: adds properties to events.

## Levels (draft)
Ordered from most verbose to least:
`trace`, `debug`, `info`, `warn`, `error`, `fatal`.

## Tags / categories
Short strings such as `NET`, `IO`, `DB`, `AUTH`.

Tags should be cheap:
- static string pointers when possible
- optionally interned strings

## Event identity
Each event should have:
- timestamp
- level
- tag
- template OR message
- properties (key/value)
- optional exception-like payload (MVP: string; later: structured)

## Rendering
Text rendering is a view:
- sink decides how to format, or
- core can provide a “default renderer” (optional).
