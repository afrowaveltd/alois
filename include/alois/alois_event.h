#ifndef ALOIS_EVENT_H
#define ALOIS_EVENT_H

#include "alois_types.h"
#include "alois_string.h"
#include "alois_level.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Property types (kept minimal + ABI-safe) */
    typedef enum alois_prop_type
    {
        ALOIS_PROP_NULL = 0,
        ALOIS_PROP_BOOL = 1,
        ALOIS_PROP_I64 = 2,
        ALOIS_PROP_U64 = 3,
        ALOIS_PROP_F64 = 4,
        ALOIS_PROP_STR = 5
    } alois_prop_type;

    typedef struct alois_prop
    {
        alois_string_view key;
        alois_prop_type type;
        alois_u32 _reserved0;

        union
        {
            alois_bool b;
            alois_i64 i64;
            alois_u64 u64;
            double f64;
            alois_string_view str;
        } value;
    } alois_prop;

    /* Event payload */
    typedef struct alois_event
    {
        /* basic envelope */
        alois_time_ns ts_ns; /* timestamp */
        alois_level level;   /* severity */
        alois_u8 flags;      /* reserved for future (e.g., sampled, etc.) */
        alois_u16 _reserved0;

        /* message and context */
        alois_string_view message;        /* message text (already formatted or template-resolved) */
        alois_string_view category;       /* optional category/source (logger name) */
        alois_string_view correlation_id; /* optional trace/span/req id */

        /* structured props (owned by caller for duration of call) */
        const alois_prop *props;
        alois_u32 props_count;

        /* optional binary blob pointer (for later; can be NULL now) */
        const void *blob;
        alois_u32 blob_len;

        /* reserved for ABI growth */
        alois_u64 _reserved1[2];
    } alois_event;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ALOIS_EVENT_H */
