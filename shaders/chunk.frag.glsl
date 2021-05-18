#version 440 core

layout (location = 0)in vec2 v_TexCoords;
layout (location = 1)in float v_Lightness;

layout (location = 0)out vec4 f_Color;

layout (binding = 0)uniform sampler2D u_Texture;

void main(){
    f_Color = vec4(texture(u_Texture, v_TexCoords).xyz * (0.9 + v_Lightness * 0.15), 1.0);
}