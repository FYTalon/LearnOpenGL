#version 440 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_specular0;
uniform vec3 viewPos;

void main(){
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse0, TexCoords));

    vec3 norm = normalize(vec3(texture(texture_normal0, TexCoords)));
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse0, TexCoords));

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec3 specular = light.specular * spec * vec3(texture(texture_specular0, TexCoords));

    vec3 result = ambient + diffuse;

    FragColor = vec4(result, 1.0);
}