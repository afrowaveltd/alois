#ifndef ALOIS_SINK_H
#define ALOIS_SINK_H

#include "alois_types.h"
#include "alois_caps.h"
#include "alois_event.h"
#include "alois_version.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Sink identity + ABI */
    typedef struct alois_sink_info
    {
        alois_u32 abi_version_packed; /* must be ALOIS_ABI_VERSION_PACKED */
        alois_caps caps;              /* capabilities bitmask */
        alois_string_view name;       /* "console", "file", "sqlite", ... */
        alois_string_view vendor;     /* optional */
        alois_u32 flags;              /* reserved */
        alois_u32 _reserved0;
    } alois_sink_info;

    /* Read/query model (cursor-based, optional) */
    typedef struct alois_read_options
    {
        alois_time_ns from_ts_ns; /* inclusive; 0 means no lower bound */
        alois_time_ns to_ts_ns;   /* exclusive; 0 means no upper bound */
        alois_u32 min_level;      /* optional: cast to alois_level; 0 means TRACE */
        alois_u32 max_items;      /* 0 = unlimited */
        alois_u32 _reserved0;
    } alois_read_options;

    /* Query expression (simple for now: string DSL, e.g. "level>=WARN AND category='Auth'") */
    typedef struct alois_query
    {
        alois_string_view expr;
        alois_u32 _reserved0;
        alois_u32 _reserved1;
    } alois_query;

    /* Cursor opaque; methods operate on sink instance */
    struct alois_cursor
    {
        alois_u64 _opaque[4];
    };

    /* Sink vtable */
    typedef struct alois_sink_vtable
    {
        /* lifecycle */
        alois_result (*get_info)(void *sink_ctx, alois_sink_info *out_info);

        alois_result (*open)(void *sink_ctx);  /* optional; may be NULL */
        alois_result (*close)(void *sink_ctx); /* optional; may be NULL */

        /* write path */
        alois_result (*write)(void *sink_ctx, const alois_event *ev);
        alois_result (*flush)(void *sink_ctx); /* optional; may be NULL */

        /* read path (optional if ALOIS_CAP_READ) */
        alois_result (*read_open)(void *sink_ctx, const alois_read_options *opt, alois_cursor *out_cur);                           /* may be NULL */
        alois_result (*read_next)(void *sink_ctx, alois_cursor *cur, alois_event *out_ev, void *scratch, alois_usize scratch_len); /* may be NULL */
        alois_result (*read_close)(void *sink_ctx, alois_cursor *cur);                                                             /* may be NULL */

        /* query path (optional if ALOIS_CAP_QUERY) */
        alois_result (*query_open)(void *sink_ctx, const alois_query *q, const alois_read_options *opt, alois_cursor *out_cur); /* may be NULL */

        /* reserved for ABI extension */
        void *_reserved[8];
    } alois_sink_vtable;

    /* Sink instance (ABI-safe wrapper) */
    struct alois_sink
    {
        const alois_sink_vtable *vtbl;
        void *ctx;
        alois_u64 _reserved[4];
    };

    /* Helper: validate that sink has required functions per caps */
    alois_result alois_sink_validate(const alois_sink *s);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ALOIS_SINK_H */
