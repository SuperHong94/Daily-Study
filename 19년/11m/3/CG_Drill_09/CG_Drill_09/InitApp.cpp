
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


void CreateCon(GLuint& ConEBO, GLuint& ConVBO)
{
	GLfloat vertexData[] = {
		0.0f,0.5f,0.0f,		1.0f,1.0f,0.0f,  //0번점
		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f,  //1번점
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f,  //2번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f,  //3번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f  //4번점
	};
	glGenBuffers(1, &ConVBO);

	glBindBuffer(GL_ARRAY_BUFFER, ConVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	unsigned int indexDeta[] = {
		2,1,3,
		3,1,4, //밑면
		0,2,3, //앞면
		0,1,2,//좌측면
		0,4,1,//뒷면
		0,3,4,//우측면	
	};
	glGenBuffers(1, &ConEBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ConEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 18, &indexDeta, GL_STATIC_DRAW);
}
void CreateCube(GLuint& EBO, GLuint& VBO)
{

	GLfloat vertex[] = {
		-0.5f,0.5f,-0.5f,	1.0f,1.0f,0.0f,  //0번점
		-0.5f,0.5f,0.5f,	0.0f,1.0f,1.0f,  //1번점
		0.5f,0.5f,0.5f,		1.0f,0.0f,1.0f,  //2번점
		0.5f,0.5f,-0.5f,	0.0f,0.0f,1.0f,  //3번점

		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f,  //4번점
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f,  //5번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f,  //6번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f,  //7번점
	};
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	//front
	GLint gIndices[]
	{
		0,1,2,
		0,2,3,  //윗면

		1,5,6,
		1,6,2, //앞면

		2,6,7,
		2,7,3, //우측면

		0,4,5,
		0,5,1, //좌측면

		5,4,6,
		4,7,6,// 밑면

		0,7,4, //뒷면
		0,3,7
	};

	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gIndices), &gIndices, GL_STATIC_DRAW);



}

void CreateAxis(GLuint& Axis)
{
	GLfloat AxisData[] = {
		1.0f,0.0f,0.0f,
		-1.0f,0.0f,0.0f,

		0.0f,1.0f,0.0f,
		0.0f,-1.0f,0.0f
	};
	glGenBuffers(1, &Axis);
	glBindBuffer(GL_ARRAY_BUFFER, Axis);
	glBufferData(GL_ARRAY_BUFFER, sizeof(AxisData), &AxisData, GL_STATIC_DRAW);
}

GLvoid draw_cube(GLuint ShaderProgram, GLuint VBO, GLuint EBO, float x)
{


	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 rm = glm::mat4(1.0f); //회전
	glm::mat4 tm = glm::mat4(1.0f); //회전

	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	rm = glm::rotate(rm, glm::radians(30.0f), glm::vec3(0.5f, 0.5f, 0));
	rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0f, 1.0f, 0));
	tm = glm::translate(tm, glm::vec3(0.5f, 0.0f, 0.0f));
	model = model * rm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(frag_id);
}