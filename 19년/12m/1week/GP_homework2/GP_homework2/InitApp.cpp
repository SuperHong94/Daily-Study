
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

bool InitLightProgram(unsigned int& ShaderProgram)
{
	const char* vertexSource = filetobuf("lightVs.glvs");
	const char* fragmentSource = filetobuf("lightFs.glfs");
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
void CreateSphere(GLuint& VBO,GLuint& NVBO)
{
	std::vector< glm::vec3 > outvertex, outnormal;
	std::vector< glm::vec2 > outuv;
	loadObj("sphere.obj", outvertex, outnormal, outuv);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	

	glGenBuffers(1, &NVBO);
	glBindBuffer(GL_ARRAY_BUFFER, NVBO);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);

	std::cout << outvertex.size() << std::endl;
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
		-0.5f,0.5f,-0.5f,	 -1.0f,1.0f,-1.0f, //0번점
		-0.5f,0.5f,0.5f,	  -1.0f,1.0f,1.0f,//1번점
		0.5f,0.5f,0.5f,		  1.0f,1.0f,1.0f,//2번점
		0.5f,0.5f,-0.5f,	  1.0f,1.0f,-1.0f,//3번점

		-0.5f,-0.5f,-0.5f,	  -1.0f,-1.0f,-1.0f,//4번점
		-0.5f,-0.5f,0.5f,	  -1.0f,-1.0f,1.0f,//5번점
		0.5f,-0.5f,0.5f,	  1.0f,-1.0f,1.0f,//6번점
		0.5f,-0.5f,-0.5f,	  1.0f,-1.0f,-1.0f//7번점
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



void view(GLuint ShaderProgram,float x,float y,float z)
{
	static float t = 0.0f;
	t += 0.01f;
	glm::vec3 cameraPos = glm::vec3(0.0f+x, 2.0f+y, 10.0f+z);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f,0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(ShaderProgram, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}
void Myprojection(GLuint ShaderProgram) {
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 1.0f, 100.0f);
	unsigned int projectionLocation = glGetUniformLocation(ShaderProgram, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}





void drawRobot(GLuint EBO, GLuint VBO, GLuint ShaderProgram)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 transalte = glm::mat4(1.0f);
	transalte = glm::translate(transalte, glm::vec3(0.0f, 1.0f, 0.0f));
	scale = glm::scale(scale, glm::vec3(1.0f, 1.0f, 1.0f));
	model = transalte*scale * model;
	int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "myColor");
	glUniform4f(colorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
	std::cout << modelLocation << std::endl;


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	int light_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id);
	glVertexAttribPointer(light_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(light_id);

	//코만들꺼임
	glm::mat4 noseModel = model;
	glm::mat4 nose_model = glm::mat4(1.0f);
	glm::mat4 nose_scale = glm::mat4(1.0f);
	nose_scale = glm::scale(nose_scale, glm::vec3(0.25, 0.25, 1.0f));
	glm::mat4 nose_transalte = glm::mat4(1.0f);
	nose_transalte = glm::translate(nose_transalte, glm::vec3(0.0f, 1.0f, 1.0f));
	noseModel = nose_transalte *nose_scale *noseModel;
	int noseLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(noseLocation, 1, GL_FALSE, glm::value_ptr(noseModel));

	int noseColor = glGetUniformLocation(ShaderProgram, "myColor");
	glUniform4f(noseColor, 0.0f, 0.0f, 1.0f, 1.0f);


	int nose_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(nose_id);
	glVertexAttribPointer(nose_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(nose_id);

}
void drawMap(GLuint EBO, GLuint VBO,GLuint ShaderProgram)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	scale = glm::scale(scale, glm::vec3(5.0f, -1.0f, 5.0f));
	model = scale * model;
	int modelLocation = glGetUniformLocation(ShaderProgram,"trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "myColor");
	glUniform4f(colorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
	std::cout << modelLocation << std::endl;


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	int light_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(light_id);
	glVertexAttribPointer(light_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(light_id);

}