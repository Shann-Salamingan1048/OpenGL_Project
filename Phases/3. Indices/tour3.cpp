#include "tour3.h"
void Indices()
{
	const char* vertexShaderScr = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderScr = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"		FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
		"}\n\0";

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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderScr, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmenShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmenShader, 1, &fragmentShaderScr, nullptr);
	glCompileShader(fragmenShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmenShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmenShader);

/*
	GLfloat vertices[] =
	{ // x,		y,							z
		// x, y, z
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower left corner	0
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Lower right corner	1
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	// Upper corner			2

		-0.5f / 2.0f, 0.5f * float(sqrt(3)) / 6, 0.0f,	//Inner left		3
		0.5f / 2.0f, 0.5f * float(sqrt(3)) / 6, 0.0f,	//Inner right		4
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f			//Inner down		5
	};
	GLuint indices[] =
	{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};
*/

	// Baliktad
	GLfloat vertices[] =
	{ // x,		y,							z
		// x, y, z
		-0.5f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,		// Upper left corner	0
		0.5f, 0.5f * float(sqrt(3)) * 2 /  3, 0.0f,		// Upper right corner	1
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	// Upper corner			2

		-0.5f / 2.0f, 0.5f * float(sqrt(3)) / 6, 0.0f,	//Inner left		3
		0.5f / 2.0f, 0.5f * float(sqrt(3)) / 6, 0.0f,	//Inner right		4
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f			//Inner down		5
	};
	GLuint indices[] =
	{
		0, 3, 2,
		3, 5, 4,
		2, 4, 1
	};


	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);


		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();



}