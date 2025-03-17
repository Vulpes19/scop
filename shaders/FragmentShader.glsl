#version 330 core
out vec4 FragColor;
  
in vec3 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 TexCoord;

uniform sampler2D texture1; // built-in data-type for texture objects
uniform sampler2D texture2;

void main()
{
    // FragColor = vec4(vertexColor, 1.0);
    // FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
} 