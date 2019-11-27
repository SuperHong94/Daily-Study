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
GLuint tVBO;
GLuint EBO;
GLuint Axis;
GLuint Sine;
GLuint Spring;
GLuint Zig;
int t = 0;
int SpringSize = 0;

float sinx = 0;
float siny = 0;
float springX = 0.0f;
float springJ = -1.0f;
float zigX = -1.0f;
float plus = 1.0f;
float zigY = 0.0f;
float r = 0.0f;
bool rotate = false;
bool mysine = true;
bool myspring = false;
bool myzig = false;
GLvoid draw_cube(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x);
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
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
	CreateAxis(Axis);
	CreateSine(Sine);
	SpringSize = CreateSpring(Spring);
	CreateZig(Zig);
	CreateCube(EBO, VBO);
	CreateTriangle(tVBO);
	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
const float pi = 3.141592f;
void Timer(int a)
{
	if (rotate)
		r += 0.1f;

	if (mysine) {
		if (sinx > 20.0f)
			sinx = 0.0f;
		sinx += 0.01f;
	}
	if (myspring) {
		if (springX > 2 * pi) {
			springJ += 0.1f;
			springX = 0.0f;
		}
		springX += 0.01f;
	}

	if (myzig) {
		if (zigY > 1.0f) {
			plus = -1.0f;
		}
		else if (zigY < -1.0f)
			plus = 1.0f;

		zigX += 0.001f;
		zigY += 0.01f*plus;
		std::cout << zigY << std::endl;
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(ShaderProgram);
	drawAxis(ShaderProgram, Axis);
	if (myspring)
		drawSpring(ShaderProgram, Spring, SpringSize);
	if (mysine)
		drawSine(ShaderProgram, Sine);
	if (myzig)
		drawZig(ShaderProgram, Zig);
	draw_cube(ShaderProgram, VBO, EBO, 1);
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
	case 'r':
		if (rotate)
			rotate = false;
		else {
			rotate = true;

		}
		break;
	case '1':
		if (mysine)
			mysine = false;
		else {
			mysine = true;
			myspring = false;
			myzig = false;
		}
		break;
	case '2':
		if (myspring)
			myspring = false;
		else {
			mysine = false;
			myspring = true;
			myzig = false;
		}
		break;
	case '3':
		if (myzig)
			myzig = false;
		else {
			mysine = false;
			myspring = false;
			myzig = true;
		}
		break;
	case '0':
		sinx = 0;
		siny = 0;
		springX = 0.0f;
		springJ = -1.0f;
		zigX = -1.0f;
		plus = 1.0f;
		zigY = 0.0f;
		r = 0.0f;
		rotate = false;
		mysine = true;
		myspring = false;
		myzig = false;
	default:
		break;
	}
}
GLvoid draw_cube(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x)
{

	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 rm = glm::mat4(1.0f);
	if (rotate)
		rm = glm::rotate(rm, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
	//sin 곡선
	if (mysine) {
		glm::mat4 tm1 = glm::mat4(1.0f);
		glm::mat4 tm = glm::mat4(1.0f);
		glm::mat4 sm = glm::mat4(1.0f);
		tm1 = glm::translate(tm1, glm::vec3(-1.0f, 0.0f, 0.0f));
		tm = glm::translate(model, glm::vec3(sinx*0.1, sin(sinx)*0.5f, 0.0f));
		sm = glm::scale(sm, glm::vec3(0.25f, 0.25f, 0.25f));

		model =  tm* tm1*sm*rm ;
	}
	//spring 곡선
	if (myspring) {
		glm::mat4 sm = glm::mat4(1.0f);
		glm::mat4 tm = glm::mat4(1.0f);
		sm = glm::scale(sm, glm::vec3(0.25f, 0.25f, 0.25f));
		tm = glm::translate(tm, glm::vec3(cos(springX)*0.3f + springJ, sin(springX)*0.3, 0.0f));
		model = rm * tm * sm;
	}

	//zig곡선
	if (myzig) {
		glm::mat4 sm = glm::mat4(1.0f);
		glm::mat4 tm = glm::mat4(1.0f);
		sm = glm::scale(sm, glm::vec3(0.25f, 0.25f, 0.25f));
		tm = glm::translate(tm, glm::vec3(zigX, zigY*0.5f, 0.0f));

		model = rm * tm * sm*rm;
	}

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(frag_id);
}

void drawTriangle(int i)
{
	glm::mat4 triangle;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	//sm = glm::scale(sm, glm::vec3(0.5f, 0.5f, 0.0f));

	//tm = glm::translate(tm, glm::vec3(x, y, 0.0f));
	model = tm * sm;

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint fragment_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(fragment_id);
	glVertexAttribPointer(fragment_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));

	glDrawArrays(GL_TRIANGLES, 0, 3);


	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(fragment_id);
}