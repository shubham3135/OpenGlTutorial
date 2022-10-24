#version 330 core
layout(location=0) in vec3 aPos;
//layout(location=1) in vec3 aColor;
//layout(location=2) in vec2 aTextCoord;
layout(location=1) in vec2 aTextCoord;

//out vec3 ourColor;
out vec2 textCoord;

//uniform mat4 transform; //set in code
uniform mat4 model; //set in code
uniform mat4 view; //set in code
uniform mat4 projection; //set in code

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	//gl_Position = vec4(aPos, 1.0);
	//ourColor = aColor;
	textCoord = aTextCoord;
	
}