#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TextCoords;
out vec4 FragColor;


struct PointLight {
    vec3 position; 

    float constant; 
    float linear;
    float quadratic;

    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};
#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3; 

//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main () {
	vec4 mixResult = mix(texture(texture1, TextCoords), texture(texture2, TextCoords), 0.50);
	vec4 finalTexture = mix(mixResult,texture(texture3,TextCoords), 0.50);
	FragColor =	finalTexture * vec4(1.0f, 1.0f, 1.0f,1.0f);
	//FragColor =vec4(1.0f, 1.0f, 1.0f,1.0f);
}



