#version 330 core

layout( location = 0 ) out vec4 FragColor;

in vec3 Position;
in vec2 UV;
in vec3 Normal;


void main () {

	FragColor = vec4(abs(Position), 1.0);
}
