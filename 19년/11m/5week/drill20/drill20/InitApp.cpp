
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





void view(GLuint ShaderProgram)
{
	static float t = 0.0f;
	t += 0.01f;
	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 8.0f);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(ShaderProgram, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}
void Myprojection(GLuint ShaderProgram) {
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 1000.0f);
	unsigned int projectionLocation = glGetUniformLocation(ShaderProgram, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}

void Sun(GLuint ShaderProgram)
{
	loadObj("only_quad_sphere.obj");
	static float t = 0.0f;
	t += 0.1f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	sm = glm::scale(sm, glm::vec3(0.5f, 0.5f, 0.5f));
	rm = glm::rotate(rm, glm::radians(t), glm::vec3(0.0f, 1.0f, 0.0f));
	model = rm * sm*model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLUquadricObj *qobj;
	qobj = gluNewQuadric(); // 객체 생성하기
	if (Line)
		gluQuadricDrawStyle(qobj, GLU_LINE); // 도형 스타일
	else
		gluQuadricDrawStyle(qobj, GLU_FILL); // 도형 스타일
	gluQuadricNormals(qobj, GLU_SMOOTH); // 생략 가능
	gluQuadricOrientation(qobj, GLU_OUTSIDE); // 생략 가능
	gluSphere(qobj, 1.5, 50, 50);

}


void Earth1(GLuint ShaderProgram)
{
	static float t = 0.0f;
	t += 0.5f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	sm = glm::scale(sm, glm::vec3(0.25f, 0.25f, 0.25f));
	tm = glm::translate(tm, glm::vec3(2.0f, 0.0f, 0.0f));
	rm = glm::rotate(rm, glm::radians(t) * 2, glm::vec3(0.0f, 1.0f, 0.0f));
	model = rm * tm*sm*model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLUquadricObj *qobj;
	qobj = gluNewQuadric(); // 객체 생성하기
	if (Line)
		gluQuadricDrawStyle(qobj, GLU_LINE); // 도형 스타일
	else
		gluQuadricDrawStyle(qobj, GLU_FILL); // 도형 스타일
	gluQuadricNormals(qobj, GLU_SMOOTH); // 생략 가능
	gluQuadricOrientation(qobj, GLU_OUTSIDE); // 생략 가능
	gluSphere(qobj, 1.5, 50, 50);


	//model = rm*tm;
	glm::mat4 model1 = model;
	rm = glm::rotate(model, glm::radians(t) * 2, glm::vec3(0.0f, 1.0f, 0.0f));
	tm = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
	model1 = rm * tm;


	unsigned int modelLocation1 = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, glm::value_ptr(model1));

	GLUquadricObj *qobj1;
	qobj1 = gluNewQuadric(); // 객체 생성하기
	if (Line)
		gluQuadricDrawStyle(qobj, GLU_LINE); // 도형 스타일
	else
		gluQuadricDrawStyle(qobj, GLU_FILL); // 도형 스타일
	gluQuadricNormals(qobj1, GLU_SMOOTH); // 생략 가능
	gluQuadricOrientation(qobj1, GLU_OUTSIDE); // 생략 가능
	gluSphere(qobj1, 1.5, 50, 50);



}
void Earth2(GLuint ShaderProgram)
{

	static float t = 0.0f;
	t += 0.5f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	glm::mat4 rm2 = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 tm2 = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	sm = glm::scale(sm, glm::vec3(0.25f, 0.25f, 0.25f));
	tm = glm::translate(model, glm::vec3(2.0f, -2.0f, 0.0f));
	//tm2 = glm::translate(tm2, glm::vec3(-4.0f, -4.0f, 0.0f));
	//rm2 = glm::rotate(rm, glm::radians(0.45f), glm::vec3(0.0f, 0.0f, 0.0f));
	rm = glm::rotate(rm, glm::radians(-t) * 2, glm::vec3(1.0f, 1.0f, 0.0f));

	model = rm * tm*sm*model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLUquadricObj *qobj;
	qobj = gluNewQuadric(); // 객체 생성하기
	if (Line)
		gluQuadricDrawStyle(qobj, GLU_LINE); // 도형 스타일
	else
		gluQuadricDrawStyle(qobj, GLU_FILL); // 도형 스타일
	gluQuadricNormals(qobj, GLU_SMOOTH); // 생략 가능
	gluQuadricOrientation(qobj, GLU_OUTSIDE); // 생략 가능
	gluSphere(qobj, 1.5, 50, 50);


	//model = rm*tm;
	glm::mat4 model1 = model;
	rm = glm::rotate(model, glm::radians(t) * 2, glm::vec3(1.0f, 1.0f, 0.0f));
	tm = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
	model1 = rm * rm2 * tm;


	unsigned int modelLocation1 = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, glm::value_ptr(model1));

	GLUquadricObj *qobj1;
	qobj1 = gluNewQuadric(); // 객체 생성하기
	if (Line)
		gluQuadricDrawStyle(qobj, GLU_LINE); // 도형 스타일
	else
		gluQuadricDrawStyle(qobj, GLU_FILL); // 도형 스타일
	gluQuadricNormals(qobj1, GLU_SMOOTH); // 생략 가능
	gluQuadricOrientation(qobj1, GLU_OUTSIDE); // 생략 가능
	gluSphere(qobj1, 1.5, 50, 50);

}


void Earth3(GLuint ShaderProgram)
{

	static float t = 0.0f;
	t += 0.5f;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	glm::mat4 rm2 = glm::mat4(1.0f);
	glm::mat4 tm = glm::mat4(1.0f);

	glm::mat4 sm = glm::mat4(1.0f);
	sm = glm::scale(sm, glm::vec3(0.25f, 0.25f, 0.25f));
	tm = glm::translate(model, glm::vec3(2.0f, 2.0f, 0.0f));

	rm = glm::rotate(rm, glm::radians(t) * 2, glm::vec3(1.0f, -1.0f, 0.0f));

	model = rm * tm*sm*model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	GLUquadricObj *qobj;
	qobj = gluNewQuadric(); // 객체 생성하기
	if (Line)
		gluQuadricDrawStyle(qobj, GLU_LINE); // 도형 스타일
	else
		gluQuadricDrawStyle(qobj, GLU_FILL); // 도형 스타일
	gluQuadricNormals(qobj, GLU_SMOOTH); // 생략 가능
	gluQuadricOrientation(qobj, GLU_OUTSIDE); // 생략 가능
	gluSphere(qobj, 1.5, 50, 50);


	//model = rm*tm;
	glm::mat4 model1 = model;
	rm = glm::rotate(model, glm::radians(t) * 2, glm::vec3(1.0f, -1.0f, 0.0f));
	tm = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
	model1 = rm * rm2 * tm;


	unsigned int modelLocation1 = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, glm::value_ptr(model1));

	GLUquadricObj *qobj1;
	qobj1 = gluNewQuadric(); // 객체 생성하기
	if (Line)
		gluQuadricDrawStyle(qobj, GLU_LINE); // 도형 스타일
	else
		gluQuadricDrawStyle(qobj, GLU_FILL); // 도형 스타일
	gluQuadricNormals(qobj1, GLU_SMOOTH); // 생략 가능
	gluQuadricOrientation(qobj1, GLU_OUTSIDE); // 생략 가능
	gluSphere(qobj1, 1.5, 50, 50);

}



