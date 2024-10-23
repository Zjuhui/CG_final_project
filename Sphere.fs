#version 330 core

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;

};

out vec4 color;   //FragColor

in vec3 normal;   //Normal
in vec3 worldPos; //FragPos
in vec2 texCoord; //TexCoords

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, texCoord).rgb;
    //diffuse
    vec3 N = normalize(normal);
    vec3 L = normalize(light.position - worldPos);
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = light.diffuse * diff *
        texture(material.diffuse, texCoord).rgb;
    // specular
    vec3 V = normalize(viewPos - worldPos);
    vec3 R = reflect(-L, N);
    float spec = pow(max(dot(V, R), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    // attenuation
    float distance    = length(light.position - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation; 

    vec3 resultColor = ambient + diffuse + specular;
    color = vec4(resultColor, 1.0);
}