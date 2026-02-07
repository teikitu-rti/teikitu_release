// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  »Project«   Teikitu Gaming System (TgS) (∂)
//  »File«      Default_VLKN_DBG_Line.task.glsl
//  »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//  »Version«   5.22 | »GUID« A1B2C3D4-E5F6-7890-1234-56789ABCDEF0
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

##extension GL_EXT_shader_explicit_arithmetic_types_int32 : require
##extension GL_EXT_mesh_shader : require

#include "Default_VLKN_Common.glsl"

layout(local_size_x = KTgKN_GPU_VLKN_DBG_LINE__TASK_WORKGROUP_SIZE) in;

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Push Constants                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

layout(push_constant) uniform PushConstants {
    uint m_uiInput_Line_SBO_Offset;
    uint m_nuiTotal_Lines;
} DBG_Line_Push;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Buffer Bindings                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

layout(set = 1, binding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__INPUT_LINES) readonly buffer _DBG_Line_Input_Lines {
    DBG_Line m_asLines[];
} DBG_Line_Input_Lines;

layout(set = 1, binding = KTgMACRO_KN_GPU_VLKN_BINDING_DBG_LINE_SBO__VISIBLE_LINES) writeonly buffer _DBG_Line_Visible_Lines {
    DBG_Line m_asVisible_Lines[];
} DBG_Line_Visible_Lines;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Task Payload                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

taskPayloadSharedEXT struct {
    uint m_auiVisible_Line_Indices[64];
    uint m_nuiVisible_Lines;
} payload;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Shared Memory for Compaction                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

shared uint s_nuiVisible_Count;
shared uint s_auiCompacted_Indices[64];


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Culling Functions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

bool isLineVisible(vec3 start_pos, vec3 end_pos) {
    /* Frustum culling */
    for (int i = 0; i < 6; i++) {
        vec4 plane = Render_DESC.m_sCamera_Shared.m_avFrustum_PN[i];
        float d1 = dot(plane.xyz, start_pos) + plane.w;
        float d2 = dot(plane.xyz, end_pos) + plane.w;
        if (d1 < 0.0 && d2 < 0.0) return false;
    }
    
    /* Degenerate line culling */
    float line_length_sq = dot(end_pos - start_pos, end_pos - start_pos);
    if (line_length_sq < 1e-6) return false;
    
    return true;
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Main Task Shader                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

void main() {
    uint line_index = gl_WorkGroupID.x * 64 + gl_LocalInvocationID.x;
    
    if (gl_LocalInvocationID.x == 0) {
        s_nuiVisible_Count = 0;
    }
    barrier();
    
    /* Cull lines in parallel */
    bool visible = false;
    if (line_index < DBG_Line_Push.m_nuiTotal_Lines) {
        DBG_Line line = DBG_Line_Input_Lines.m_asLines[DBG_Line_Push.m_uiInput_Line_SBO_Offset + line_index];
        visible = isLineVisible(line.m_vStart_Width.xyz, line.m_vEnd_Width.xyz);
    }
    
    /* Compact visible lines using shared memory */
    uint local_index = 0;
    if (visible) {
        local_index = atomicAdd(s_nuiVisible_Count, 1);
        s_auiCompacted_Indices[local_index] = line_index;
    }
    
    barrier();
    
    /* Copy visible lines to output and prepare payload */
    uint visible_count = s_nuiVisible_Count;
    if (gl_LocalInvocationID.x < visible_count) {
        uint src_index = s_auiCompacted_Indices[gl_LocalInvocationID.x];
        uint dst_index = gl_WorkGroupID.x * 64 + gl_LocalInvocationID.x;
        DBG_Line_Visible_Lines.m_asVisible_Lines[DBG_Line_Push.m_uiInput_Line_SBO_Offset + dst_index] = DBG_Line_Input_Lines.m_asLines[DBG_Line_Push.m_uiInput_Line_SBO_Offset + src_index];
        payload.m_auiVisible_Line_Indices[gl_LocalInvocationID.x] = dst_index;
    }
    
    if (gl_LocalInvocationID.x == 0) {
        payload.m_nuiVisible_Lines = visible_count;
        /* Spawn mesh workgroups: 32 lines per mesh workgroup */
        uint mesh_workgroups = (visible_count + 31) / 32;
        EmitMeshTasksEXT(mesh_workgroups, 1, 1);
    }
}
