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
#define BAZIERSIZE 100
struct MYVERTEX {
	float x, y, z = 0.0f;
	MYVERTEX(float X, float Y) :x(X), y(Y), z(0.0f) {};
};
struct MYPOINT {
	float x;
	float y;
	float z = 0.0f;
};
extern bool case1;//"위~왼쪽 충돌 \n";
extern bool case2;//"위~오른쪽 충돌 \n";
extern bool case3;//"왼쪽~오른쪽 충돌 \n";
extern bool cutState;
bool InitProgram(unsigned int& ShaderProgram);
bool Check(unsigned int ShaderProgram);

void CreateTriangle(GLuint& triangleVBO);
glm::mat4 Draw_Triangle(GLuint ShaderProgram, GLuint VBO, float x, float y);

bool Crush(float mouseStartX, float mouseStartY, float mouseEndX, float mouseEndY, glm::mat4 triangleVertex, glm::mat2& crushXY);

void DrawPoints(GLuint ShaderProgram,glm::mat2 CrushXY);
bool GetIntersectPoint(const  MYPOINT& AP1, const  MYPOINT& AP2, const MYPOINT& BP1, const MYPOINT& BP2, MYPOINT& IP);


void BezierCurve(MYPOINT* A);
