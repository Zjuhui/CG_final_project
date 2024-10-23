#version 330 core
out vec4 FragColor;

/*
struct Light {
    vec3 color;
};
*/

//uniform Light light;

void main()
{
    //vec3 result = light.color;
    //FragColor = vec4(result,1.0); // set all 4 vector values to 1.0
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
}