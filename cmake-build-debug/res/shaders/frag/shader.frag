#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

in vec2 objScaleXY;

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

uniform bool nineSlice;
uniform vec4 uNineBorderUV;

// texelPadUV = 0.5/textureSize along this axis (half-texel in UV units)
float nineSlice1D(float u01, float scaleTiles, float leftW, float rightW, float texelPadUV) {
    float leftTiles  = leftW;
    float rightTiles = rightW;

    float t = u01 * scaleTiles;

    // Left border
    if (t <= leftTiles) {
        float a = (leftTiles <= 0.0) ? 0.0 : (t / leftTiles);
        float u = a * leftW;
        return clamp(u, texelPadUV, 1.0 - texelPadUV);
    }

    // Right border
    if (t >= (scaleTiles - rightTiles)) {
        float a = (rightTiles <= 0.0) ? 0.0 : ((t - (scaleTiles - rightTiles)) / rightTiles);
        float u = (1.0 - rightW) + a * rightW;
        return clamp(u, texelPadUV, 1.0 - texelPadUV);
    }

    // Center (repeat)
    float centerTiles = max(scaleTiles - leftTiles - rightTiles, 0.0);
    float centerW     = max(1.0 - leftW - rightW, 0.0);

    if (centerTiles <= 0.0 || centerW <= 0.0) {
        return clamp(leftW, texelPadUV, 1.0 - texelPadUV);
    }

    float tc = (t - leftTiles);   // [0 .. centerTiles]
    float rep = fract(tc);        // [0 .. 1)

    // Pad away from the edges of the center region to avoid seams.
    float pad = min(texelPadUV, centerW * 0.49);
    float repPadded = (rep * (centerW - 2.0 * pad) + pad) / centerW;

    float u = leftW + repPadded * centerW;
    return clamp(u, texelPadUV, 1.0 - texelPadUV);
}

vec2 nineSliceUV(vec2 uv01, vec2 scaleTiles) {
    vec2 texSize = vec2(textureSize(material.texture_diffuse1, 0));
    vec2 halfTexelUV = 0.5 / texSize;

    float u = nineSlice1D(uv01.x, scaleTiles.x, uNineBorderUV.x, uNineBorderUV.y, halfTexelUV.x);
    float v = nineSlice1D(uv01.y, scaleTiles.y, uNineBorderUV.z, uNineBorderUV.w, halfTexelUV.y);
    return vec2(u, v);
}

vec2 getSampleUV() {
    if(!nineSlice) return TexCoords;
    vec2 s = max(objScaleXY, vec2(1.0));
    return nineSliceUV(TexCoords, s);
}

vec3 calculateDiffuse(Light light, vec3 lightDir, vec3 norm) {
    float diff = max(dot(norm, lightDir), 0.0);
    return light.diffuse * diff * vec3(texture(material.texture_diffuse1, getSampleUV()));
}

vec3 calculateAmbient(Light light) {
    return light.ambient * vec3(texture(material.texture_diffuse1, getSampleUV()));
}

vec3 calculateSpecular(Light light, vec3 lightDir, vec3 norm) {
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    return light.specular * spec * vec3(texture(material.texture_diffuse1, getSampleUV()));
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
//    FragColor = vec4(1, 1.0);
    vec3 output = vec3(0.0);
    for(int i = 0; i < MAX_LIGHTS; i++)
            if(lights[i].type != 0)
                output += calculateLight(lights[i]);
    FragColor = vec4(output, 1.0);
//    FragColor = vec4(fract(TexCoords), 0.0, 1.0);
}