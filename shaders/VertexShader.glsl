#version 330 core
layout (location = 0) in vec3 aPos;
 // tells OpenGL that the input for that attribute comes from index 0 of the vertex array
// layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

// out vec3 vertexColor; // specify a color output to the fragment shader
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    // vertexColor = aColor; // set the output variable to a dark-red color
    gl_Position = projection * view * model * vec4(aPos, 1.0); // passing vec3 to vec4's constructor
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = aTexCoord;
    // vertexColor = aColor; // set the output variable to a dark-red color
}