#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
//in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;

//uniform float cvalue;
void main()
{
   // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord),1);
   FragColor = vec4(lightColor * objectColor, 1.0);
}