# Architecture

## Overview
Alois = Core + Sinks (+ optional Filters/Enrichers) + (optional Viewer).

- **Core** creates events, applies filters/enrichment, and dispatches to sinks.
- **Sinks** write events somewhere (console, file, sqlite, syslog, ...).
- Some sinks may also be able to **read** events back (viewer / tooling).
- **Viewer** is a client of *read-capable sinks* (or a unified store adapter).

## Core responsibilities
- Event creation (timestamp, level, tag, template/message, properties)
- Filter/enricher pipeline
- Routing (which sinks receive which events)
- Backpressure policy (MVP: synchronous; later: optional async queue)
- Safety policy (never crash; report sink failures in a controlled way)

## Sink responsibilities
- Implement an ABI-stable interface to receive events
- Format/write or store events
- Handle failure internally (no exceptions escaping to host)
- Provide flush/close semantics
- Optionally provide read/query APIs if the sink is also a store

## Optional Viewer responsibilities
- Discover configured read-capable sinks
- Query time range / level / tag / free-text search (when supported)
- Render event views (raw structured, formatted text, APEP-like diagnostics view, ...)

## Threading model
- MVP: synchronous dispatch on caller thread.
- Optional future: async queue (single worker, bounded queue, drop policy).

## ABI boundaries
- **Core ↔ Sink**: stable C ABI (versioned).
- **Core ↔ Viewer**: stable C API (can reuse store/query ABI).
