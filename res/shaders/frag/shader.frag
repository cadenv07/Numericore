#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    sampler2D texture_normal;
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct Light {
    //general
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;

    //point
    float constant;
    float linear;
    float quadratic;

    //spotlight
    float cutOff;
    float outerCutoff;

    int type;
};

#define MAX_LIGHTS 32
uniform Material material;
uniform Light lights[MAX_LIGHTS];
uniform vec3 viewPos;

vec3 calculateDiffuse(Light light, vec3 lightDir, vec3 norm) {
    float diff = max(dot(norm, lightDir), 0.0);
    return light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
}

vec3 calculateAmbient(Light light) {
    return light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
}

vec3 calculateSpecular(Light light, vec3 lightDir, vec3 norm) {
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    return light.specular * spec * vec3(texture(material.texture_diffuse1, TexCoords));
}

vec3 calculateLight(Light light) {
    //directional lighting
    if(light.type == 1) {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(-light.direction);
        vec3 ambient = calculateAmbient(light);
        vec3 diffuse = calculateDiffuse(light,lightDir,norm);
        vec3 specular = calculateSpecular(light,lightDir,norm);
        vec3 lighting = (ambient + diffuse + specular) * light.color;
        return lighting;
    } else

    //point lighting
    if(light.type == 2) {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        float distance = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        vec3 ambient = calculateAmbient(light);
        vec3 diffuse = calculateDiffuse(light,lightDir,norm) * attenuation;
        vec3 specular = calculateSpecular(light,lightDir,norm) * attenuation;
        vec3 lighting = (ambient + diffuse + specular) * light.color;
        return lighting;
    } else

    //Spotlight
    if(light.type == 3) {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        float theta = dot(normalize(FragPos - light.position), normalize(light.direction));
        float epsilon = light.cutOff - light.outerCutoff;
        float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
        float distance = length(FragPos - light.position);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        vec3 ambient = calculateAmbient(light);
        vec3 diffuse = calculateDiffuse(light,lightDir,norm) * intensity;
        vec3 specular = calculateSpecular(light,lightDir,norm) * intensity;
        vec3 lighting = (ambient + diffuse + specular) * light.color;
        return lighting;
    }
}

void main() {
    vec3 output = vec3(0.0);
    for(int i = 0; i < MAX_LIGHTS; i++)
            if(lights[i].type != 0)
                output += calculateLight(lights[i]);
    FragColor = vec4(output, 1.0);
//    FragColor = texture(material.texture_diffuse1, TexCoords);
}