#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos; 
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  //gl_Position = projection * view * model * transform * vec4(aPos.x + xyOffset, aPos.y+ xyOffset, aPos.z+ xyOffset, 1.0); // add the xOffset to the x position of the vertex position
  // ourColor = aColor;
  //Normal = aNormal;
  FragPos = vec3(model * vec4(aPos, 1.0));
  Normal = mat3(transpose(inverse(model))) * aNormal;
  TexCoords = aTexCoords;
  gl_Position = projection * view *  vec4(FragPos, 1.0); // add the xOffset to the x position of the vertex position

}