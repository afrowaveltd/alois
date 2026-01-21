#ifndef ALOIS_LOGGER_H
#define ALOIS_LOGGER_H

#include "alois_types.h"
#include "alois_sink.h"
#include "alois_level.h"
#include "alois_string.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Logger options */
    typedef struct alois_logger_options
    {
        alois_level min_level;
        alois_u32 max_sinks;    /* 0 = default (e.g., 16) */
        alois_bool enable_diag; /* internal diagnostics on/off */
        alois_u8 _reserved0;
        alois_u16 _reserved1;
        alois_u64 _reserved2[4];
    } alois_logger_options;

    /* Create/destroy */
    alois_result alois_logger_create(const alois_logger_options *opt, alois_logger **out_logger);
    alois_result alois_logger_destroy(alois_logger *logger);

    /* Composition */
    alois_result alois_logger_add_sink(alois_logger *logger, const alois_sink *sink);

    /* Set min level at runtime */
    alois_result alois_logger_set_min_level(alois_logger *logger, alois_level lvl);

    /* Emit event */
    alois_result alois_logger_write(alois_logger *logger, const alois_event *ev);

    /* Convenience: formatted message already built outside, so we just pass views */
    alois_result alois_logger_log(
        alois_logger *logger,
        alois_level level,
        alois_string_view message,
        alois_string_view category,
        const alois_prop *props,
        alois_u32 props_count);

    /* Flush all sinks that support flush */
    alois_result alois_logger_flush(alois_logger *logger);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ALOIS_LOGGER_H */
