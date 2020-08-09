#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

//layout (location = 1) in vec3 aColor;
//layout (location = 1) in vec2 aTexCoord;

//out vec3 ourColor;
//out vec2 TexCoord; 

out vec3 FragPos; 
out vec3 Normal;

#if 0
uniform float xyOffset;
uniform mat4 transform;
#endif

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
  //gl_Position = projection * view * model * transform * vec4(aPos.x + xyOffset, aPos.y+ xyOffset, aPos.z+ xyOffset, 1.0); // add the xOffset to the x position of the vertex position
  // ourColor = aColor;
  //TexCoord = aTexCoord;

  FragPos = vec3(model * vec4(aPos, 1.0));
  //Normal = aNormal;
  Normal = mat3(transpose(inverse(model))) * aNormal;
  gl_Position = projection * view * model *  vec4(aPos, 1.0); // add the xOffset to the x position of the vertex position

}