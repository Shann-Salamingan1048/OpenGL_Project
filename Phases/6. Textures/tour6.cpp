#include "tour6.h"

void class6::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}
class6::class6()
{
	init();
	m_window = glfwCreateWindow(800, 800, "OpenGL", nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cout << "failed to create glfw window\n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
}
class6::class6(uint16_t width, uint16_t height, const char* title)
{
	init();
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cout << "failed to create glfw window\n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
}

void class6::run()
{
	Shader shader("Phases/6. Textures/default.vert", "Phases/6. Textures/default.frag");
	// Vertices coordinates
	// Vertices coordinates
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};
	// Indices for vertices order
	GLuint indices[] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};
	VAO vao;
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	GLuint uniID = glGetUniformLocation(shader.ID, "scale");
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();

	std::string texPath = "\\OpenGL_Project\\Phases\\6. Textures\\images\\";
	std::cout << parentDir + texPath;
	// Texture
	Texture popCat((parentDir + texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shader, "tex0", 0);

	while (!glfwWindowShouldClose(m_window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();

		float time = glfwGetTime();
		glUniform1f(uniID, time);
		popCat.Bind();
		vao.Bind();

		// ----------------------------------v Number of vertices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}


	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	popCat.Delete();
	shader.Delete();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}


