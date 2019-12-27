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




bool InitProgram(unsigned int& ShaderProgram);

bool InitLightProgram(unsigned int& ShaderProgram);
bool Check(unsigned int ShaderProgram);

void CreateAxis(GLuint& Axis);
void CreateCube(GLuint& EBO, GLuint& VBO);
void CreateCon(GLuint& EBO, GLuint& VBO);
void CreateSphere(GLuint& VBO,GLuint& NVBO);

int loadObj(const char* filename, std::vector< glm::vec3 >& outvertex, std::vector< glm::vec3 >& outnormal, std::vector< glm::vec2 >& outuv);

void drawRobot(GLuint EBO, GLuint VBO, GLuint ShaderProgram);
void drawMap(GLuint EBO, GLuint VBO, GLuint ShaderProgram);
void view(GLuint ShaderProgram, float x, float y, float z);
void Myprojection(GLuint shaderProgram);