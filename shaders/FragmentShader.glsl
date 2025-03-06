#version 330 core
out vec4 FragColor;
  
in vec3 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 TexCoord;

uniform sampler2D ourTexture; // built-in data-type for texture objects

void main()
{
    // FragColor = vec4(vertexColor, 1.0);
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // FragColor = texture(ourTexture, TexCoord);
} 