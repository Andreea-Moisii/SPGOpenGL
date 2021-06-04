#version 330 core

out vec4 FragColor;
uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;
uniform sampler2D texture_normal;



struct Light {
    vec3 position;
    
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


#define NR_LIGHTS 20

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

//----------------------- material used if text not set -------------------
uniform float shininess;
//------------------------------------------------------------------------
uniform vec3 viewPos;
uniform Light Lights[NR_LIGHTS];


vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{    
   
    vec3  norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0f);

    for(int i = 0; i < Lights.length(); i++)
            result += CalcLight(Lights[i], norm, FragPos, viewDir);  

    FragColor =  vec4(result,1.f);
}


vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (1 + light.linear * dist + light.quadratic * (dist * dist));    
    vec3 ambient = light.ambient * texture(texture_diffuse, TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(texture_diffuse, TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(texture_specular, TexCoords).rgb;
  
        
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

