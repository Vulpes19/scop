#version 330 core
out vec4 FragColor;
  
in vec3 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vec4(vertexColor, 1.0);
} 