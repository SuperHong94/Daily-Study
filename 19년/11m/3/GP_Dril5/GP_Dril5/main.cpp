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
GLuint VAO;
GLuint VBO;
float X=0, Y=0;
void Mouse(int button, int state, int x, int y);
void CircleDraw(float x, float y);
struct myCicle {
	float radius;
};
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
	InitBuffer(VAO, VBO);
	InitProgram(ShaderProgram);

	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene);

	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(ShaderProgram);

	CircleDraw(X, Y);


	glutSwapBuffers();


}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		X = (x-390)/390.0f;
		Y = (290-y)/290.0f;
		std::cout << x << ',' << y << std::endl;
		std::cout << "ū" << X << ' ,' << Y << std::endl;
	}

}

void CircleDraw(float x, float y)
{

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, 0));
	glm::mat4 mode1 = glm::mat4(1.0f);
	mode1 = glm::scale(mode1, glm::vec3(0.5f, 0.5f, 0));
	model = model * mode1;

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glPointSize(10);
	glDrawArrays(GL_LINE_LOOP, 0, NUMBER_OF_VERTICES);
	glDisableVertexAttribArray(pos_id);
}