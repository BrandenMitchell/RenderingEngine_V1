#version 330 core

layout(location = 0) in vec3 aPos; // input position (x,y)
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTextCoords; 

out vec3 FragPos; //fragments position in world space
out vec3 Normal;
out vec3 LightPos;
out vec2 TextCoords;



//tranformation matrices here
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;





void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) *aNormal;
    LightPos = lightPos;  
    TextCoords = aTextCoords;

    gl_Position = projection * view * model * vec4(aPos, 1.0);

}
