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
#include <random>
#include "file2buf.h"
#define NUMBER_OF_VERTICES 30
bool InitProgram(unsigned int& ShaderProgram);

bool Check(unsigned int ShaderProgram);
void InitBuffer(GLuint& VAO);
enum EDIRECTION {
	left = 0, right, up, down
};
//struct MYtriangle {
//	float x, y, r, g, b;
//
//	GLfloat* vertexData;
//	float size = 0.25f;
//	EDIRECTION dir;
//	GLuint VAO;
//	MYtriangle()
//	{
//		srand(time(NULL));
//
//		x = ((rand() % 14) - 7)*0.01;
//		y = ((rand() % 14) - 7)*0.01;
//		r = (rand() % 100)*0.01;
//		g = (rand() % 100)*0.01;
//		b = (rand() % 100)*0.01;
//		dir = (EDIRECTION)(rand() % 4);
//
//
//		vertexData = new float[18]{
//			x, size + y, r, g, b,
//				(-size / 2) + x, y, 0, r, g, b,
//				size + x, y, 0, r, g, b,
//		};
//
//	}
//	void mInitBuffer()
//	{
//		glGenVertexArrays(1, &VAO);
//		glBindVertexArray(VAO);
//		GLuint VBO[2];
//		glGenBuffers(2, VBO);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
//		glEnableVertexAttribArray(0);
//
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//		glEnableVertexAttribArray(1);
//	}
//	void draw()
//	{
//		
//	}
//	void Update();
//	~MYtriangle() {
//		std::cout << "¼Ò¸ê" << std::endl;
//		delete[] vertexData;
//	}
//};

struct Mytrans
{
	float x;
	float y;
	float speed = 0.01;
	glm::mat4 model = glm::mat4(1.0f);
	EDIRECTION dir;
	Mytrans()
	{
		srand(time(NULL));
		this->dir = (EDIRECTION)(rand() % 4);
		this->x = (rand() % 50)*0.01;
		this->y = (rand() % 50)*0.01;

		std::cout << dir << std::endl;
	}
};