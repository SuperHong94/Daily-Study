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
float gravity = 0.0f;
int speed = 50;
glm::mat4 nowTriangleVertex;
glm::mat2 crushXY = glm::mat2(1.0f);
MYPOINT bazierArray[BAZIERSIZE];
bool case1 = false;
bool case2 = false;
bool case3 = false;
bool case1Count = false;
bool case2Count = false;
bool case3Count = false;
bool leftButton = false;
bool cutState = false;
bool PolygonType = true;
bool linePrint = true;
float dragStartX, dragStartY, dragEndX, dragEndY;
void Timer(int a);
void InputKey(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Mouse(int x, int y);
void drawline();
void drawSpline();
void drawRightPiece();
void drawleftPiece();
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
	BezierCurve(bazierArray);
	InitProgram(ShaderProgram);
	//glutIdleFunc(drawScene);
	glutKeyboardFunc(InputKey);
	glutTimerFunc(speed, Timer, 1);
	glutMouseFunc(Mouse);
	glutMotionFunc(Mouse);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void Timer(int a)
{
	glutPostRedisplay();

	glutTimerFunc(speed, Timer, 1);
}
GLvoid drawScene()
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	static int i = 0;
	if (i == 99)
		i = 0;
	if (gravity < -1.2f) {
		i = 0;
		gravity = 0.0f;
		case1 = false;
		case2 = false;
		case3 = false;
		cutState = false;
		case1Count = false;
		case2Count = false;
		case3Count = false;
	}
	if (!cutState) {
		x = bazierArray[i].x;
		y = bazierArray[i].y;
		i++;
	}

	glUseProgram(ShaderProgram);
	if (linePrint)
		drawSpline();
	if (!cutState)
		nowTriangleVertex = Draw_Triangle(ShaderProgram, VBO, x, y);
	//std::cout << nowTriangleVertex[3].x << "," << nowTriangleVertex[3].y << "," << nowTriangleVertex[3].z << std::endl;
	if (leftButton)
		drawline();
	if (Crush(dragStartX, dragStartY, dragEndX, dragEndY, nowTriangleVertex, crushXY)) {
		cutState = true;
		gravity = 0.0f;
	}
	if (cutState) {
		drawRightPiece();
		drawleftPiece();
	}
	else
		std::cout << "cutState" << std::endl;
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{

	glViewport(0, 0, w, h);

}


void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		leftButton = true;
		dragStartX = (x - 400) / 400.0f, dragStartY = (400 - y) / 400.0f;
		dragEndX = dragStartX, dragEndY = dragStartY;

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

		//dragEndX = (x - 400) / 400.0f, dragEndY = (400 - y) / 400.0f;
		//std::cout << dragEndX << ' ' << dragEndY << std::endl;
		leftButton = false;
		dragStartX = -2.0f, dragEndX = -2.0f, dragStartY = -2.0f, dragEndX = -2.0f;
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
	float vertexData[] = {
		dragStartX,dragStartY,0.0f,
		dragEndX,dragEndY,0.0f
	};


	//std::cout << "드로우 시작점" << dragStartX << ' ' << dragStartY << std::endl;
	//std::cout << "드로우 끝점" << dragEndX << ' ' << dragEndY << std::endl;

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
}

void drawSpline() {
	float vertexData[] = {
		dragStartX,dragStartY,0.0f,
		dragEndX,dragEndY,0.0f
	};


	//std::cout << "드로우 시작점" << dragStartX << ' ' << dragStartY << std::endl;
	//std::cout << "드로우 끝점" << dragEndX << ' ' << dragEndY << std::endl;

	glm::mat4 model = glm::mat4(1.0f);

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bazierArray), bazierArray, GL_DYNAMIC_DRAW);


	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);


	glDrawArrays(GL_LINE_STRIP, 0, BAZIERSIZE);

	glDisableVertexAttribArray(pos_id);
}

