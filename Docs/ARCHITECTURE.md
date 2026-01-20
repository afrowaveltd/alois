# Architecture

## Overview
Alois = Core + Sinks (+ optional enrichers/filters).

### Core responsibilities
- Create log events (timestamp, level, tag, template, properties)
- Apply filters and enrichment
- Dispatch events to sinks

### Sink responsibilities
- Format and write events to a target (console/file/db/syslog/…)
- Handle failures internally (no crashing the app)
- Provide flush/close semantics

## Components
- Core engine
- Sink interface (stable ABI surface)
- Built-in sinks (optional)
- Plugin sinks (future / optional)

## Threading
Initial target: synchronous core.
Future: optional async queue with worker thread.
