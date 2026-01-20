# Configuration

Alois configuration should be expressible via:
- CLI args
- environment variables (optional)
- config file (AJIS/JSON/INI – TBD)

Key goals:
- easy to generate configs
- deterministic mode for tests
- explicit sinks and routing

Draft options:
- log level
- sinks list (console,file,memory,sqlite,syslog)
- per-sink options (paths, rotation, batch, tty target)
