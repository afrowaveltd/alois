#ifndef ALOIS_CAPS_H
#define ALOIS_CAPS_H

#include "alois_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Sink capabilities bitmask */
    typedef alois_u32 alois_caps;

    enum
    {
        ALOIS_CAP_WRITE = 1u << 0, /* can write events */
        ALOIS_CAP_READ = 1u << 1,  /* can read raw stored events */
        ALOIS_CAP_QUERY = 1u << 2, /* can query/filter server-side */

        /* Optional flags for future expansion */
        ALOIS_CAP_THREADSAFE = 1u << 8, /* sink is internally threadsafe */
        ALOIS_CAP_DURABLE = 1u << 9     /* data persists across restarts */
    };

    static inline alois_bool alois_caps_has(alois_caps caps, alois_caps flag)
    {
        return ((caps & flag) != 0u) ? ALOIS_TRUE : ALOIS_FALSE;
    }

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ALOIS_CAPS_H */
