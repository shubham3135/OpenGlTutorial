#version 330 core
out vec4 FragColor;

in vec3 ourColor;

void main(){
	//FragColor = vec4(1.0f, 0.3f, 0.4f, 1.0f);
	FragColor = vec4(ourColor, 1.0);
}