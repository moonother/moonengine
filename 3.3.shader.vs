#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord; 
uniform float xyOffset;

void main()
{
    gl_Position = vec4(aPos.x + xyOffset, aPos.y+ xyOffset, aPos.z, 1.0); // add the xOffset to the x position of the vertex position
    ourColor = aColor;
    TexCoord = aTexCoord;
}