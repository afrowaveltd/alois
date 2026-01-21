# Spec 0006: AJIS Config Examples (Draft)

This file shows example configs using the current *test AJIS* style.
The exact syntax may evolve, but the **model** must match Spec 0003.

## Example 1: Minimal (console + memory)
```ajis
core:
  minLevel: "info"
  deterministic: false
  timestamps: "local"
  internalDiagnostics: true

sinks: [
  {
    id: "console"
    type: "apep_console"
    enabled: true
    options: {
      tty: "auto"
      theme: "auto"
    }
  },
  {
    id: "mem"
    type: "memory"
    enabled: true
    options: {
      capacity: 4096
      mode: "ring"
    }
  }
]
```

## Example 2: Add file store + per-sink minLevel
```ajis
core:
  minLevel: "debug"

sinks: [
  { id:"console" type:"apep_console" enabled:true },
  {
    id: "file_main"
    type: "file"
    enabled: true
    minLevel: "info"
    options: {
      path: "./logs/app.alog"
      format: "v1"
      fsync: false
    }
  }
]
```

## CLI override examples
- `--debug` -> core.minLevel=debug + internalDiagnostics=true
- `--sink -console` -> disable sink `console`
- `--sink +file_main` -> enable sink `file_main`
