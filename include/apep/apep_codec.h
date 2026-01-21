#ifndef APEP_CODEC_H
#define APEP_CODEC_H

#include "apep_types.h"
#include "apep_record.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /* Minimal encode/decode interface (you can later expand to your full APEP spec).
       For now Alois only needs "encode one event into bytes" and optionally decode. */

    typedef struct apep_codec
    {
        apep_u32 abi_version_packed;
        apep_u32 flags;
        apep_u64 _reserved[4];
    } apep_codec;

    apep_result apep_codec_init(apep_codec *c);

    /* Encode: caller provides output buffer */
    apep_result apep_encode(
        const apep_codec *c,
        const void *input,    /* typically pointer to alois_event or normalized struct */
        apep_usize input_len, /* or 0 if codec understands the struct */
        void *out_buf,
        apep_usize out_cap,
        apep_usize *out_len);

    /* Decode: optional; can be stubbed in early phase */
    apep_result apep_decode(
        const apep_codec *c,
        const void *in_buf,
        apep_usize in_len,
        void *out_buf,
        apep_usize out_cap,
        apep_usize *out_len);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* APEP_CODEC_H */
