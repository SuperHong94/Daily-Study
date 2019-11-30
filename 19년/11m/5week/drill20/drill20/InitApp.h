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

extern bool Line;

bool InitProgram(unsigned int& ShaderProgram);

bool Check(unsigned int ShaderProgram);
int loadObj(const char* filename);
void Sun(GLuint ShaderProgram);
void Earth1(GLuint ShaderProgram);
void Earth2(GLuint ShaderProgram);
void Earth3(GLuint ShaderProgram);
void view(GLuint shaderProgram);
void Myprojection(GLuint shaderProgram);