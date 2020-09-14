#version 330 core

struct Material 
{
    vec3 ambient;  //�����˻���������������巴����ʲô��ɫ
    vec3 diffuse;  //����������������µ��������ɫ
    vec3 specular; //�����˾��������������ɫӰ��
    float shininess; //Ӱ�쾵��߹��ɢ��&�뾶
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
    vec3 ambient = lightColor * material.ambient;//������
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);//������

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//����߹�ɢ��뾶
    vec3 specular = lightColor * (spec * material.specular); //������� 
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}