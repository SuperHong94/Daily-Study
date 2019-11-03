#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include "file2buf.h"
#include "InitApp.h"

bool InitProgram(unsigned int& ShaderProgram)
{
	const char* vertexSource = filetobuf("Vertex.glsl");
	const char* fragmentSource = filetobuf("Fragment.glsl");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	if (!Check(vertexShader)) return false;

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	if (!Check(fragmentShader)) return false;

	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (!Check(ShaderProgram)) {
		glDeleteProgram(ShaderProgram);
		return false;

	}
	return true;

}
bool Check(unsigned int ShaderProgram)
{
	GLint state;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &state);
	if (state == GL_FALSE) {
		int infologLength = 0;
		glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &infologLength);
		if (infologLength > 0) {
			char* infolog = new char[infologLength];
			glGetProgramInfoLog(ShaderProgram, infologLength, NULL, infolog);
			std::cout << infolog << std::endl;
			delete[] infolog;
		}
		return false;
	}


	return true;
}

void InitBuffer()
{
	const float vertexData[] = {
		0.5, 1.0, 0.0,	 1.0, 0.0, 0.0,
		0.0, 0.0, 0.0,	 0.0, 1.0, 0.0,
		1.0, 0.0, 0.0,	 0.0, 0.0, 1.0 };

	GLuint vertexOBJ;
	GLuint fragmentOBJ;

	//glGenBuffers(1, &vertexOBJ);

	//glBindBuffer(GL_ARRAY_BUFFER, vertexOBJ);
	//glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &vertexData[0], GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//glEnableVertexAttribArray(0);

	//
	//glBindBuffer(GL_ARRAY_BUFFER, fragmentOBJ);
	//glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &vertexData[3], GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//glEnableVertexAttribArray(1);
	glGenBuffers(1, &vertexOBJ);
	glGenBuffers(1, &fragmentOBJ);
	glBindBuffer(GL_ARRAY_BUFFER, vertexOBJ);
	glBindBuffer(GL_ARRAY_BUFFER, fragmentOBJ);  //속성 부여
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);  //데이터를 한번에 넣기
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치


	glEnableVertexAttribArray(1);
}


void CreateCone()
{
	GLfloat vertex[] = {
		0.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.5f, 1.0f,
		0.5f, -0.5f, -0.5f,	0.5f, 0.5f, 1.0f
	};
	
	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	GLint gIndices[]
	{
		1,3,2,
		2,3,4,

		0,1,2,
		0,3,1,

		0,3,4,
		0,2,4,

	};

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gIndices), &gIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치


	glEnableVertexAttribArray(1);


}
void CreateCube()
{

	GLfloat vertex[] = {
		-0.5f, 0.5f, 0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,	0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f,	0.0f, 1.0f, 0.0f,

		0.5f, -0.5f, 0.5f,	0.0f, 1.0f, 0.5f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.5f, 1.0f,
		-0.5f, 0.5f, -0.5f,	1.0f, 0.0f, 1.0f,

		0.5f, 0.5f, -0.5f,	0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.1f
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	//front
	GLint gIndices[]
	{
		0,1,2,
		2,1,3,

		0,5,4,
		0,4,1,

		5,6,7,
		5,7,4,

		2,6,7,
		2,7,3,

		0,2,5,
		2,6,5,

		1,4,7,
		1,7,3
	};

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gIndices), &gIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치


	glEnableVertexAttribArray(1);


}