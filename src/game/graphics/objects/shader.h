#ifndef SHADER_H
#define SHADER_H


#include "../graphicssettings.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
class Shader
{
	private:
		std::string vertexFile;
		std::string fragmentFile;
		GLuint shaderProgram;
		GLuint vertexShader;
		GLuint fragmentShader;
		int loadShader(std::string, GLint);
		bool shaderCompileCheck(GLuint);
		bool shaderLinkCheck(GLuint);
	public:
		Shader(std::string, std::string);
		~Shader();
		void setupShaders();
		GLint getAttribLocation(std::string);
		GLint getUniformLocation(std::string);
		void useProgram(bool);
		void useProgramTransform(bool);
		void releaseResources();
};

#endif