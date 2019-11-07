#pragma once

bool InitProgram(unsigned int& ShaderProgram);
bool Check(unsigned int ShaderProgram);
void InitBuffer(GLuint& VAO);
void CreateCube(GLuint& VAO);
void CreateCone();