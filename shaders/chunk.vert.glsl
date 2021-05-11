#version 440

layout (location = 0)in vec3 a_Position;
layout (location = 1)in vec2 a_TexCoords;

layout (location = 0)out vec2 v_TexCoords;

layout (binding = 1)uniform Transforms{
    mat4 u_Projection;
    mat4 u_View;
};

void main(){
    gl_Position = u_Projection * u_View * vec4(a_Position.xyz, 1.0);

    v_TexCoords = a_TexCoords;
}