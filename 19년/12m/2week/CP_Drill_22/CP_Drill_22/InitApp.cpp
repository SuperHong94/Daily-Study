
#include "InitApp.h"

#include "stb_image.h"

bool InitProgram(unsigned int& ShaderProgram)
{
	const char* vertexSource = filetobuf("Vertex.glsl");
	const char* fragmentSource = filetobuf("Fragment.glsl");
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	if (!Check(vertexShader)) {
		glDeleteShader(vertexShader);
		return false;
	}
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	if (!Check(fragmentShader))
	{
		glDeleteShader(fragmentShader);
		return false;
	}

	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);

	glLinkProgram(ShaderProgram);
	if (!Check(ShaderProgram)) {
		glDeleteProgram(ShaderProgram);
		return false;

	}
	glDetachShader(ShaderProgram, vertexShader);
	glDetachShader(ShaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



}


bool Check(unsigned int ShaderProgram)
{
	GLint state;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &state);
	if (state == GL_FALSE) {
		int infologLength = 0;
		glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &infologLength);
		if (infologLength > 1) {
			int charsWritten = 0;
			char* infolog = new char[infologLength];
			glGetProgramInfoLog(ShaderProgram, infologLength, &charsWritten, infolog);
			std::cout << infolog << std::endl;
			delete[] infolog;
		}
		return false;
	}
	return true;
}


