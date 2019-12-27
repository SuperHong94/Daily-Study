#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>
#include "file2buf.h"
#include "InitApp.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLuint ShaderProgram;
GLuint LightProgram;
GLuint VBO;
GLuint EBO;
float cameraX = 0.0f, cameraY = 1.0f, cameraZ = 1.0f;
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
bool lightLotate = false;
void main(int argc, char** argv)
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
	CreateCube(EBO, VBO);
	std::cout << EBO << std::endl;
	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{

	
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(ShaderProgram);
	view(ShaderProgram, cameraX, cameraY, cameraZ);
	Myprojection(ShaderProgram);
	drawMap(EBO, VBO,ShaderProgram);
	drawRobot(EBO, VBO, ShaderProgram);


	glutSwapBuffers();


}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}



void InputKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		cameraY += 0.1f;
		break;
	case 'a':
		cameraX -= 0.1f;
		break;
	case 's':
		cameraY -= 0.1f;
		break;
	case 'd':
		cameraX += 0.1f;
		break;
	case 'z':
		cameraZ -= 0.1f;
		break;
	case 'x':
		cameraZ += 0.1f;
		break;
	default:
		break;
	}
}








