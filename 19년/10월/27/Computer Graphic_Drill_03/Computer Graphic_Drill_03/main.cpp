#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include <random>
#include "file2buf.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
const GLchar* vertexsource;
const GLchar* fragmentssource;
GLuint vertexShader, fragmentShader;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLuint complie_shader();
void drawScene();
float r = 1.0f;
float g = 1.0f;
float b = 1.0f;
bool floag = false;
void Mouse(int button, int state, int x, int y);
const float MYSIZE = 0.5;
GLfloat triShape[4][3][3] = {

	{{  MYSIZE*0.5f,  MYSIZE*1.0f, 0.0f  }, // top 
	{  0.0f,  0.0f , 0.0f }, // left 
	{  MYSIZE*1.0f, 0.0 , 0.0 }}, // right ,

	{{  MYSIZE*-0.5f,  MYSIZE*1.0f, 0.0  }, // top 
	{  MYSIZE*-1.0f,  0.0 , 0.0 }, // left 
	{  0.0, 0.0 , 0.0 }}, // right ,

	{{  MYSIZE*-0.5f,  0.0f, 0.0  }, // top 
	{  MYSIZE*-1.0f,  MYSIZE*-1.0f , 0.0 }, // left 
	{  0.0, MYSIZE*-1.0f , 0.0 }}, // right ,

	{{  MYSIZE*0.5f,  0.0, 0.0  }, // top 
	{  0.0,  MYSIZE*-1.0f , 0.0 }, // left 
	{  MYSIZE*1.0f, MYSIZE*-1.0f , 0.0 }}, // right ,
};

enum eAREA {
	one = 0, two, three, four
};
eAREA count = one;
eAREA nowCount = one;
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
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}

GLuint complie_shader()
{
	GLuint vao, vbo[2];
	const GLchar *vertexsource, *fragmentsource;
	GLuint vertexshader, fragmentshader;
	GLuint shaderprogram;

	vertexsource = filetobuf("Vertex Shader.vshader");
	fragmentssource = filetobuf("Fragment Shader.fshader");
	switch (count)
	{
	case one:
		count = two;
		break;
	case two:
		count = three;
		break;
	case three:
		count = four;
		break;
	case four:
		count = one;
		break;
	default:
		break;
	}

	const GLfloat colors[4][3][3] = {


		{{  00.1*(rand() % 25), 0, 0 }, // Red 
		{ 0,  00.1*(rand() % 25),  0 }, // Green
		{  0, 0,  00.1*(rand() % 25)  }}, // Blue

		{ {  00.1*(rand() % 25), 0, 0 }, // Red 
		{ 0,  00.1*(rand() % 25),  0 }, // Green
		{  0, 0,  00.1*(rand() % 25)  }}, // Blue

		{ {  00.1*(rand() % 25), 0, 0 }, // Red 
		{ 0,  00.1*(rand() % 25),  0 }, // Green
		{  0, 0,  00.1*(rand() % 25)  }}, // Blue

		{ {  00.1*(rand() % 25), 0, 0 }, // Red 
		{ 0,  00.1*(rand() % 25),  0 }, // Green
		{  0, 0,  00.1*(rand() % 25)  }} // Blue


	};

	

	glGenVertexArrays(1, &vao);//VAO�� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao); //VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo); //2���� VBO�� �����ϰ� �Ҵ��ϱ�

	//----1��° VBO�� Ȱ���Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ�(��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//���� diamond���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape[count], GL_STATIC_DRAW); //triShape �迭�� ������:9*float

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3*float
	glEnableVertexAttribArray(0); //attribute �ε��� 0���� ����ϰ���

	//--2��° VBO�� Ȱ��ȭ �Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ�(����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors[count], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//���̴� �ڵ带 ���̴� ��ü�� �ֱ�: GL�� ��������.(�ҽ��ڵ�: ���ڿ�)
	glShaderSource(vertexShader, 1, &vertexsource, NULL);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR:vertex shader ������ ����\n" << errorLog << std::endl;
		return false;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentssource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR:fragmentShader ������ ����\n" << errorLog << std::endl;
		return false;
	}
	GLuint ShaderProgramID = glCreateProgram();

	glAttachShader(ShaderProgramID, vertexShader);
	glAttachShader(ShaderProgramID, fragmentShader);
	glLinkProgram(ShaderProgramID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		std::cerr << "EROOR:shader program�������\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(ShaderProgramID);
	return ShaderProgramID;
}

void drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	GLuint ID[4];
	for (int i = 0; i < 4; i++) {
		ID[i] = complie_shader();
		glUseProgram(ID[i]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	glutSwapBuffers();
	glFlush();
}


void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::cout << "x = " << x << "y = " << y << std::endl;
		GLfloat newVertax[3][3] = {
			{x*0.001,(y - 100)*0.001,0},
			{(x - 100)*0.001,y*0.001,0},

		};



		switch (nowCount)
		{
		case one:
			nowCount = two;
			break;
		case two:
			nowCount = three;
			break;
		case three:
			nowCount = four;
			break;
		case four:
			nowCount = one;
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}

}