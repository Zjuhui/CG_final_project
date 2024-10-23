#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec2 tc;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(binding = 0) uniform sampler2D texture_diffuse1;

void main()
{
    tc = texCoords;    
    gl_Position = projection * view * model * vec4(position, 1.0);
}