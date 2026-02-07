#version 450 core

#include "UnitTest_Common.glsli"

// Input vertex attributes
layout(location = 0) in vec3 m_vS0;
layout(location = 1) in vec4 m_vCL;

// Output to fragment shader
layout(location = 0) out vec4 colour;

void main()
{
    gl_Position = vec4(m_vS0, 1.0);
    colour = m_vCL;
} 