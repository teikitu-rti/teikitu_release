// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  »Project«   Teikitu Gaming System (TgS) (∂)
//  »File«      Default_VLKN_Luminance_Histogram.comp.glsl
//  »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//  »Version«   5.22 | »GUID« A1B2C3D4-E5F6-7890-1234-56789ABCDEF0
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
//  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
//  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
//  visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

##extension GL_EXT_buffer_reference : require
##extension GL_EXT_buffer_reference_uvec2 : require
##extension GL_EXT_shader_explicit_arithmetic_types_int64 : require
##extension GL_EXT_nonuniform_qualifier : require

#include "Default_VLKN_Common.glsl"

layout (local_size_x = 16, local_size_y = 16) in;

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Push Constants                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

layout (push_constant) uniform Params {
    float minLogLuminance;  // e.g. -8.0
    float maxLogLuminance;  // e.g. 4.0
    int numBins;            // typically 256
    uint64_t uiSourceImageView;
} pc;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Buffer Bindings                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

layout (set = 1, binding = KTgMACRO_KN_GPU_VLKN_BINDING_LUMINANCE_HISTOGRAM) buffer Histogram {
    uint hist[256]; // 256 luminance bins
};


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Main Shader                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

shared uint localHist[256]; // Workgroup-local histogram

void main()
{
    // Get image handles from push constants and use them to dynamically index the image arrays
    // The handles are cast to indices into the bindless image arrays
    int sourceImageIndex = int(pc.uiSourceImageView & 0xFFFFFFFF);

    ivec2 size = imageSize(g_image[sourceImageIndex]);
    ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
    if (coord.x >= size.x || coord.y >= size.y)
        return;

    // Initialize local histogram
    for (int i = int(gl_LocalInvocationIndex); i < pc.numBins; i += int(gl_WorkGroupSize.x * gl_WorkGroupSize.y))
        localHist[i] = 0;

    barrier();

    // Load HDR color
    vec3 hdr = imageLoad(g_image[sourceImageIndex], coord).rgb;
    float luminance = dot(hdr, vec3(0.2126, 0.7152, 0.0722));
    luminance = max(luminance, 1e-6);

    // Convert to log space
    float logLum = log2(luminance);
    float binF = (logLum - pc.minLogLuminance) / (pc.maxLogLuminance - pc.minLogLuminance);
    int bin = int(clamp(binF * float(pc.numBins - 1), 0.0, float(pc.numBins - 1)));

    // Accumulate into local histogram
    atomicAdd(localHist[bin], 1u);

    barrier();

    // Merge local into global histogram
    for (int i = int(gl_LocalInvocationIndex); i < pc.numBins; i += int(gl_WorkGroupSize.x * gl_WorkGroupSize.y))
        atomicAdd(hist[i], localHist[i]);
}
