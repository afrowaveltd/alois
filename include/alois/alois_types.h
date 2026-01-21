#ifndef ALOIS_TYPES_H
#define ALOIS_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* Fixed width types */
    typedef uint8_t alois_u8;
    typedef uint16_t alois_u16;
    typedef uint32_t alois_u32;
    typedef uint64_t alois_u64;

    typedef int8_t alois_i8;
    typedef int16_t alois_i16;
    typedef int32_t alois_i32;
    typedef int64_t alois_i64;

    typedef size_t alois_usize;

    /* Boolean (C-friendly) */
    typedef alois_u8 alois_bool;
#define ALOIS_TRUE ((alois_bool)1u)
#define ALOIS_FALSE ((alois_bool)0u)

    /* Result codes (stable) */
    typedef enum alois_result
    {
        ALOIS_OK = 0,

        /* Generic errors */
        ALOIS_E_UNKNOWN = 1,
        ALOIS_E_INVALID_ARG = 2,
        ALOIS_E_NOT_SUPPORTED = 3,
        ALOIS_E_OUT_OF_MEMORY = 4,
        ALOIS_E_IO = 5,
        ALOIS_E_PARSE = 6,
        ALOIS_E_STATE = 7,

        /* Store/query */
        ALOIS_E_NOT_FOUND = 20,
        ALOIS_E_END = 21,      /* end of iteration/cursor */
        ALOIS_E_TRUNCATED = 22 /* record truncated due to buffer limits */
    } alois_result;

    /* Opaque handles */
    typedef struct alois_sink alois_sink;
    typedef struct alois_logger alois_logger;
    typedef struct alois_cursor alois_cursor;

    /* Time (nanoseconds since Unix epoch by convention; caller may supply) */
    typedef alois_i64 alois_time_ns;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ALOIS_TYPES_H */
