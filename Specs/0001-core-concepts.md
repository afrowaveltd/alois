# Spec 0001: Core Concepts

## Terms
- Event: a structured log record
- Sink: a destination that writes events
- Filter: rules that decide whether an event is emitted
- Enricher: adds properties to events

## Levels
TBD: trace, debug, info, warn, error, fatal

## Tags/Categories
Short strings such as NET, IO, DB, AUTH.
