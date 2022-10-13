#version 330 core
out vec4 FragColor;

in vec4 color;

void main(){
	//FragColor = vec4(1.0f, 0.3f, 0.4f, 1.0f);
	FragColor = color;
}