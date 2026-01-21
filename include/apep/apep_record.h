#ifndef APEP_RECORD_H
#define APEP_RECORD_H

#include "apep_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* APEP record is transport-neutral; console sink is just one renderer.
       Keep it as a flat envelope + payload bytes. */

    typedef struct apep_record_view
    {
        const void *data;
        apep_usize len;
    } apep_record_view;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APEP_RECORD_H */
