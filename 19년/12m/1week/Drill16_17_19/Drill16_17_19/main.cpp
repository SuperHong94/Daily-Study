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
GLuint SVBO;
GLuint SNVBO;

GLvoid draw_Sphere();
void Sun(GLuint ShaderProgram);
void Earth1(GLuint ShaderProgram);
void Earth2(GLuint ShaderProgram);
void Earth3(GLuint ShaderProgram);
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 0.0f;
float lightX = 0.0f, lightY = 1.0f, lightZ = 0.0f;
float lightRColor = 0.0f, lightGColor = 0.0f, lightBColor = 0.0f;
float angle = 0;
GLvoid draw_cube(float);

GLvoid draw_light(float x);
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
	CreateSphere(SVBO, SNVBO);

	InitProgram(ShaderProgram);
	InitLightProgram(LightProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{

	
	if (lightLotate) {
		angle += 0.1f;
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(ShaderProgram);
	view(ShaderProgram, cameraX, cameraY, cameraZ);
	Myprojection(ShaderProgram);
	//draw_Sphere();
	draw_cube(angle);
	//Sun(ShaderProgram);
	//Earth1(ShaderProgram);
	glUseProgram(LightProgram);
	view(LightProgram, cameraX, cameraY, cameraZ);
	Myprojection(LightProgram);
	draw_light(angle);

	glutSwapBuffers();


}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}
GLvoid draw_Sphere()
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = tm = glm::mat4(1.0f);
	glm::mat4 sm = sm = glm::mat4(1.0f);
	glm::mat4 rm = rm = glm::mat4(1.0f); //회전

	tm = glm::translate(tm, glm::vec3(0.0f, 0.0f, 0.0f));
	sm = glm::scale(sm, glm::vec3(0.125f, 0.125f, 0.125f));
	model = tm * sm *model;
	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightPos");
	glUniform3f(lightPosLocation, lightX, lightY, 0.0f);
	int lightColorLocation = glGetUniformLocation(ShaderProgram, "lightColor");
	glUniform3f(lightColorLocation, lightRColor, lightGColor, lightBColor);
	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, 1.0, 0.0f, 1.0f);


	glBindBuffer(GL_ARRAY_BUFFER, SVBO);
	int light_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id);
	glVertexAttribPointer(light_id, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, SNVBO);

	int normal_id = glGetAttribLocation(ShaderProgram, "vNormal");

	glEnableVertexAttribArray(normal_id);
	glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glDrawArrays(GL_TRIANGLES, 0, 2880);

	glDisableVertexAttribArray(light_id);
	glDisableVertexAttribArray(normal_id);
}
GLvoid draw_cube(float x)
{

	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = tm = glm::mat4(1.0f);
	glm::mat4 sm = sm = glm::mat4(1.0f);
	glm::mat4 rm = rm = glm::mat4(1.0f); //회전

	tm = glm::translate(tm, glm::vec3(0.0f, 0.0f, 0.0f));
	sm = glm::scale(sm, glm::vec3(1.0f, 1.0f, 1.0f));
	model = tm * sm *model;
	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightPos");
	glUniform3f(lightPosLocation, lightX, lightY, 0.0f);
	int lightColorLocation = glGetUniformLocation(ShaderProgram, "lightColor");
	glUniform3f(lightColorLocation, lightRColor, lightGColor, lightBColor);
	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, 1.0, 0.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	int light_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id);
	glVertexAttribPointer(light_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//std::cout << light_id << std::endl;
	int normal_id = glGetAttribLocation(ShaderProgram, "vNormal");
	//std::cout << normal_id << std::endl;
	glEnableVertexAttribArray(normal_id);
	glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(light_id);
	glDisableVertexAttribArray(normal_id);




}

