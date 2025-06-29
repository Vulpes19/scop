#version 330 core

out vec4 FragColor;
  
in vec3 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

uniform sampler2D texture1;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;
uniform vec3 lightColor;
uniform vec3 lightDir;
uniform vec3 viewPos;
uniform vec3 flatColor;
uniform float blend;
void main()
{
    vec3 textureColor = texture(texture1, TexCoord).rgb;
    vec3 baseColor = mix(flatColor, textureColor, blend);

    vec3 ambient = baseColor * material.ambient;

    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = baseColor * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = baseColor * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;

    //FragColor = vec4(result, 1.0);
    FragColor = vec4(Color, 1.0);
} 