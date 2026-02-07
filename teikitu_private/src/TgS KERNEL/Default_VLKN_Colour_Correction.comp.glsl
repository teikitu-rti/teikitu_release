// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  »Project«   Teikitu Gaming System (TgS) (∂)
//  »File«      Default_VLKN_Colour_Correction.comp.glsl
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

// Push constants: image view handles passed from C code for dynamic indexing
layout (push_constant) uniform PushConstants {
    uint64_t uiSourceImageView;
    uint64_t uiDestinationImageView;
    uint bHDR_Enabled;
    float fGamma;
    float fExposure;
    uint enTone_Map_Type;
} push_data;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Main Shader                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

vec3 ToneMap_Reinhard(vec3 colour)
{
    return colour / (colour + vec3(1.0));
}

vec3 ToneMap_ACES(vec3 colour)
{
    // Simplified ACES approximation by Krzysztof Narkowicz (2015)
    // see: "ACES Filmic Tone Mapping Curve"
    const float a = 2.51;
    const float b = 0.03;
    const float c = 2.43;
    const float d = 0.59;
    const float e = 0.14;
    return clamp((colour * (a * colour + b)) / (colour * (c * colour + d) + e), 0.0, 1.0);
}

// --- Main compute kernel ---
void main()
{
    ivec2 coord = ivec2(gl_GlobalInvocationID.xy);

    // Get image handles from push constants and use them to dynamically index the image arrays
    // The handles are cast to indices into the bindless image arrays
    int sourceImageIndex = int(push_data.uiSourceImageView & 0xFFFFFFFF);
    int destImageIndex = int(push_data.uiDestinationImageView & 0xFFFFFFFF);

    // CRITICAL: Validate destination image dimensions to prevent out-of-bounds writes
    ivec2 destSize = imageSize(g_image[destImageIndex]);
    if (coord.x >= destSize.x || coord.y >= destSize.y)
    {
        return; // Early exit for out-of-bounds threads
    }

    // CRITICAL: Validate source image dimensions to prevent out-of-bounds reads
    ivec2 sourceSize = imageSize(g_image[sourceImageIndex]);
    if (coord.x >= sourceSize.x || coord.y >= sourceSize.y)
    {
        // Fallback: write black if source coordinate is out of bounds
        imageStore(g_image[destImageIndex], coord, vec4(0.0, 0.0, 0.0, 1.0));
        return;
    }

    // Load HDR colour from read-only array
    vec4 hdrColour = imageLoad(g_image[sourceImageIndex], coord);

    // Apply colour correction for display output
    vec3 colour = HDRCorrection(hdrColour.rgb);

    // Clamp to valid range and write to destination
    vec4 finalColour = vec4(colour, hdrColour.a);
    imageStore(g_image[destImageIndex], coord, finalColour);
}
