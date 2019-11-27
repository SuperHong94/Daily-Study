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
extern bool rotate;
extern float r;
extern bool mysine;
extern bool myspring;
extern bool myzig;
void CreateAxis(GLuint& Axis);
void CreateCube(GLuint& EBO, GLuint& VBO);
void CreateCon(GLuint& EBO, GLuint& VBO);
void drawAxis(GLuint ShaderProgram, GLuint Axis);
void CreateSine(GLuint& Sine);
void drawSine(GLuint ShaderProgram, GLuint Sine);
void drawSpring(GLuint ShaderProgram, GLuint Spring,int size);
int CreateSpring(GLuint& Spring);
void CreateZig(GLuint&Zig);
void drawZig(GLuint ShaderProgram, GLuint Zig);
void CreateTriangle(GLuint& VBO);