﻿#version 330 core

out vec4 FragColor;


struct Material 
{
    //vec3 ambient;  //定义了环境光照下这个物体反射是什么颜色
    sampler2D diffuse;  //定义了漫反射光照下的物体的颜色
    sampler2D specular; //定义了镜面光照怼物体的颜色影响
    float shininess; //影响镜面高光的散射&半径
}; 

struct DirLight {//定向光
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  


struct PointLight {//点光源
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  



struct SpotLight{//聚光

vec3 position;
vec3 direction;
float cutOff;
float outerCutOff;
  
float constant;
float linear;
float quadratic;
  
vec3 ambient;
vec3 diffuse;
vec3 specular;

};
#define NR_POINT_LIGHTS 4


//in vec3 ourColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform Material material;
uniform vec3 viewPos;
uniform SpotLight spotLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;
//uniform vec3 lightPos;
//uniform vec3 objectColor;
//uniform vec3 lightColor;


//uniform float cvalue;
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                 light.quadratic * (distance * distance));    
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // 聚光强度
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main()
{
#if 0
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord),1);
    // ambient
    //vec3 ambient = light.ambient * material.ambient;//环境光
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;//加了贴图的环境光
  
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    //vec3 lightDir = normalize(-light.direction);//平行光
    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * (diff * material.diffuse);//漫反射
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;//加了贴图的漫反射光   为什么不加.rgb会出现vec4转vec3错误？

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//镜面高光散射半径
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb; //只使用了金属的镜面光照 
    
    //计算θ值，并将它和切光角ϕ对比，来决定是否在聚光的内部
    float theta = dot(lightDir, normalize(-light.direction));

    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);  

    diffuse  *= intensity;
    specular *= intensity;

    float distance    = length(light.position - FragPos);//此两式为计算物体距离光源的距离并且根据距离给出一个衰减值
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient  *= attenuation; //将环境光、漫反射和镜面光乘衰减值
    diffuse  *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
#endif

    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}