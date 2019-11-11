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


GLuint Axis;
float angle = 0;
bool cube = true;
bool con = false;
bool rotate = false;
bool lineOrFill = true;
GLvoid draw_Axis();
GLvoid draw_cube(float);
GLvoid drawCon(float x);
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
	CreateCon(ConEBO, ConVBO);
	CreateCube(EBO, VBO);

	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{
	if (rotate)
		angle += 0.1f;

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(ShaderProgram);
	draw_Axis();

	if (cube)
		draw_cube(angle);
	if (con)
		drawCon(angle);

	glutSwapBuffers();


}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}
GLvoid draw_cube(float x)
{


	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 rm = glm::mat4(1.0f); //회전

	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	rm = glm::rotate(rm, glm::radians(30.0f), glm::vec3(0.5f, 0.5f, 0));
	rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0f, 1.0f, 0));
	model = model * rm;
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

	if (lineOrFill)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(frag_id);
}

GLvoid draw_Axis()
{
	glm::mat4 model = glm::mat4(1.0f);
	GLuint modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER, Axis);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, 4);
	glDisableVertexAttribArray(pos_id);
}
GLvoid drawCon(float x)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 rm = glm::mat4(1.0f); //회전

	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	rm = glm::rotate(rm, glm::radians(30.0f), glm::vec3(0.5f, 0.5f, 0));
	rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0f, 1.0f, 0));

	model = model * rm;

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER, ConVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ConEBO);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	if (lineOrFill)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(frag_id);
}
void InputKey(unsigned char key, int x, int y)
{
	static bool culling = false;
	switch (key)
	{
	case 'c':
		con = false;
		cube = true;
		break;
	case 'p':
		cube = false;
		con = true;
		break;
	case 'y':
		if (rotate)
			rotate = false;
		else
			rotate = true;
		break;
	case 'w':
		if (lineOrFill)
			lineOrFill = false;
		else
			lineOrFill = true;
		break;
	case 'h':
		if (culling) {
			glEnable(GL_CULL_FACE);
			culling = false;
		}
		else
		{
			glDisable(GL_CULL_FACE);
			culling = true;
		}
		break;
	default:
		break;
	}
}