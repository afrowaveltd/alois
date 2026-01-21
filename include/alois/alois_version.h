#ifndef ALOIS_VERSION_H
#define ALOIS_VERSION_H

/* Public ABI versioning for Alois */

#define ALOIS_ABI_VERSION_MAJOR 1u
#define ALOIS_ABI_VERSION_MINOR 0u
#define ALOIS_ABI_VERSION_PATCH 0u

/* Numeric packing: 0xMMmmpp (8 bits each) */
#define ALOIS_ABI_VERSION_PACKED \
    ((ALOIS_ABI_VERSION_MAJOR << 16u) | (ALOIS_ABI_VERSION_MINOR << 8u) | (ALOIS_ABI_VERSION_PATCH))

/* Optional library build info (can be defined by build system) */
#ifndef ALOIS_LIB_NAME
#define ALOIS_LIB_NAME "alois"
#endif

#ifndef ALOIS_LIB_VERSION_STR
#define ALOIS_LIB_VERSION_STR "1.0.0"
#endif

#endif /* ALOIS_VERSION_H */
