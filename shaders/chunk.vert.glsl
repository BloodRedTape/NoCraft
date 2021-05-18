#version 440

layout (location = 0)in vec3 a_Position;
layout (location = 1)in vec2 a_TexCoords;
layout (location = 2)in vec3 a_Normal;

layout (location = 0)out vec2 v_TexCoords;
layout (location = 1)out float v_Lightness;

layout (binding = 1)uniform Transforms{
    mat4 u_Projection;
    mat4 u_View;
};

vec3 s_SunPos = vec3(200, 400, 300);

void main(){
    gl_Position = u_Projection * u_View * vec4(a_Position.xyz, 1.0);

    v_TexCoords = a_TexCoords;
    v_Lightness = dot(normalize(s_SunPos), a_Normal);
}