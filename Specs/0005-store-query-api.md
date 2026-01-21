# Spec 0005: Store Query API (for Viewer)

This spec defines how a sink that is also a store exposes read/query functionality.

## Two levels of support
1) `READ`: sequential iteration (like a cursor)
2) `QUERY`: filtered search handled by the sink

## Minimal query object
- time range: from/to (ns)
- level min/max
- tag allowlist/denylist
- text contains (optional)
- limit / offset (optional)

## Iteration model
- viewer asks sink to create an iterator
- viewer pulls events until exhausted
- sink releases iterator resources

## Client-side fallback
If a sink supports `READ` but not `QUERY`:
- viewer can iterate and apply filters client-side (slower but portable)
