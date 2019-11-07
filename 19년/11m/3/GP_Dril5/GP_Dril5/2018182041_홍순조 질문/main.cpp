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
GLuint VBO;
void Mouse(int button, int state, int x, int y);

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
	InitBuffer(VAO,VBO);
	InitProgram(ShaderProgram);
	
	
	glutDisplayFunc(drawScene);
	//glutIdleFunc(delay);
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//static float radius = 0.5;
	//std::vector<float> vertexBuffer;
	//for (float i = 0; i < 2 * 3.141592; i += (2 * 3.141592) / NUMBER_OF_VERTICES) {
	//	vertexBuffer.push_back(cos(i) * radius);    //X coordinate
	//	vertexBuffer.push_back(sin(i) * radius);    //Y coordinate
	//	vertexBuffer.push_back(0.0);                //Z coordinate
	//}
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer.data(), GL_STATIC_DRAW);
	//if (radius > 2)
	//	radius = 0;
	//radius += 0.03;
	//std::cout << radius << std::endl;
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertexBuffer.data());
	//glEnableVertexAttribArray(0);
	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model,glm::vec3(0.9f,0.2f,0));

	//unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glPointSize(10);
	glDrawArrays(GL_POINTS, 0, NUMBER_OF_VERTICES);

	glutSwapBuffers();
	

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}

GLvoid delay()
{
	std::cout << "delay" << std::endl;
	Sleep(50);
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{

}