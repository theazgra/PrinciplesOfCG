#pragma once
//GLEW - The OpenGL Extension Wrangler Library
#include <GL/glew.h>

#include <string.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class ShaderLoader
{
	GLuint	programID, vertexID, fragmentID;
	string loadFile(const char *fname);
public:
	GLuint loadShader(const char *vertexFile, const char *fragmentFile);
	void deleteShader();
};

