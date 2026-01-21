#ifndef ALOIS_LEVEL_H
#define ALOIS_LEVEL_H

#include "alois_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Log level (Serilog-ish ordering) */
    typedef enum alois_level
    {
        ALOIS_LEVEL_TRACE = 0,
        ALOIS_LEVEL_DEBUG = 1,
        ALOIS_LEVEL_INFO = 2,
        ALOIS_LEVEL_WARN = 3,
        ALOIS_LEVEL_ERROR = 4,
        ALOIS_LEVEL_FATAL = 5
    } alois_level;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ALOIS_LEVEL_H */
