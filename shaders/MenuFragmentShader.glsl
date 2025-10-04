#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D textTexture; // Optional texture (text or button)
uniform vec3 baseColor;        // Fallback flat color
uniform vec3 highlightColor;   // highlight flat color
uniform vec3 textHighlightColor;   // highlight text color
uniform int button; // button ID
uniform bool isTitle; // Is Title
uniform int selectedIndex; // selected button

void main()
{
    vec4 texColor = texture(textTexture, TexCoord);
    if (isTitle) {
        FragColor = texColor;
        return ;
    }

    // Button bg color
    vec3 bgColor = baseColor;
    if (button == selectedIndex)
        bgColor = highlightColor;
    
    // Button text color
    vec3 textColor = texColor.rgb;
    if (texColor.a > 0.1)
    {
        if (button == selectedIndex)
            textColor = textHighlightColor;
    }

    vec3 finalRGB = mix(bgColor, textColor, texColor.a);
    FragColor = vec4(finalRGB, 1.0);
}