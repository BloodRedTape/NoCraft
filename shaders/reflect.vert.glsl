#version 440 core

layout (location = 0)in vec3 a_Position;
layout (location = 1)in vec2 a_TexCoords;
layout (location = 2)in vec3 a_Normal;

layout (location = 0)out vec2 v_TexCoords;
layout (location = 1)out vec3 v_FragPos;
layout (location = 2)out vec3 v_Normal;

layout (binding = 3)uniform Transforms{
    mat4 u_Projection;
    mat4 u_View;
};

void main(){
    v_FragPos = a_Position;
    gl_Position = u_Projection * u_View * vec4(a_Position.xyz, 1.0);

    v_TexCoords = a_TexCoords;
    v_Normal = a_Normal;
}