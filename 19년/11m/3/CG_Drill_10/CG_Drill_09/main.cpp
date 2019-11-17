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
float X = 0.0f;
float Y = 0.0f;
float Rx = 0.0f;
float Rz = 0.0f;
float Rangle = 0.0f;
bool cube = true;
bool con = false;
bool con3 = false;
bool disk = false;
bool cylinder = false;
bool rotate = false;
bool Rrotate = false;
GLvoid draw_Axis();
GLvoid draw_Sphere(float x);
GLvoid drawCon(float x);
GLvoid drawConY(float x);
GLvoid drawDisck(float x);
GLvoid drawCylinder(float x);
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
		angle += 0.2f;

	if (Rrotate) {
		int a = 0;
		Rx = sin(glm::radians(Rangle));
		Rz = cos(glm::radians(Rangle));
		Rangle += 0.2f;
		angle += 0.2f;
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(ShaderProgram);


	//glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 1.0f);
	//glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	//view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(ShaderProgram, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = glm::mat4(1.0f);
	//projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 1000.0f);
	unsigned int projectionLocation = glGetUniformLocation(ShaderProgram, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	draw_Axis();
	if (cube)
		draw_Sphere(angle);
	if (con)
		drawCon(angle);
	if (con3)
		drawConY(angle);
	if (disk)
		drawDisck(angle);
	if (cylinder)
		drawCylinder(angle);


	glutSwapBuffers();


}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}
GLvoid draw_Sphere(float x)
{


	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 rm = glm::mat4(1.0f); //회전
	glm::mat4 rtm = glm::mat4(1.0f); //이동
	glm::mat4 tm = glm::mat4(1.0f); //이동
	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	rtm = glm::translate(rtm, glm::vec3(Rx, 0.0f, Rz));
	rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0f, 1.0f, 0));
	tm = glm::translate(tm, glm::vec3(X, Y, 0.0f));
	model = model * tm* rm*rtm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	GLUquadric* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluSphere(qobj, 1.0, 50, 50);
}

GLvoid draw_Axis()
{
	glm::mat4 model = glm::mat4(1.0f); //최종

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
	glm::mat4 rtm = glm::mat4(1.0f); //이동
	glm::mat4 tm = glm::mat4(1.0f); //이동
	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	rtm = glm::translate(rtm, glm::vec3(Rx, 0.0f, Rz));
	rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0f, 1.0f, 0));
	tm = glm::translate(tm, glm::vec3(X, Y, 0.0f));
	model = model * tm* rm*rtm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLUquadric* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 1.0, 0.0, 2.0, 20, 8);

}
GLvoid drawConY(float x)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 rm = glm::mat4(1.0f); //회전
	glm::mat4 rtm = glm::mat4(1.0f); //이동
	glm::mat4 tm = glm::mat4(1.0f); //이동
	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	rtm = glm::translate(rtm, glm::vec3(Rx, 0.0f, Rz));
	rm = glm::rotate(rm, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0));
	rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0f, 1.0f, 0));
	tm = glm::translate(tm, glm::vec3(X, Y, 0.0f));
	model = model * tm* rm*rtm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLUquadric* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 1.0, 0.0, 2.0, 20, 8);

}



GLvoid drawDisck(float x)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 rm = glm::mat4(1.0f); //회전
	glm::mat4 rtm = glm::mat4(1.0f); //이동
	glm::mat4 tm = glm::mat4(1.0f); //이동
	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	rtm = glm::translate(rtm, glm::vec3(Rx, 0.0f, Rz));
	rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0f, 1.0f, 0));
	tm = glm::translate(tm, glm::vec3(X, Y, 0.0f));
	model = model * tm* rm*rtm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLUquadric* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluDisk(qobj, 0.5f, 2.0f, 20, 3);
}
GLvoid drawCylinder(float x)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 rm = glm::mat4(1.0f); //회전
	glm::mat4 rtm = glm::mat4(1.0f); //이동
	glm::mat4 tm = glm::mat4(1.0f); //이동
	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	rtm = glm::translate(rtm, glm::vec3(Rx, 0.0f, Rz));
	rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0f, 1.0f, 0));
	tm = glm::translate(tm, glm::vec3(X, Y, 0.0f));
	model = model * tm* rm*rtm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLUquadric* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8);
}







void InputKey(unsigned char key, int x, int y)
{
	static bool culling = false;
	switch (key)
	{
	case '1':
		con = false;
		cube = true;
		con3 = false;
		disk = false;
		cylinder = false;
		break;
	case '2':
		cube = false;
		con3 = false;
		con = true;
		disk = false;
		cylinder = false;
		break;
	case '3':
		con3 = true;
		cube = false;
		con = false;
		disk = false;
		cylinder = false;
		break;
	case '4':
		con3 = false;
		cube = false;
		con = false;
		disk = true;
		cylinder = false;
		break;
	case '5':
		con3 = false;
		cube = false;
		con = false;
		disk = false;
		cylinder = true;
		break;
	case 'y':
		if (rotate)
			rotate = false;
		else
			rotate = true;
		break;
	case 'w':
		Y += 0.5f;
		break;
	case 'a':
		X -= 0.3f;
		break;
	case 's':
		Y -= 0.3f;
		break;
	case 'd':
		X += 0.3f;
		break;
	case 'r':
		if (!Rrotate)
			Rrotate = true;
		else
			Rrotate = false;
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
	case 'c':
		angle = 0;
		X = 0.0f;
		Y = 0.0f;
		Rx = 0.0f;
		Rz = 0.0f;
		Rangle = 0.0f;
		cube = true;
		con = false;
		con3 = false;
		disk = false;
		cylinder = false;
		rotate = false;
		Rrotate = false;
		break;
	default:
		break;
	}
}