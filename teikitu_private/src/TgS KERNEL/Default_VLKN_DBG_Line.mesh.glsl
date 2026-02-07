// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  »Project«   Teikitu Gaming System (TgS) (∂)
//  »File«      Default_VLKN_DBG_Line.mesh.glsl
//  »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//  »Version«   5.22 | »GUID« A1B2C3D4-E5F6-7890-1234-56789ABCDEF0
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
//  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
//  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
//  visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

##extension GL_EXT_mesh_shader : require

#include "Default_VLKN_Common.glsl"

layout(local_size_x = 32, local_size_y = 1, local_size_z = 1) in;
layout(triangles, max_vertices = 128, max_primitives = 64) out;

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Task Payload                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

taskPayloadSharedEXT struct {
    uint m_auiVisible_Line_Indices[64];
    uint m_nuiVisible_Lines;
} payload;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Mesh Shader Outputs                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

layout(location = 0) out vec4 frag_color[];
layout(location = 1) out vec2 line_coord[];


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Buffer Bindings                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

layout(set = 1, binding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__VISIBLE_LINES) readonly buffer _DBG_Line_Visible_Lines {
    DBG_Line                                    m_asVisible_Lines[];
} DBG_Line_Visible_Lines;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Utility Functions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Quad vertices in normalized coordinates */
vec2 quad_positions[4] = vec2[4](
    vec2(-1.0, -1.0), vec2( 1.0, -1.0),
    vec2(-1.0,  1.0), vec2( 1.0,  1.0)
);

vec4 generateLineQuadVertex(DBG_Line line, int vertex_index) {
    vec2 quad_vertex = quad_positions[vertex_index];

    /* Transform line endpoints to clip space */
    vec4 clip_start = vec4(line.m_vStart_Width.xyz, 1.0) * Render_DESC.m_sCamera_Shared.m_avW2S;
    vec4 clip_end = vec4(line.m_vEnd_Width.xyz, 1.0) * Render_DESC.m_sCamera_Shared.m_avW2S;

    /* Convert to screen space for pixel-perfect thickness */
    vec2 screen_start = (clip_start.xy / clip_start.w + 1.0) * 0.5;
    vec2 screen_end = (clip_end.xy / clip_end.w + 1.0) * 0.5;

    /* Calculate line direction and perpendicular in screen space */
    vec2 line_dir = normalize(screen_end - screen_start);
    vec2 perpendicular = vec2(-line_dir.y, line_dir.x);

    /* Calculate line thickness (use per-line thickness or global) */
    float thickness = max(line.m_vStart_Width.w, Render_DESC.m_sDBG_Render_DESC.m_fGlobal_Line_Width);
    thickness *= 0.001; // Convert to screen space units

    /* Generate quad vertex position */
    vec2 position_along_line = mix(screen_start, screen_end, (quad_vertex.x + 1.0) * 0.5);
    vec2 offset_perpendicular = perpendicular * thickness * quad_vertex.y;
    vec2 final_screen_pos = position_along_line + offset_perpendicular;

    /* Convert back to normalized device coordinates */
    vec2 ndc_pos = final_screen_pos * 2.0 - 1.0;

    /* Interpolate depth */
    float depth = mix(clip_start.z, clip_end.z, (quad_vertex.x + 1.0) * 0.5);

    return vec4(ndc_pos, depth, 1.0);
}

vec4 interpolateLineColor(DBG_Line line, vec2 quad_vertex) {
    /* Interpolate color along line */
    float t = (quad_vertex.x + 1.0) * 0.5;
    return mix(line.m_vStart_Colour, line.m_vEnd_Colour, t);
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Main Mesh Shader                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

void main() {
    uint base_line_index = gl_WorkGroupID.x * 32;
    uint lines_in_group = min(32, payload.m_nuiVisible_Lines - base_line_index);

    if (gl_LocalInvocationID.x >= lines_in_group) {
        return;
    }

    uint line_index = payload.m_auiVisible_Line_Indices[base_line_index + gl_LocalInvocationID.x];
    DBG_Line line = DBG_Line_Visible_Lines.m_asVisible_Lines[line_index];

    uint vert_base = gl_LocalInvocationID.x * 4;
    uint prim_base = gl_LocalInvocationID.x * 2;

    for (int i = 0; i < 4; i++) {
        uint vertex_id = vert_base + i;
        gl_MeshVerticesEXT[vertex_id].gl_Position = generateLineQuadVertex(line, i);
        frag_color[vertex_id] = interpolateLineColor(line, quad_positions[i]);
        line_coord[vertex_id] = quad_positions[i];
    }

    gl_PrimitiveTriangleIndicesEXT[prim_base] = uvec3(vert_base + 0, vert_base + 1, vert_base + 2);
    gl_PrimitiveTriangleIndicesEXT[prim_base + 1] = uvec3(vert_base + 1, vert_base + 3, vert_base + 2);

    if (gl_LocalInvocationID.x == 0) {
        SetMeshOutputsEXT(lines_in_group * 4, lines_in_group * 2);
    }
}