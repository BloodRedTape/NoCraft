#version 440 core

layout (location = 0)in vec2 v_TexCoords;

layout (location = 0)out vec4 f_Color;

layout (binding = 0)uniform sampler2D u_Texture;

void main(){
    f_Color = texture(u_Texture, v_TexCoords);
}