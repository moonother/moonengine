#version 330 core

struct Material 
{
    vec3 ambient;  //定义了环境光照下这个物体反射是什么颜色
    vec3 diffuse;  //定义了漫反射光照下的物体的颜色
    vec3 specular; //定义了镜面光照怼物体的颜色影响
    float shininess; //影响镜面高光的散射&半径
}; 

out vec4 FragColor;

//in vec3 ourColor;
//in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform Material material;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

//uniform float cvalue;
void main()
{
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord),1);
    // ambient
    vec3 ambient = lightColor * material.ambient;//环境光
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);//漫反射

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//镜面高光散射半径
    vec3 specular = lightColor * (spec * material.specular); //镜面光照 
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}