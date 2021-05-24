#version 440 core

layout(location = 0)in vec2 v_TexCoords;
layout(location = 1)in float v_TexIndex;

layout(location = 0)out vec4 f_Color;

layout(binding = 0)uniform sampler2D u_Textures[2];

void main(){
    f_Color = texture(u_Textures[int(v_TexIndex)], v_TexCoords);
/*
    if(int(v_TexIndex) == 0)
        f_Color = texture(u_Textures[int(v_TexIndex)], v_TexCoords);
    else
        f_Color = texture(u_Textures[int(v_TexIndex)], vec2(v_TexCoords.x, 1 - v_TexCoords.y));
*/
}