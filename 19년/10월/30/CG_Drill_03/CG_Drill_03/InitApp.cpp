#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include "file2buf.h"
#include "InitApp.h"

bool InitProgram1(unsigned int& ShaderProgrameID)
{
	const GLchar* vShader = filetobuf("v.glsl");
	const GLchar* fShader = filetobuf("f.glsl");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShader, NULL);
	glCompileShader(vertexShader);
	Check(vertexShader);

	GLuint framentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(framentShader, 1, &fShader, NULL);
	glCompileShader(framentShader);
	Check(framentShader);

	ShaderProgrameID = glCreateProgram();

	glAttachShader(ShaderProgrameID, vertexShader);
	glAttachShader(ShaderProgrameID, framentShader);

	glBindAttribLocation(ShaderProgrameID, 0, "vPos");
	glBindAttribLocation(ShaderProgrameID, 1, "vColor");

	glLinkProgram(ShaderProgrameID);
	glDeleteShader(vertexShader);
	glDeleteShader(framentShader);
	if (!Check(ShaderProgrameID))
	{
		glDeleteProgram(ShaderProgrameID);
		std::cout << "안됨123?";
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
		0.0, 0.0, 0.0,	 1.0, 0.0, 0.0, 
		1.0, 0.0, 0.0,	 1.0, 0.0, 0.0 };

	GLuint vertexOBJ;
	GLuint fragmentOBJ;

	/*glGenBuffers(1, &vertexOBJ);
	glBindBuffer(GL_ARRAY_BUFFER, vertexOBJ);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), &vertexData[0]);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &fragmentOBJ);
	glBindBuffer(GL_ARRAY_BUFFER, fragmentOBJ);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), &vertexData[3]);
	glEnableVertexAttribArray(1);*/

	glGenBuffers(1, &vertexOBJ);
	glGenBuffers(1, &fragmentOBJ);
	glBindBuffer(GL_ARRAY_BUFFER, vertexOBJ);  
	glBindBuffer(GL_ARRAY_BUFFER, fragmentOBJ);  //속성 부여
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);  //데이터를 한번에 넣기
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	std::cout << (void*)(3 * sizeof(float)) << std::endl;
	glEnableVertexAttribArray(1);

}

