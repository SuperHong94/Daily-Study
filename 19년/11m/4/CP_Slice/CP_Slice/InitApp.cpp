
#include "InitApp.h"



bool InitProgram(unsigned int& ShaderProgram)
{
	const char* vertexSource = filetobuf("Vertex.glsl");
	const char* fragmentSource = filetobuf("Fragment.glsl");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	if (!Check(vertexShader)) return false;

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	if (!Check(fragmentShader)) return false;

	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (!Check(ShaderProgram)) {
		glDeleteProgram(ShaderProgram);
		return false;

	}


}


bool Check(unsigned int ShaderProgram)
{
	GLint state;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &state);
	if (state == GL_FALSE) {
		int infologLength = 0;
		glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &infologLength);
		if (infologLength > 0) {
			char* infolog = new char[infologLength];
			glGetProgramInfoLog(ShaderProgram, infologLength, NULL, infolog);
			std::cout << infolog << std::endl;
			delete[] infolog;
		}
		return false;
	}
	return true;
}

void CreateTriangle(GLuint& triangleVBO)
{
	srand(time(NULL));
	float r = (rand() % 11)*0.1f, g = (rand() % 11)*0.1f, b = (rand() % 11)*0.1f;

	GLfloat vertexData[] = {
		0.0f,0.25f,0.0f,		r,g,b,
		-0.125f,0.0f,0.0f,	r,g,b,
		0.125f,0.0f,0.0f,		r,g,b,
	};
	glGenBuffers(1, &triangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

glm::mat4 Draw_Triangle(GLuint ShaderProgram, GLuint VBO, float x, float y)
{

	glm::mat4 triangle;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	//sm = glm::scale(sm, glm::vec3(0.5f, 0.5f, 0.0f));

	tm = glm::translate(tm, glm::vec3(x, y, 0.0f));
	model = tm * sm;

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint fragment_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(fragment_id);
	glVertexAttribPointer(fragment_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));

	glDrawArrays(GL_TRIANGLES, 0, 3);


	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(fragment_id);

	//tm = glm::mat4(1.0f);
	triangle = model;

	return triangle;

}

bool Crush(float mouseStartX, float mouseStartY, float mouseEndX, float mouseEndY, glm::mat4 triangleVertex, glm::mat2& crushXY)
{
	int crushCount = 0; //점 2개 나와야 교점 완전한거임

	//glm::mat4 triangle = {
	//	{0.0f,0.25f,0.0f,1.0f}, //top
	//	{-0.125f,0.0f,0.0f,1.0f},  //left
	//	{0.125f,0.0f,0.0f,1.0f },  //right
	//	{0.0f,0.0f,0.0f,1.0f}
	//};
	//for (int i = 0; i < 4; i++) {
	//	triangle[i] = triangleVertex * triangle[i];
	//}
	glm::vec4 topV(0.0f, 0.25f, 0.0f, 1.0f);
	glm::vec4 leftV(-0.125f, 0.0f, 0.0f, 1.0f);
	glm::vec4 rightV(0.125f, 0.0f, 0.0f, 1.0f);
	topV = triangleVertex * topV;
	leftV = triangleVertex * leftV;
	rightV = triangleVertex * rightV;
	MYPOINT mouseStart, mouseEnd, Ttop, Tleft, Tright;
	mouseStart.x = mouseStartX; mouseStart.y = mouseStartY;
	mouseEnd.x = mouseEndX; mouseEnd.y = mouseEndY;
	Ttop.x = topV.x; Ttop.y = topV.y;
	Tleft.x = leftV.x; Tleft.y = leftV.y;
	Tright.x = rightV.x; Tright.y = rightV.y;

	//std::cout << Ttop.x << ' ' << Ttop.y << std::endl;
	MYPOINT crush;
	if (GetIntersectPoint(mouseStart, mouseEnd, Ttop, Tleft, crush)) {
		if (!cutState) {
			crushXY[crushCount].x = crush.x;
			crushXY[crushCount].y = crush.y;
			crushCount++;
			case1 = true;
		}


	}
	if (GetIntersectPoint(mouseStart, mouseEnd, Ttop, Tright, crush)) {
		if (!cutState) {
			crushXY[crushCount].x = crush.x;
			crushXY[crushCount].y = crush.y;
			case2 = true;
			crushCount++;
		}
	}
	if (GetIntersectPoint(mouseStart, mouseEnd, Tleft, Tright, crush)) {
		if (!cutState) {
			crushXY[crushCount].x = crush.x;
			crushXY[crushCount].y = crush.y;
			case3 = true;
			crushCount++;
		}
	}
	if (crushCount == 2) {

		return true;

	}
	else {
		case1 = false;
		case2 = false;
		case3 = false;
		return false;
	}


}

void DrawPoints(GLuint ShaderProgram, glm::mat2 CrushXY)
{
	const int start = 0, end = 1, x = 0, y = 1;
	float vertexData[] = {
		CrushXY[start][x],CrushXY[start][y],0.0f,
		CrushXY[end][x],CrushXY[end][y],0.0f
	};

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

	glPointSize(10);
	glDrawArrays(GL_POINTS, 0, 2);
	glDisableVertexAttribArray(pos_id);
}


bool GetIntersectPoint(const  MYPOINT& AP1, const  MYPOINT& AP2, const MYPOINT& BP1, const MYPOINT& BP2, MYPOINT& IP)

{
	double t;
	double s;
	double under = (BP2.y - BP1.y)*(AP2.x - AP1.x) - (BP2.x - BP1.x)*(AP2.y - AP1.y);

	if (under == 0)
		return false;


	double _t = (BP2.x - BP1.x)*(AP1.y - BP1.y) - (BP2.y - BP1.y)*(AP1.x - BP1.x);
	double _s = (AP2.x - AP1.x)*(AP1.y - BP1.y) - (AP2.y - AP1.y)*(AP1.x - BP1.x);

	t = _t / under;
	s = _s / under;
	if (t<0.0 || t>1.0 || s<0.0 || s>1.0)
		return false;



	if (_t == 0 && _s == 0)
		return false;



	IP.x = AP1.x + t * (double)(AP2.x - AP1.x);

	IP.y = AP1.y + t * (double)(AP2.y - AP1.y);

	return true;
}




void BezierCurve(MYPOINT* A)
{
	srand(time(NULL));
	float p2X = -0.5f, p2Y = 0.8f, p3X = 0.5f, p3Y = 0.8f;
	static float sX = -1.0f, sY = ((rand()%20)*0.1f)-1.0f, endX = 1.0f, endY = -1.0f;
	float t = 0.0f;
	for (int i = 0; i < BAZIERSIZE; i++) {

		A[i].x = pow((1.0f - t), 3)*sX + (3 * t)*(pow((1.0f - t), 2))*p2X + (3 * (pow(t, 2)))*(1 - t)*p3X + (pow(t, 3))*endX;
		A[i].y = pow((1.0f - t), 3)*sY + (3 * t)*(pow((1.0f - t), 2))*p2Y + (3 * (pow(t, 2)))*(1 - t)*p3Y + (pow(t, 3))*endY;
		t += 0.01f;
	}
}