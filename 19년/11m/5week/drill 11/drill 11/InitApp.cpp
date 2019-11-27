
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
void CreateTriangle(GLuint& VBO) {
	float vertexData[] = {
		0.0f,0.5f,0.0f,
		-0.25f,0.0f,0.0f,
		0.25f,0.0f,0.0f,
		
	};
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
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
	float vertexData[]{
		-1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,

		0.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f,
	};

	glGenBuffers(1, &Axis);
	glBindBuffer(GL_ARRAY_BUFFER, Axis);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}
void CreateSine(GLuint& Sine)
{
	const float pi = 3.141592f;
	std::vector<float> vertexData;
	for (float i = 0.0f; i < 1000.0f; i += 0.1f) {
		vertexData.push_back(i*0.1f-1.0f);
		vertexData.push_back(sin(i)*0.5f);
		vertexData.push_back(0.0f);
	}
	std::cout << vertexData.size() << std::endl;
	glGenBuffers(1, &Sine);
	glBindBuffer(GL_ARRAY_BUFFER, Sine);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
}
int CreateSpring(GLuint& Spring)
{
	const float pi = 3.141592f;
	std::vector<float> vertexData;
	for (float j = -1.0f; j < 2.0f; j += 0.1f) {
		for (float i = 0.0f; i < 2*pi; i += 0.01f) {
			vertexData.push_back((cos(i))*0.3f+j);
			vertexData.push_back(sin(i)*0.3f);
			vertexData.push_back(0.0f);
		}
	}
	std::cout << vertexData.size() << std::endl;
	glGenBuffers(1, &Spring);
	glBindBuffer(GL_ARRAY_BUFFER, Spring);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
	return vertexData.size();
}

void CreateZig(GLuint&Zig)
{
	std::vector<float> vertexData;
	float plus = 1.0f;
	for (float j = -1.0f; j <= 1.0f; j += 0.1f) {
		vertexData.push_back(j);
		vertexData.push_back(plus*0.5);
		vertexData.push_back(0.0f);
		plus =-1.0f*plus;
	}

	glGenBuffers(1, &Zig);
	glBindBuffer(GL_ARRAY_BUFFER, Zig);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
	std::cout << vertexData.size() << std::endl;
}
void drawZig(GLuint ShaderProgram, GLuint Zig)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	
	if (rotate)
		rm = glm::rotate(rm, glm::radians(r), glm::vec3(1.0f, r, 1.0f));
	model = rm*model;
	GLuint modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glBindBuffer(GL_ARRAY_BUFFER, Zig);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);
	glDrawArrays(GL_LINE_STRIP, 0, 20);
	glDisableVertexAttribArray(pos_id);
}
void drawAxis(GLuint ShaderProgram, GLuint Axis)
{
	glm::mat4 model = glm::mat4(1.0f);
	GLuint modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	
	std::cout << r << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, Axis);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, 4);
	glDisableVertexAttribArray(pos_id);

}

void drawSine(GLuint ShaderProgram, GLuint Sine)
{
	//glm::mat4 model = glm::mat4(1.0f);
	//
	////model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	//GLuint modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));


	if (rotate)
		model = glm::rotate(model, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
	model =  model* rm;
	GLuint modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER, Sine);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINE_STRIP, 0, 30003);
	glDisableVertexAttribArray(pos_id);

}

void drawSpring(GLuint ShaderProgram, GLuint Spring, int size)
{
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 rm = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));


	if (rotate)
		model = glm::rotate(model, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
	model = model * rm;
	GLuint modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));


	glBindBuffer(GL_ARRAY_BUFFER, Spring);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINE_STRIP, 0, size);
	glDisableVertexAttribArray(pos_id);

}