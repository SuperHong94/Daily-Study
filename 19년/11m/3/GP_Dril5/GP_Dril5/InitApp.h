#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "file2buf.h"
#define NUMBER_OF_VERTICES 30
bool InitProgram(unsigned int& ShaderProgram);

bool Check(unsigned int ShaderProgram);
void InitBuffer(GLuint& VAO, GLuint& VBO);
void CreateCube();
void CreateCone();

//
//struct myCicle {
//	float* coordinate;
//	int type;
//	float radius;
//	myCicle(GLuint);
//	void InitBuffer();
//};