void CreateCon(GLuint& ConEBO, GLuint& ConVBO, GLuint& ConTVBO, GLuint ShaderProgram)
{
	GLfloat vertexData[] = {
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f, 1.0f,0.0f, //2번점
		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f, 0.0f,0.0f, //1번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f, 1.0f,1.0f, //3번점

		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f, 1.0f,1.0f, //3번점
		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f, 0.0f,0.0f, //1번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f, 0.0f,1.0f,//4번점

		0.0f,0.5f,0.0f,		1.0f,1.0f,0.0f, 0.5f,0.5f, //0번점
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f, 0.0f,0.0f, //2번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f, 1.0f,0.0f, //3번점

		0.0f,0.5f,0.0f,		1.0f,1.0f,0.0f, 0.5f,0.5f, //0번점
		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f, 0.0f,0.0f, //1번점
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f, 1.0f,0.0f, //2번점

		0.0f,0.5f,0.0f,		1.0f,1.0f,0.0f, 0.5f,0.5f, //0번점
		.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f, 0.0f,0.0f,//4번점
		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f, 1.0f,0.0f, //1번점

		0.0f,0.5f,0.0f,		1.0f,1.0f,0.0f, 0.5f,0.5f, //0번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f, 0.0f,0.0f, //3번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f, 1.0f,0.0f, //4번점
	};
	glGenBuffers(1, &ConVBO);

	glBindBuffer(GL_ARRAY_BUFFER, ConVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	GLuint texture_id = glGetAttribLocation(ShaderProgram, "vTexCoord");
	glEnableVertexAttribArray(texture_id);
	glVertexAttribPointer(texture_id, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glGenTextures(1, &ConTVBO);
	glBindTexture(GL_TEXTURE_2D, ConTVBO);
	//std::cout << TVBO << std::endl;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int widthImage, heightImage, numberOfChannel;

	unsigned char *data = stbi_load("texture2.png", &widthImage, &heightImage, &numberOfChannel,0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int tLocation_1 = glGetUniformLocation(ShaderProgram, "outTexure");
	glUniform1i(tLocation_1, 0);
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


	
//glDisableVertexAttribArray(pos_id);
	//glDisableVertexAttribArray(frag_id);



}
void CreateCube(GLuint ShaderProgram, GLuint& EBO, GLuint& VBO, GLuint& TVBO)
{

	GLfloat vertex[] = {
		-0.5f,0.5f,-0.5f,	1.0f,1.0f,0.0f, 0.0f,1.0f, //0번점
		-0.5f,0.5f,0.5f,	0.0f,1.0f,1.0f, 0.0f,0.0f, //1번점
		0.5f,0.5f,0.5f,		1.0f,0.0f,1.0f, 1.0f,0.0f, //2번점

		-0.5f,0.5f,-0.5f,	1.0f,1.0f,0.0f, 0.0f,1.0f, //0번점
		0.5f,0.5f,0.5f,		1.0f,0.0f,1.0f, 1.0f,0.0f, //2번점
		0.5f,0.5f,-0.5f,	0.0f,0.0f,1.0f, 1.0f,1.0f, //3번점


		//앞
		-0.5f,0.5f,0.5f,	0.0f,1.0f,1.0f, 0.0f,1.0f, //1번점
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f, 0.0f,0.0f, //5번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f, 1.0f,0.0f, //6번점

		-0.5f,0.5f,0.5f,	0.0f,1.0f,1.0f, 0.0f,1.0f, //1번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f, 1.0f,0.0f, //6번점
		0.5f,0.5f,0.5f,		1.0f,0.0f,1.0f, 1.0f,1.0f, //2번점
		
		//우
		0.5f,0.5f,0.5f,		1.0f,0.0f,1.0f, 0.0f,1.0f, //2번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f, 0.0f,0.0f, //6번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f, 1.0f,0.0f, //7번점

		0.5f,0.5f,0.5f,		1.0f,0.0f,1.0f, 0.0f,1.0f, //2번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f, 1.0f,0.0f, //7번점
		0.5f,0.5f,-0.5f,	0.0f,0.0f,1.0f, 1.0f,1.0f, //3번점

		//좌
		-0.5f,0.5f,-0.5f,	1.0f,1.0f,0.0f, 0.0f,1.0f, //0번점
		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f, 0.0f,0.0f,  //4번점
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f, 1.0f,0.0f, //5번점

		-0.5f,0.5f,-0.5f,	1.0f,1.0f,0.0f, 0.0f,1.0f, //0번점
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f, 1.0f,0.0f, //5번점
		-0.5f,0.5f,0.5f,	0.0f,1.0f,1.0f, 1.0f,1.0f, //1번점
		

		//밑
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f, 0.0f,1.0f, //5번점
		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f, 0.0f,0.0f,  //4번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f, 1.0f,1.0f, //6번점

		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f, 0.0f,0.0f,  //4번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f, 0.0f,1.0f, //7번점
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f, 1.0f,1.0f, //6번점

		//뒤
		-0.5f,0.5f,-0.5f,	1.0f,1.0f,0.0f, 1.0f,1.0f, //0번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f, 0.0f,0.0f, //7번점
		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f, 1.0f,.0f,  //4번점

		-0.5f,0.5f,-0.5f,	1.0f,1.0f,0.0f, 1.0f,1.0f, //0번점
		0.5f,0.5f,-0.5f,	0.0f,0.0f,1.0f, 0.0f,1.0f, //3번점
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f, 0.0f,0.0f, //7번점
	};
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	std::cout << VBO << std::endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//3번째 인자는 다음꺼까지 얼마나 떨어질까, 맨뒤에 인자는 어디서 시작할까 x,y,z,r,g,b,니깐  3번쨰부터시작해서 6칸떨어져야 다음시작위치
	GLuint texture_id = glGetAttribLocation(ShaderProgram, "vTexCoord");
	glEnableVertexAttribArray(texture_id);
	glVertexAttribPointer(texture_id, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glGenTextures(1, &TVBO);
	glBindTexture(GL_TEXTURE_2D, TVBO);
	std::cout << TVBO << std::endl;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int widthImage, heightImage, numberOfChannel;
	
	unsigned char *data = stbi_load("texture2.png", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int tLocation_1 = glGetUniformLocation(ShaderProgram, "outTexure");
	glUniform1i(tLocation_1, 0);

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
	std::cout << EBO << std::endl;
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



void view(GLuint ShaderProgram, float x, float y, float z)
{
	glm::vec3 cameraPos = glm::vec3(0.0f + x, 2.0f + y, 10.0f + z);
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



GLvoid draw_cube(GLuint ShaderProgram, GLuint VBO, GLuint EBO, GLuint TVBO, float x)
{


	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //회전
	tm = glm::translate(tm, glm::vec3(1.0f, 0.0f, 0.0f));
	sm = glm::scale(sm, glm::vec3(1.0f, 1.0f, 1.0f));
	/*if (xrotate)
		rm = glm::rotate(rm, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0));


	if (centerRotate) {
		rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0, 1.0f, 0.0f));
		model = rm * tm * sm *model;
	}
	else*/
	model = tm * rm * sm *model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TVBO);

	glDrawArrays(GL_TRIANGLES,0, 36);
}

GLvoid drawCon(GLuint ShaderProgram, GLuint ConVBO, GLuint ConEBO, GLuint ConTVBO, float x)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f); //회전
	glm::mat4 rm = glm::mat4(1.0f); //회전
	glm::mat4 sm = glm::mat4(1.0f); //회전
	tm = glm::translate(tm, glm::vec3(-1.0f, 0.0f, 0.0f));
	sm = glm::scale(sm, glm::vec3(0.5f, 0.5f, 0.5f));
	/*if (centerRotate) {
		rm = glm::rotate(rm, glm::radians(x), glm::vec3(0.0, 1.0f, 0.0f));
		model = rm * tm * sm *model;
	}
	else if (yrotate) {
		rm = glm::rotate(rm, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

		model = tm * rm *sm* model;
	}
	else*/
	model = tm * sm;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindBuffer(GL_ARRAY_BUFFER, ConVBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ConEBO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ConTVBO);

	glDrawArrays(GL_TRIANGLES, 0, 18);


}