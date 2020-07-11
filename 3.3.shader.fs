#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture,TexCoord);//使用GLSL内建的texture函数来采样纹理的颜色，它第一个参数是纹理采样器，第二个参数是对应的纹理坐标
   //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);//把纹理颜色与顶点颜色在片段着色器中相乘来混合二者的颜色
}