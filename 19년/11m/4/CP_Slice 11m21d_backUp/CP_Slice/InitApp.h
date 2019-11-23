#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include <Windows.h>
#include <random>
#include <vector>
#include <cmath>
#include "file2buf.h"
#define NUMBER_OF_VERTICES 30
bool InitProgram(unsigned int& ShaderProgram);
bool Check(unsigned int ShaderProgram);

void CreateTriangle(GLuint& triangleVBO);
void Draw_Triangle(GLuint ShaderProgram, GLuint VBO, float x, float y);