#pragma once
//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_images.h>
#include "../../shader.h"
#include "../../vbo.h"
#include "../../vao.h"
#include "../../ebo.h"
#include "../../Texture.h"


class class6
{
public:
	class6(uint16_t width, uint16_t height, const char* title);
	class6();
	void run();


private:
	void init();;
	GLFWwindow* m_window;

};