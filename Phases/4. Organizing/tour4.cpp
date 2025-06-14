#include "tour4.h"

void run4()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "Open a Window", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "failed to create glfw window\n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	
	Shader shader("Phases/4. Organizing/default.vert", "Phases/4. Organizing/default.frag");
	// Baliktad
	GLfloat vertices[] =
	{
		-0.5f, 0.5f, 0.0f, // 0
		-0.5f, -0.5f, 0.0f, // 1
		 0.5f, 0.5f, 0.0f, // 2
		 0.5f, -0.5f, 0.0f, // 3

		 -0.25f, 0.25f, 0.0f, // 4
		 -0.25f, -0.25f, 0.0f, // 5
		 0.25f,0.25f, 0.0f, // 6
		 0.25f, -0.25f, 0.0f, // 7

		 -0.25f, 0.5f, 0.0f, // 8
		 -0.25f, -0.5f, 0.0f, // 9
		 0.25f, -0.5f, 0.0f, // 10
		 0.25f, 0.5f, 0.0f // 11

	};
	GLuint indices[] =
	{
		0, 8, 9,
		1, 9, 0,

		5, 9, 10,
		7, 10, 5,

		11, 2, 3,
		10, 3, 11,

		8, 11, 6,
		4, 8, 6

	};

	VAO vao;
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));
	
	vao.LinkVBO(vbo, 0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();
		vao.Bind();

		// ----------------------------------v Number of vertices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shader.Delete();
	
	glfwDestroyWindow(window);
	glfwTerminate();



}