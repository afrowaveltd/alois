#ifndef ALOIS_STRING_H
#define ALOIS_STRING_H

#include "alois_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* ABI-safe string view: not necessarily null-terminated */
    typedef struct alois_string_view
    {
        const char *ptr;
        alois_usize len;
    } alois_string_view;

    static inline alois_string_view alois_sv(const char *p, alois_usize n)
    {
        alois_string_view v;
        v.ptr = p;
        v.len = n;
        return v;
    }

    static inline alois_bool alois_sv_is_null(alois_string_view v)
    {
        return (v.ptr == NULL) ? ALOIS_TRUE : ALOIS_FALSE;
    }

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ALOIS_STRING_H */
