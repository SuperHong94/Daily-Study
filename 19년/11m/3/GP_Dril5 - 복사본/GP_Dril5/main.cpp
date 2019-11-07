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
GLvoid delay();
GLuint ShaderProgram;
GLuint VAO;
Mytrans model[10];
unsigned int modelLocation;
void Mouse(int button, int state, int x, int y);
void main(int argc, char** argv)
{
	srand(time(NULL));
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
	InitBuffer(VAO);
	InitProgram(ShaderProgram);


	glutDisplayFunc(drawScene);
	glutIdleFunc(delay);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(ShaderProgram);
	glBindVertexArray(VAO);

	//for (int i = 0; i < 10; i++) {
	//	
	//	modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model->model[i]));
	//	glDrawArrays(GL_TRIANGLES, 0, 3);

	//}
	modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model[5].model));
	glDrawArrays(GL_TRIANGLES, 0, 3);

	modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model[2].model));
	glDrawArrays(GL_TRIANGLES, 0, 3);

	modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model[0].model));
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}

GLvoid delay()
{
	std::cout << "delay" << std::endl;
	Sleep(500);
	for (int i = 0; i < 10; i++) {
		switch (model[i].dir)
		{
		case left:
			if (model[i].speed < -0.9f)
				model[i].dir = right;
			model[i].model = glm::translate(model[i].model, glm::vec3(model[i].x+model[i].speed--, 0.2f, 0));
			break;
		case right:
			model[i].model = glm::translate(model[i].model, glm::vec3(model[i].x + model[i].speed++, 0.2f, 0));
			break;
		case up:

			model[i].model = glm::translate(model[i].model, glm::vec3(0, model[i].speed++, 0));
			break;
		case down:
			model[i].model = glm::translate(model[i].model, glm::vec3(0, model[i].speed--, 0));
			break;
		default:
			break;
		}
	}
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{

}