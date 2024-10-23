#version 330 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertNormal;
layout (location = 2) in vec2 inTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection; 


out vec3 normal; 
out vec3 worldPos; 
out vec2 texCoord; 

void main() {
    gl_Position = projection * view * model * vec4(vertPos, 1.0);
    normal = mat3(transpose(inverse(model))) * vertNormal;
    worldPos = vec3(model * vec4(vertPos, 1.0));
    texCoord = inTexCoord;
}