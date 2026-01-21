# Vision

Alois is a modular logging engine with a **small core** and **powerful sinks**.

Core ideas:
- **C-first** and portable: minimal dependencies, stable ABI boundaries.
- **Structured events**: properties are first-class; text is a view.
- **Composable**: the user can “build the logger” from parts.
- **Fail-soft**: logging must never crash the host application.
- **Observable**: stored logs can be read back via a viewer when a sink supports it.

Alois aims for Serilog-like capability on .NET, without inheriting heavyweight assumptions:
- predictable runtime behavior
- optional features stay optional
- sane defaults, but highly configurable

Non-goals:
- being a full telemetry system (tracing/metrics) on day one
- mandating async/threads (optional later)
