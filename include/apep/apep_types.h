#ifndef APEP_TYPES_H
#define APEP_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef uint8_t apep_u8;
    typedef uint16_t apep_u16;
    typedef uint32_t apep_u32;
    typedef uint64_t apep_u64;

    typedef int8_t apep_i8;
    typedef int16_t apep_i16;
    typedef int32_t apep_i32;
    typedef int64_t apep_i64;

    typedef size_t apep_usize;

    typedef apep_u8 apep_bool;
#define APEP_TRUE ((apep_bool)1u)
#define APEP_FALSE ((apep_bool)0u)

    typedef enum apep_result
    {
        APEP_OK = 0,
        APEP_E_INVALID_ARG = 1,
        APEP_E_IO = 2,
        APEP_E_OVERFLOW = 3,
        APEP_E_PARSE = 4
    } apep_result;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APEP_TYPES_H */
