// Kinecraft1.cpp : Defines the entry point for the application.
//

#include "Kinecraft1.h"


float vertices[]{
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};


unsigned int VBO;
unsigned int VAO;

const char* vertexShaderSource = "#version 330\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;"
"void main() {\n"
"	gl_Position= vec4(aPos, 1.0);\n"
"	vertexColor= vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330\n"
"out vec4 FragColor;"

"uniform vec4 ourColor;"
"void main() {\n"
"	FragColor = ourColor;\n"
"}\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Kinecraft", NULL, NULL);
	if (window == NULL) {
		std::cout << "Kinecraft >> Failed to create GLFW window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Kinecraft >> Failed to initialize GLAD\n";
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	// vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Kinecraft >> Error while compiling the shader\n" << infoLog << std::endl;
	}

	// Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Kinecraft >> Error while compiling the shader fragment\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Kinecraft >> Error while compiling the shader shaderProgram\n" << infoLog << std::endl;
	}


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Kinecraft >> Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;



		while (!glfwWindowShouldClose(window)) {
			// Input handling
			processInput(window);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(shaderProgram);


			float timeValue = glfwGetTime();
			float greenValue = sin(timeValue / 2.0) + 0.5;
			int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
			std::cout << "Green Value: " << greenValue << "\nOurColor Value: " << vertexColorLocation << std::endl;
			glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			// check and call events and swap the buffers
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glfwTerminate();
	return 0;
}