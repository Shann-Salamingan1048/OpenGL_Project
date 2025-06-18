#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>


std::string get_file_contents(const char* filename);
class Shader
{
public:
	GLuint ID;
	Shader(const char* vertex, const char* frag);
	Shader();
	void Activate();
	void Delete();


	void setBool(const std::string& name, bool value) const;
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
private:
	void compileErrors(size_t shader, const char* type);
};
