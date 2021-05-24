#version 440 core

layout (location = 0)in vec2 v_TexCoords;
layout (location = 1)in vec3 v_FragPos;
layout (location = 2)in vec3 v_Normal;

layout (location = 0)out vec4 f_Color;

layout (binding = 0)uniform sampler2D u_TextureAtlas;
layout (binding = 1)uniform sampler2D u_ReflectionTexture;

layout (binding = 2)uniform Info{
    vec2 u_WindowSize;
    vec3 u_CameraPosition;
};


void main(){
    vec4 block_color = texture(u_TextureAtlas, v_TexCoords);
    vec4 reflection_color = texture(u_ReflectionTexture, vec2(gl_FragCoord.x/u_WindowSize.x, (u_WindowSize.y - gl_FragCoord.y)/u_WindowSize.y));

    vec3 camera_direction = normalize(u_CameraPosition - v_FragPos);
    float frensel = dot(v_Normal, camera_direction);

    f_Color = vec4(mix(reflection_color, block_color, 0.5).rgb, 0.7);
}