GLvoid draw_light(float x)
{


	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //회전
	tm = glm::translate(tm, glm::vec3(lightX, lightY, 0.0f));
	sm = glm::scale(sm, glm::vec3(1.0f, 1.0f, 1.0f));
	if (lightLotate) {
		tm = glm::translate(tm, glm::vec3(5.0f, 0.0f, 0.0f));
		rm = glm::rotate(rm, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	model = rm * tm  * sm *model;
	lightX = model[3][0] * lightX;
	lightY = model[3][0] * lightY;
	int modelLocation = glGetUniformLocation(LightProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int lightPosLocation = glGetUniformLocation(LightProgram, "LightColor");
	glUniform3f(lightPosLocation, lightRColor, lightGColor, lightBColor);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GLuint pos_id = glGetAttribLocation(LightProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(pos_id);
}



void InputKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (lightLotate)
			lightLotate = false;
		else{
			lightLotate = true;
			angle = 0.0f;
		}
		break;
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
		cameraZ += 0.1f;
		break;
	case 'x':
		cameraZ -= 0.1f;
		break;
	case 'i':
		lightY += 0.1f;
		break;
	case 'j':
		lightX -= 0.1f;
		break;
	case 'k':
		lightY -= 0.1f;
		break;
	case 'l':
		lightX += 0.1f;
		break;
	case 'o':
		lightZ += 0.1f;
		break;
	case 'O':
		lightZ -= 0.1f;
		break;
	case 'r':
		srand(time(NULL));
		lightRColor = (rand() % 11)*0.1f;
		lightGColor = (rand() % 11)*0.1f;
		lightBColor = (rand() % 11)*0.1f;
		break;
	case 'q':
		lightRColor = 0.0f;
		lightGColor = 0.0f;
		lightBColor = 0.0f;
		break;
	default:
		break;
	}
}




void Sun(GLuint ShaderProgram)
{
	static float t = 0.0f;
	t += 0.1f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	sm = glm::scale(sm, glm::vec3(0.125f, 0.125f, 0.125f));
	rm = glm::rotate(rm, glm::radians(t), glm::vec3(0.0f, 1.0f, 0.0f));
	model = rm * sm*model;
	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightPos");
	glUniform3f(lightPosLocation, lightX, lightY, 0.0f);
	int lightColorLocation = glGetUniformLocation(ShaderProgram, "lightColor");
	glUniform3f(lightColorLocation, lightRColor, lightGColor, lightBColor);
	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, 1.0, 0.0f, 1.0f);


	glBindBuffer(GL_ARRAY_BUFFER, SVBO);
	int light_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id);
	glVertexAttribPointer(light_id, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, SNVBO);

	int normal_id = glGetAttribLocation(ShaderProgram, "vNormal");

	glEnableVertexAttribArray(normal_id);
	glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glDrawArrays(GL_TRIANGLES, 0, 2880);

	glDisableVertexAttribArray(light_id);
	glDisableVertexAttribArray(normal_id);
}



void Earth1(GLuint ShaderProgram)
{
	static float t = 0.0f;
	t += 0.5f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	sm = glm::scale(sm, glm::vec3(0.025f, 0.025f, 0.025f));
	tm = glm::translate(tm, glm::vec3(4.0f, 0.0f, 0.0f));
	rm = glm::rotate(rm, glm::radians(t) * 2, glm::vec3(0.0f, 1.0f, 0.0f));
	model = rm * tm*sm*model;
	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightPos");
	glUniform3f(lightPosLocation, lightX, lightY, 0.0f);
	int lightColorLocation = glGetUniformLocation(ShaderProgram, "lightColor");
	glUniform3f(lightColorLocation, lightRColor, lightGColor, lightBColor);
	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, 1.0, 0.0f, 1.0f);


	glBindBuffer(GL_ARRAY_BUFFER, SVBO);
	int light_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id);
	glVertexAttribPointer(light_id, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, SNVBO);

	int normal_id = glGetAttribLocation(ShaderProgram, "vNormal");

	glEnableVertexAttribArray(normal_id);
	glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glDrawArrays(GL_TRIANGLES, 0, 2880);


	//model = rm*tm;
	glm::mat4 model1 = model;
	glm::mat4 sm1 = glm::mat4(1.0f);
	sm1 = glm::scale(sm1, glm::vec3(10.0f, 10.0f, 10.0f));
	rm = glm::rotate(model, glm::radians(t) * 2, glm::vec3(0.0f, 1.0f, 0.0f));
	tm = glm::translate(model, glm::vec3(1000.0f, 0.0f, 0.0f));

	model1 = rm * tm*sm1;


	unsigned int modelLocation1 = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, glm::value_ptr(model1));

	int lightPosLocation1 = glGetUniformLocation(ShaderProgram, "LightPos");
	glUniform3f(lightPosLocation1, lightX, lightY, 0.0f);
	int lightColorLocation1 = glGetUniformLocation(ShaderProgram, "lightColor");
	glUniform3f(lightColorLocation1, lightRColor, lightGColor, lightBColor);
	int objColorLocation1 = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation1, 1.0, 0.0f, 1.0f);


	glBindBuffer(GL_ARRAY_BUFFER, SVBO);
	int light_id1 = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id1);
	glVertexAttribPointer(light_id1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, SNVBO);

	int normal_id1 = glGetAttribLocation(ShaderProgram, "vNormal");

	glEnableVertexAttribArray(normal_id1);
	glVertexAttribPointer(normal_id1, 3, GL_FLOAT, GL_FALSE, 0, 0);//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glDrawArrays(GL_TRIANGLES, 0, 2880);



}
