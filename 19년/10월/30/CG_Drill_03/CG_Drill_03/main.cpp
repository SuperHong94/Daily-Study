#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include "file2buf.h"
#include "InitApp.h"
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
bool InitProgram();
bool CheckProgram(GLuint program);
GLuint ShaderProgrameID;
GLuint vertexShader;
struct myPos
{
	float x, y, z;
	float r, g, b;
};
myPos Pos[4];
GLuint VBO[2];
GLuint VAO;
GLfloat vertax[]
{
	-0.5f,0.0f, 0.0f,
	0.5f,0.0f,0.0f,
	0.0f,0.5f,0.0f,

	1.0f,0,0,
	1.0f,0,0,
	1.0f,0,0,
};

GLfloat fragment[]
{
	0.25,-0.27,0.5,
	-0.1,-0.25,0.5,
	0.25,0.25,0.5,
};



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	std::cout << sizeof(vertax) << std::endl;

	InitProgram1(ShaderProgrameID);
	InitBuffer();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(ShaderProgrameID);
	static float time = 0;
	time += 0.01f;
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model,time, glm::vec3(0.0f, 0.f, 1.0f));

	unsigned int modelLocation = glGetUniformLocation(ShaderProgrameID, "trans");


	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
	modelLocation = glGetUniformLocation(ShaderProgrameID, "trans");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_POLYGON_MODE, 0, 3);


	glutSwapBuffers();
	glFlush();



}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}
bool CheckProgram(GLuint program)
{
	GLint state;
	glGetProgramiv(program, GL_LINK_STATUS, &state);
	if (GL_FALSE == state) {
		int infologLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);
		if (infologLength > 1) {
			int charsWritten = 0;
			char*infoLog = new char[infologLength];
			glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);
			std::cout << infoLog << std::endl;
			delete[] infoLog;
		}
		return false;
	}
	return true;
}

bool InitProgram()
{







	glGenBuffers(2, VBO); //积己



	const GLchar* vShader = filetobuf("v.glsl");
	const GLchar* fShader = filetobuf("f.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShader, NULL);
	glCompileShader(vertexShader);
	CheckProgram(vertexShader);

	GLuint framentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(framentShader, 1, &fShader, NULL);
	glCompileShader(framentShader);
	CheckProgram(framentShader);

	ShaderProgrameID = glCreateProgram();

	glAttachShader(ShaderProgrameID, vertexShader);
	glAttachShader(ShaderProgrameID, framentShader);

	glBindAttribLocation(ShaderProgrameID, 0, "vPos");
	glBindAttribLocation(ShaderProgrameID, 1, "vColor");

	glLinkProgram(ShaderProgrameID);
	glDeleteShader(vertexShader);
	glDeleteShader(framentShader);
	if (!CheckProgram(ShaderProgrameID))
	{
		glDeleteProgram(ShaderProgrameID);
		std::cout << "救凳123?";
		return false;
	}


	//GLint vID = glGetAttribLocation(ShaderProgrameID, "vPos");
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);  //加己 何咯
	//glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertax, GL_STATIC_DRAW);
	//glVertexAttribPointer(vID, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	//glEnableVertexAttribArray(0);

	//GLint fID = glGetAttribLocation(ShaderProgrameID, "vColor");
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);  //加己 何咯
	//glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), &vertax[9], GL_STATIC_DRAW);
	//glVertexAttribPointer(fID, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),0);
	//glEnableVertexAttribArray(fID);
	//
	const float vertexData[] = {
		0.5, 1.0, 0.0,	 1.0, 0.0, 0.0,
		0.0, 0.0, 0.0,	 0.0, 1.0, 0.0,
		1.0, 0.0, 0.0,	 0.0, 0.0, 1.0 };

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




	return true;
}