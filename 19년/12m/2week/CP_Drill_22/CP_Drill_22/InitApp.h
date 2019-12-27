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
#define STB_IMAGE_IMPLEMENTATION


bool InitProgram(unsigned int& ShaderProgram);

bool Check(unsigned int ShaderProgram);

void CreateAxis(GLuint& Axis);
void CreateCube(GLuint ShaderProgram, GLuint& EBO, GLuint& VBO, GLuint& TVBO);
//void CreateCon(GLuint& EBO, GLuint& VBO);
void CreateCon(GLuint& ConEBO, GLuint& ConVBO, GLuint& ConTVBO, GLuint ShaderProgram);
GLvoid draw_cube(GLuint ShaderProgram, GLuint VBO, GLuint EBO, GLuint TVBO, float x);

GLvoid drawCon(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO,GLuint ConTVBO ,float x);
void view(GLuint ShaderProgram, float x, float y, float z);
void Myprojection(GLuint shaderProgram);