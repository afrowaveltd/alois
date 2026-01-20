# Alois

Alois is a modular logging engine built around intelligent sinks and structured log events.

> Nobody said a logger has to sound like a logger.
> Around here we ask: “Did you check what Alois saw?”

## What Alois is
- A small, portable logging core (C-first mindset)
- Sink-based routing (console, file, memory, sqlite, syslog, …)
- Structured events (properties, tags, templates)
- Test-friendly and deterministic when needed

## What Alois is not
- Not a profiler
- Not a crash reporter (it can help, but it is not the goal)
- Not a UI framework (viewers are separate tools)

## Relationship to other tools
- **APEP**: a console renderer and future log viewer UI. Alois can use APEP as a sink.
- **Probe**: a test/mocking environment that can capture Alois logs via memory sinks.

## Repository map
- `Docs/` – human docs (vision, principles, architecture)
- `Specs/` – normative specs (stable interfaces, config schema)
- `Src/` – source code (to be added after docs are agreed)
- `Examples/` – example apps and usage
- `Tests/` – test suites (Probe-friendly)
- `Tools/` – helper tools/scripts

## Status
Pre-code phase: documentation first, then the API, then implementation.

## License
TBD (placeholder).
