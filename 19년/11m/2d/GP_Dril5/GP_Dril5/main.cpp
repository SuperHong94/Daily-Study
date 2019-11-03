#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm.hpp>
#include <gl/ext.hpp>
#include <gl/gtc/matrix_transform.hpp>
#include <iostream>
#include <Windows.h>
#include "file2buf.h"
#include "InitApp.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid delay();
GLuint ShaderProgram;
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
	CreateCube();
	//CreateCone();
	//InitBuffer();
	InitProgram(ShaderProgram);
	
	glutDisplayFunc(drawScene);
	glutIdleFunc(delay);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(ShaderProgram);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	static float time = 0;
	time +=0.1f;
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, time, glm::vec3(0.0f, 1.0, 0.0f));

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	glutSwapBuffers();
	glFlush();

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}

GLvoid delay()
{
	Sleep(50);
	drawScene();
}