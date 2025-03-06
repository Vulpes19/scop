#version 330 core
layout (location = 0) in vec3 aPos;
 // tells OpenGL that the input for that attribute comes from index 0 of the vertex array
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor; // specify a color output to the fragment shader
out vec2 TexCoord;

void main()
{
    // gl_Position = vec4(aPos, 1.0); // passing vec3 to vec4's constructor
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor; // set the output variable to a dark-red color
    TexCoord = aTexCoord;
}