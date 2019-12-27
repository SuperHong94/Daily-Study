#include "Rectangle.h"


void myRectangle::CreateRectangle(GLuint ShaderProgram)
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

	glGenBuffers(1,&VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0], GL_STATIC_DRAW);
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


void myRectangle::draw(GLuint ShaderProgram, float x, float y, float z)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //회전
	tm = glm::translate(tm, glm::vec3(x, y,z));
	sm = glm::scale(sm, glm::vec3(0.25f, 0.25f, 0.25f));
	model = tm * rm * sm *model;
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "trans");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int colorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(colorLocation, 0.0f, 0.0f, 1.0f);

	/*int lightPosLocation = glGetUniformLocation(ShaderProgram, "LightColor");
	glUniform3f(lightPosLocation, 1.0f,1.0f,0.0f);*/


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vColor");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void myRectangle::lightDraw(GLuint ShaderProgram,float x,float y,float z)
{
	glm::mat4 model = glm::mat4(1.0f); //최종
	glm::mat4 tm = glm::mat4(1.0f);
	glm::mat4 sm = glm::mat4(1.0f);
	glm::mat4 rm = glm::mat4(1.0f); //회전
	tm = glm::translate(tm, glm::vec3(3.0f, 0.0f, 0.0f));
	sm = glm::scale(sm, glm::vec3(1.0f, 1.0f, 1.0f));
	model = tm * rm * sm *model;


	int lightPosLocation = glGetUniformLocation(ShaderProgram, "lightPos");
	glUniform3f(lightPosLocation,x,y,z);

	int lightColorLocation = glGetUniformLocation(ShaderProgram, "lightColor");
	glUniform3f(lightColorLocation, 0.0f, 1.0f, 1.0f);

	int objColorLocation = glGetUniformLocation(ShaderProgram, "objectColor");
	glUniform3f(objColorLocation, 0.0, 1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLuint pos_id = glGetAttribLocation(ShaderProgram, "vPos");
	glEnableVertexAttribArray(pos_id);
	glVertexAttribPointer(pos_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	GLuint frag_id = glGetAttribLocation(ShaderProgram, "vNormal");
	glEnableVertexAttribArray(frag_id);
	glVertexAttribPointer(frag_id, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));



	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



	glDisableVertexAttribArray(pos_id);
	glDisableVertexAttribArray(frag_id);
}