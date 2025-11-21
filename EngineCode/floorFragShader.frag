#version 330 core
in vec2 TextCoords;

out vec4 FragColor;

uniform sampler2D texture1;


void main () {
	//FragColor = vec4(0.6f, 0.1f, 0.96f,1.0f);
	//FragColor = texture(texture1, TextCoords) * vec4(0.6f, 0.1f, 0.96f,1.0f);
	
	
	
	FragColor = vec4(0.02f, 0.02f, 0.02f,1.0f);
	
}
