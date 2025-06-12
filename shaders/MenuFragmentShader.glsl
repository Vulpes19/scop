#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D textTexture; // Optional texture (text or button)
uniform vec3 baseColor;        // Fallback flat color
uniform float useTexture;      // 1.0 = use texture, 0.0 = flat color

void main()
{
    vec4 texColor = texture(textTexture, TexCoord);
    vec4 finalColor = mix(vec4(baseColor, 1.0), texColor, useTexture);

    // Optional: alpha check for text
    if (finalColor.a < 0.1)
        discard;

    FragColor = finalColor;
}