void drawRightPiece() {

	glm::vec2 CLvertex = crushXY[0];
	glm::vec2 CRvertex = crushXY[1];
	glm::mat4 triangleVertex = nowTriangleVertex;
	glm::vec4 topV(0.0f, 0.25f, 0.0f, 1.0f);
	glm::vec4 leftV(-0.125f, 0.0f, 0.0f, 1.0f);
	glm::vec4 rightV(0.125f, 0.0f, 0.0f, 1.0f);
	topV = triangleVertex * topV;
	leftV = triangleVertex * leftV;
	rightV = triangleVertex * rightV;
	if (crushXY[0].x < crushXY[1].x) {
		CLvertex = crushXY[0];
		CRvertex = crushXY[1];
	}
	else {
		CLvertex = crushXY[1];
		CRvertex = crushXY[0];
	}

	float vertexData0[] = { //새로운점 2개와 삼각형 오른쪽점 갖는 경우;
		CRvertex.x,CRvertex.y,0.0f,
		CLvertex.x,CLvertex.y,0.0f,
		rightV.x,rightV.y,0.0f
	};
	float vertexData1[] = {  //새로운점 2개와 삼각형 윗점, 삼각형 오른쪽점갖는경우
		CLvertex.x,CLvertex.y,0.0f,
		CRvertex.x,CRvertex.y,0.0f,
		rightV.x,rightV.y,0.0f,
		

		CLvertex.x,CLvertex.y,0.0f,
		topV.x,topV.y,0.0f,
		CRvertex.x,CRvertex.y,0.0f,
		

	};
	float vertexData2[] = {  //삼각형 윗점 새로운점 2개
		topV.x,topV.y,0.0f,
		CLvertex.x,CLvertex.y,0.0f,
		CRvertex.x,CRvertex.y,0.0f,
	};

	gravity -= 0.03f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.03f, gravity, 0.0f));
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//case1;//"위~왼쪽 충돌 \n";
	//case2;//"위~오른쪽 충돌 \n";
	//case3;//"왼쪽~오른쪽 충돌 \n";
	if (case2&&case3 || case1Count) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData0), vertexData0, GL_DYNAMIC_DRAW);

		GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
		glEnableVertexAttribArray(pos_id);
		glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);


		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(pos_id);
		case1Count = true;
	}
	else if (case1&&case3 || case2Count) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData1), vertexData1, GL_DYNAMIC_DRAW);


		GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
		glEnableVertexAttribArray(pos_id);
		glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);


		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(pos_id);
		case2Count = true;
	}
	else if (case1&&case2 || case3Count) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData2), vertexData2, GL_DYNAMIC_DRAW);

		GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
		glEnableVertexAttribArray(pos_id);
		glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);


		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(pos_id);
		case3Count = true;
	}

}


void drawleftPiece() {
	glm::vec2 CLvertex;
	glm::vec2 CRvertex;
	glm::mat4 triangleVertex = nowTriangleVertex;
	glm::vec4 topV(0.0f, 0.25f, 0.0f, 1.0f);
	glm::vec4 leftV(-0.125f, 0.0f, 0.0f, 1.0f);
	glm::vec4 rightV(0.125f, 0.0f, 0.0f, 1.0f);
	topV = triangleVertex * topV;
	leftV = triangleVertex * leftV;
	rightV = triangleVertex * rightV;
	if (crushXY[0].x < crushXY[1].x) {
		CLvertex = crushXY[0];
		CRvertex = crushXY[1];
	}
	else {
		CLvertex = crushXY[1];
		CRvertex = crushXY[0];
	}

	float vertexData0[] = { //새로운점 2개와 삼각형 윗점,삼각형 왼쪽점 갖는경우
		topV.x,topV.y,0.0f,
		leftV.x,leftV.y,0.0f,
		CLvertex.x,CLvertex.y,0.0f,

		topV.x,topV.y,0.0f,
		CLvertex.x,CLvertex.y,0.0f,
		CRvertex.x,CRvertex.y,0.0f
	};
	float vertexData1[] = {  //삼각형 왼쪽점과 새로운점 2개
		CRvertex.x,CRvertex.y,0.0f,
		CLvertex.x,CLvertex.y,0.0f,
		leftV.x,leftV.y,0.0f,


	};
	float vertexData2[] = {  //새로운점 2개와 삼각형 왼쪽점
		CLvertex.x,CLvertex.y,0.0f,
		leftV.x,leftV.y,0.0f,
		CRvertex.x,CRvertex.y,0.0f,

		CRvertex.x,CRvertex.y,0.0f,
		leftV.x,leftV.y,0.0f,
		rightV.x,rightV.y,0.0f,

	};
	gravity -= 0.01f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-0.03f, gravity, 0.0f));
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (case2&&case3 || case1Count) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData0), vertexData0, GL_DYNAMIC_DRAW);

		std::cout << "1번쨰 경우 \n";
		GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
		glEnableVertexAttribArray(pos_id);
		glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);


		glDrawArrays(GL_POLYGON, 0, 6);

		glDisableVertexAttribArray(pos_id);
		case1Count = true;
	}
	else if (case1&&case3 || case2Count) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData1), vertexData1, GL_DYNAMIC_DRAW);

		std::cout << "2번쨰 \n";
		GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
		glEnableVertexAttribArray(pos_id);
		glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);


		glDrawArrays(GL_POLYGON, 0, 3);

		glDisableVertexAttribArray(pos_id);
		case2Count = true;
	}
	else if (case1&&case2 || case3Count) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData2), vertexData2, GL_DYNAMIC_DRAW);
		std::cout << "3번쨰 \n";
		GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
		glEnableVertexAttribArray(pos_id);
		glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);


		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(pos_id);
		case3Count = true;
	}

}


void InputKey(unsigned char key, int x, int y)
{
	static bool culling = false;
	switch (key)
	{
	case 'c':

		break;
	case 'p':
		if (PolygonType) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			PolygonType = false;
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			PolygonType = true;
		}
		break;
	case '+':
		if (speed > 10)
			speed-=10;
		break;
	case '-':
		if (speed < 100)
			speed+=10;
		break;
	case 'l':
		if (linePrint)
			linePrint = false;
		else
			linePrint = true;
		break;
	case 'q':
		exit(1);
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
	case 'r':
		BezierCurve(bazierArray);
		glutPostRedisplay();
	default:
		break;
	}
}