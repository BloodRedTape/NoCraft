#version 440 core

layout (location = 0)in vec2 a_Position;
layout (location = 1)in vec2 a_TexCoords;
layout (location = 2)in float a_TexIndex;

layout(location = 0)out vec2 v_TexCoords;
layout(location = 1)out float v_TexIndex;

void main(){
    gl_Position = vec4(a_Position.xy, -1.0, 1);
    v_TexCoords = a_TexCoords;
    v_TexIndex = a_TexIndex;
}