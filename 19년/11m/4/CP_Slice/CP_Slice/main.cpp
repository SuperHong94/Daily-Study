#include "InitApp.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLuint ShaderProgram;
GLuint VBO;
float sX = -1.0f, sY = 0.6f;
float endX = 1.0f, endY = 0.6f;
float x = 0.0f, y = 0.0f;
float t = 0.0f;

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

	CreateTriangle(VBO);
	InitProgram(ShaderProgram);
	glutDisplayFunc(drawScene);
	//glutKeyboardFunc(InputKey);
	glutTimerFunc(10, Timer, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{
	if (t >1.0f){
		t = 0.0f;
		x = sX;
		y = sY;
	}
	static float p2X = -0.5f, p2Y = 0.8f, p3X = 0.5f, p3Y = 0.8f;
	x = pow((1.0f - t), 3)*sX + (3 * t)*(pow((1.0f - t), 2))*p2X + (3 * (pow(t, 2)))*(1 - t)*p3X + (pow(t, 3))*endX;
	y = pow((1.0f - t), 3)*sY + (3 * t)*(pow((1.0f - t), 2))*p2Y + (3 * (pow(t, 2)))*(1 - t)*p3Y + (pow(t, 3))*endY;
	t += 0.01f;
	std::cout << x << ' ' << y <<' '<<t<< std::endl;
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(ShaderProgram);
	Draw_Triangle(ShaderProgram,VBO, x, y);
	

	glutSwapBuffers();


}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}


void InputKey(unsigned char key, int x, int y)
{
	return;
}