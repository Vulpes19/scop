#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D textTexture; // Optional texture (text or button)
uniform vec3 baseColor;        // Fallback flat color
uniform vec3 highlightColor;   // highlight flat color
uniform int button; // button ID
uniform int selectedIndex; // selected button

void main()
{
    vec4 texColor = texture(textTexture, TexCoord);
    vec4 finalColor = mix(vec4(baseColor, 1.0), texColor, 0.5);

    vec4 c = mix(vec4(highlightColor, 1.0), texColor, 0.5);
   
    FragColor = button == selectedIndex ? c : finalColor;
}