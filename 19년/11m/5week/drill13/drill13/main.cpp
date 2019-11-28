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
GLuint ConVBO;
GLuint ConEBO;
GLuint VBO;
GLuint EBO;

int SubMenu1, SubMenu2;
float angle = 0;
bool cube = true;
bool con = false;
bool rotate = false;
bool xrotate = false;
bool yrotate = false;
bool centerRotate = false;
bool Line = true;
float globalX = 0;
float globalY = 0;
float globalZ = 0;
void MenuFunc(int button);
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
void move();
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

	glEnable(GL_CULL_FACE);
	int MainMenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("line", 1);
	glutAddMenuEntry("fill", 2);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{

	angle += 0.1f;

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(ShaderProgram);
	view(ShaderProgram);

	Myprojection(ShaderProgram);
	move();
	Sun(ShaderProgram);
	Earth1(ShaderProgram);
	Earth2(ShaderProgram);
	Earth3(ShaderProgram);


	glutSwapBuffers();


}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}


void InputKey(unsigned char key, int x, int y)
{
	static bool culling = false;
	switch (key)
	{
	case 'y':
		if (yrotate)
			yrotate = false;
		else
			yrotate = true;
		break;
	case 'w':
		globalY += 0.1f;

		break;
	case 'a':
		globalX -= 0.1f;
		break;
	case 'd':
		globalX += 0.1f;
		break;
	case 's':
		globalY -= 0.1f;
		break;
	case 'z':
		globalZ += 0.1f;
		break;
	case 'x':
		globalZ -= 0.1f;
		break;
	case 'b':
		if (centerRotate)
			centerRotate = false;
		else
			centerRotate = true;
		break;
	default:
		break;
	}
}


void move()
{
	static float t = 0.0f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	tm = glm::translate(tm, glm::vec3(globalX, globalY, globalZ));
	if (yrotate)
		rm = glm::rotate(rm, glm::radians(t), glm::vec3(0.0f, 1.0f, 0.0f));
	model = rm * tm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "move");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}


void MenuFunc(int button) {
	// button: 메뉴의구별자값
	switch (button) {
	case 1:
		Line = true;
		break;
	case 2:
		Line = false;
		break;
	}
	glutPostRedisplay();
}