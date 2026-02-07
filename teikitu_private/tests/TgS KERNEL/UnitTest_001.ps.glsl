#version 450 core

#include "UnitTest_Common.glsli"

// Input from vertex shader
layout(location = 0) in vec4 colour;

// Output color
layout(location = 0) out vec4 fragColor;

void main()
{
    // This draws a perceptual gradient rather than a linear gradient.
    fragColor = vec4(pow(abs(colour.rgb), vec3(perceptual_exponent)), 1.0);
} 