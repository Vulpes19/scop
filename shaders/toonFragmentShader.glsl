#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightDir;  // Should be normalized and in world space
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    float intensity = max(dot(normalize(Normal), normalize(-lightDir)), 0.0);

    // Quantize the light intensity
    float levels = 4.0;
    float quantized = floor(intensity * levels) / levels;

    vec3 color = quantized * lightColor * objectColor;
    FragColor = vec4(color, 1.0);
}
