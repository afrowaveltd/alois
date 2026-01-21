#ifndef ALOIS_DIAG_H
#define ALOIS_DIAG_H

#include "alois_types.h"
#include "alois_string.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Internal diagnostics severity */
    typedef enum alois_diag_level
    {
        ALOIS_DIAG_INFO = 0,
        ALOIS_DIAG_WARN = 1,
        ALOIS_DIAG_ERROR = 2
    } alois_diag_level;

    /* Diagnostics callback for core internals */
    typedef void (*alois_diag_fn)(
        void *user,
        alois_diag_level lvl,
        alois_string_view msg);

    typedef struct alois_diag_sink
    {
        alois_diag_fn fn;
        void *user;
    } alois_diag_sink;

    /* Set global diagnostics sink (optional) */
    alois_result alois_diag_set_sink(const alois_diag_sink *sink);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ALOIS_DIAG_H */
