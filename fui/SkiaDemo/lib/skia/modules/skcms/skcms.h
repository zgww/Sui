/*
 * Minimal skcms.h shim for consuming the prebuilt skia.dll's public headers.
 * skcms is statically linked into skia.dll, but its header was not shipped
 * with this lib distribution. Only the types referenced by public headers
 * (SkColorSpace.h, SkCodec.h, SkEncodedInfo.h) are declared here.
 *
 * Layout note: skcms_ICCProfile must be a complete type because SkCodec holds
 * it by value, but client code never constructs SkCodec (created inside the
 * dll) nor reads these fields, so exact layout is irrelevant to ABI safety.
 */
#ifndef skcms_DEFINED
#define skcms_DEFINED

#include <stdint.h>
#include <stddef.h>

typedef struct {
    float g, a, b, c, d, e, f;
} skcms_TransferFunction;

typedef struct {
    float vals[3][3];
} skcms_Matrix3x3;

typedef enum skcms_AlphaFormat {
    skcms_AlphaFormat_Opaque,
    skcms_AlphaFormat_Unpremul,
    skcms_AlphaFormat_PremulAs8Bit,
    skcms_AlphaFormat_Premul,
} skcms_AlphaFormat;

typedef enum skcms_PixelFormat {
    skcms_PixelFormat_RGBA_8888,
    skcms_PixelFormat_BGRA_8888,
    skcms_PixelFormat_RGBA_1010102,
    skcms_PixelFormat_BGR_1010102,
    skcms_PixelFormat_RGB_888,
    skcms_PixelFormat_BGR_888,
    skcms_PixelFormat_RGBA_16161616,
    skcms_PixelFormat_RGB_16161616,
    skcms_PixelFormat_RGBA_hhh,
    skcms_PixelFormat_RGB_hhh,
    skcms_PixelFormat_RGBA_tf,
    skcms_PixelFormat_RGB_tf,
    skcms_PixelFormat_RGBA_fff,
    skcms_PixelFormat_RGB_fff,
} skcms_PixelFormat;

typedef struct skcms_ICCProfile {
    struct {
        const uint8_t* buffer;
        uint32_t       size;
    } buffer;
    skcms_Matrix3x3        toXYZD50;
    int                    has_trc;
    skcms_TransferFunction trc[3];
    int                    has_toXYZD50;
    int                    has_CICP;
    uint32_t               CICP;
} skcms_ICCProfile;

#endif  // skcms_DEFINED
