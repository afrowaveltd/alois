#ifndef ALOIS_EXPORT_H
#define ALOIS_EXPORT_H

#include "alois_types.h"
#include "alois_sink.h"
#include "alois_string.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef alois_result (*alois_writer_fn)(void *user, const void *data, alois_usize len);

    typedef struct alois_export_options
    {
        alois_read_options read; /* from/to/min_level/max_items */
        alois_query query;       /* optional expr; expr.ptr==NULL => no query */
        alois_u32 flags;         /* reserved */
        alois_u32 _reserved0;
    } alois_export_options;

    /* Export logs from a readable/queryable sink to AJIS text stream */
    alois_result alois_export_logs_ajis(
        const alois_sink *sink,
        const alois_export_options *opt,
        alois_writer_fn writer,
        void *writer_user);

#ifdef __cplusplus
}
#endif

#endif
