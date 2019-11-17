
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
		-0.25f,0.0f,0.0f,	r,g,b,
		0.0f,0.5f,0.0f,		r,g,b,
		0.25f,0.0f,0.0f,		r,g,b,
	};
	glGenBuffers(1, &triangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

void Draw_Triangle(GLuint ShaderProgram,GLuint VBO, float x, float y)
{
	srand(time(NULL));

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	sm = glm::scale(sm, glm::vec3(0.5f, 0.5f, 0.0f));
	glm::mat4 tm = glm::mat4(1.0f);

	tm = glm::translate(tm, glm::vec3(x, y, 0.0f));
	model = model*tm*sm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint fragment_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(fragment_id);
	glVertexAttribPointer(fragment_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(fragment_id);
	
}