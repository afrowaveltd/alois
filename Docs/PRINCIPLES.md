# Principles

1. Documentation first (interfaces are promises).
2. Core is small; sinks do the heavy lifting.
3. Structured events first; plain text is a view.
4. Fail-soft: logging must never crash the host app.
5. Determinism is a feature (tests + reproducibility).
6. Portability over cleverness (C-first, minimal dependencies).
7. Optional features stay optional (compile-time + runtime).
8. Config file is **source of truth**, CLI can **override** (without rewriting the file).
