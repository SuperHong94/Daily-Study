#include "InitApp.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLuint ShaderProgram;
GLuint VBO;
float sX = -1.0f, sY = 0.0f;
float endX = 1.0f, endY = 0.6f;
float x = 0.0f, y = 0.0f;
float t = 0.0f;
bool leftButton = false;
float dragStartX, dragStartY, dragEndX = dragStartX, dragEndY = dragStartX;
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Mouse(int x, int y);

void drawline();
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
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
	glutMouseFunc(Mouse);
	glutMotionFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{
	if (t > 1.0f) {
		t = 0.0f;
		x = sX;
		y = sY;
	}
	static float p2X = -0.5f, p2Y = 0.8f, p3X = 0.5f, p3Y = 0.8f;
	x = pow((1.0f - t), 3)*sX + (3 * t)*(pow((1.0f - t), 2))*p2X + (3 * (pow(t, 2)))*(1 - t)*p3X + (pow(t, 3))*endX;
	y = pow((1.0f - t), 3)*sY + (3 * t)*(pow((1.0f - t), 2))*p2Y + (3 * (pow(t, 2)))*(1 - t)*p3Y + (pow(t, 3))*endY;
	t += 0.001f;
	//std::cout << x << ' ' << y <<' '<<t<< std::endl;
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(ShaderProgram);
	Draw_Triangle(ShaderProgram, VBO, x, y);
	drawline();

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

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		leftButton = true;
		dragStartX = (x - 400) / 400.0f, dragStartY = (400 - y) / 400.0f;

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

		std::cout << "dddd'\n";
		//dragEndX = (x - 400) / 400.0f, dragEndY = (400 - y) / 400.0f;
		//std::cout << dragEndX << ' ' << dragEndY << std::endl;
		leftButton = false;
	}
}

void Mouse(int x, int y) //마우스 끌었을때
{
	if (leftButton) {
		dragEndX = (x - 400) / 400.0f, dragEndY = (400 - y) / 400.0f;
	}
}

void drawline()
{
	//float* vertexData = new float[6];
	float vertexData[] = {
		dragStartX,dragStartY,0.0f,
		dragEndX,dragEndY,0.0f


	};


	std::cout << "드로우 시작점" << dragStartX << ' ' << dragStartY << std::endl;
	std::cout << "드로우 끝점" << dragEndX << ' ' << dragEndY << std::endl;

	glm::mat4 model = glm::mat4(1.0f);

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);


	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);


	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(pos_id);
	//delete[] vertexData;
}