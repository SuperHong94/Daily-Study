#pragma once
#include "global.h"

struct myRectangle {
	GLuint VBO;
	GLuint EBO;

	void CreateRectangle(GLuint ShaderProgram);
	void draw(GLuint ShaderProgram, float x, float y, float z);
	void lightDraw(GLuint shaderProgram, float x, float y, float z);
};