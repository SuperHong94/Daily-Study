
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


void CreateCone()
{
	GLfloat vertex[] = {
		0.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.5f, 1.0f,
		0.5f, -0.5f, -0.5f,	0.5f, 0.5f, 1.0f
	};
	
	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	GLint gIndices[]
	{
		1,3,2,
		2,3,4,

		0,1,2,
		0,3,1,

		0,3,4,
		0,2,4,

	};

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gIndices), &gIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//3��° ���ڴ� ���������� �󸶳� ��������, �ǵڿ� ���ڴ� ��� �����ұ� x,y,z,r,g,b,�ϱ�  3�������ͽ����ؼ� 6ĭ�������� ����������ġ


	glEnableVertexAttribArray(1);


}
void CreateCube(GLuint& EBO, GLuint& VBO)
{

	GLfloat vertex[] = {
		-0.5f,0.5f,-0.5f,	1.0f,1.0f,0.0f,  //0����
		-0.5f,0.5f,0.5f,	0.0f,1.0f,1.0f,  //1����
		0.5f,0.5f,0.5f,		1.0f,0.0f,1.0f,  //2����
		0.5f,0.5f,-0.5f,	0.0f,0.0f,1.0f,  //3����

		-0.5f,-0.5f,-0.5f,	0.0f,1.0f,0.0f,  //4����
		-0.5f,-0.5f,0.5f,	1.0f,0.0f,0.0f,  //5����
		0.5f,-0.5f,0.5f,	1.0f,1.0f,0.5f,  //6����
		0.5f,-0.5f,-0.5f,	0.0f,0.0f,0.0f,  //7����
	};
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	//front
	GLint gIndices[]
	{
		0,1,2,
		0,2,3,  //����

		1,5,6,
		1,6,2, //�ո�

		2,6,7,
		2,7,3, //������

		0,4,5,
		0,5,1, //������

		5,4,6,
		4,7,6,// �ظ�

		0,7,4, //�޸�
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