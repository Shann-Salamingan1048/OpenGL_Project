#include "tour5.h"

void run5()
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
	
	Shader shader("Phases/5. Shaders/default.vert", "Phases/5. Shaders/default.frag");
	// Vertices coordinates
	GLfloat vertices[] =
	{ //               COORDINATES                  /     COLORS           //
		-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
		 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
		-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
		 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
		 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
	};

	
	GLuint indices[] =
	{
		0, 3, 2,
		3, 5, 4,
		2, 4, 1
	};

	VAO vao;
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));
	// Configure Position Attribute (Location 0)
	// 6 * sizeof(float) because there are 6 floats in a Row(coordinates and color)
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT ,6 * sizeof(float), (void*)0);
	//             │   │  │  │        │                   │
	//             │   │  │  │        │                   └─ Offset: Start at byte 0 of each vertex
	//             │   │  │  │        └─ Stride: 24 bytes between vertices (6 floats × 4 bytes each)
	//             │   │  │  └─ Data type: Each component is a float
	//             │   │  └─ Size: Read 3 components (X, Y, Z coordinates)
	//             │   └─ Attribute location: Corresponds to layout(location = 0) in vertex shader
	//             └─ Vertex Buffer Object containing the vertex data
	 
	
	// ↑ Attribute 0 (Position Location in default.vert): Read 3(numComponents) floats starting at offset 0, stride 24 bytes
	// stride starts taking 3 data from 0 or (0,1,2) which represents x , y ,z
	
	// Configure Color Attribute (Location 1) 
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT ,6 * sizeof(float), (void*)(3 * sizeof(float)));
	//             │   │  │  │        │                   │
	//             │   │  │  │        │                   └─ Offset: Start at byte 12 (skip 3 floats for position)
	//             │   │  │  │        └─ Stride: 24 bytes between vertices (same as position)
	//             │   │  │  └─ Data type: Each component is a float
	//             │   │  └─ Size: Read 3 components (R, G, B color values)
	//             │   └─ Attribute location: Corresponds to layout(location = 1) in vertex shader
	//             └─ Same VBO (interleaved data)
	// ↑ Attribute 1 (Color Location in default.vert): Read 3(numComponents) floats starting at offset 12, stride 24 bytes
	// stride starts taking 3 data from 3 or (3,4,5) which represents rgb
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	GLuint uniID = glGetUniformLocation(shader.ID, "uTime");
	// ID of the shader and the exact name of the uniform in the default.frag

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();

		float time = glfwGetTime();  // Get current time
	
		glUniform1f(uniID, time);
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