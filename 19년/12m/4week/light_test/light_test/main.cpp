#include "global.h"
#include "Init.h"
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLuint ShaderProgram;
GLuint ShaderProgram2;
float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 0.0f;
float lightX = 0.0f, lightY = 0.0f, lightZ = 0.0f;
myRectangle cube;
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
	CreateShader(ShaderProgram);
	CreateShader2(ShaderProgram2);
	cube.CreateRectangle(ShaderProgram);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(InputKey);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(ShaderProgram);
	view(ShaderProgram, cameraX, cameraY, cameraZ);
	Myprojection(ShaderProgram);
	cube.draw(ShaderProgram,lightX,lightY,lightZ);

	glUseProgram(ShaderProgram2);
	view(ShaderProgram2, cameraX, cameraY, cameraZ);
	Myprojection(ShaderProgram2);
	cube.lightDraw(ShaderProgram2, lightX, lightY, lightZ);
	glutSwapBuffers();
	glutPostRedisplay();


}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

}


void InputKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
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
	default:
		break;
	}
}
