#version 330 core

in vec4 position;

uniform mat4 mvpmatrix;

void main(void) {
	gl_Position = mvpmatrix * position;
}
