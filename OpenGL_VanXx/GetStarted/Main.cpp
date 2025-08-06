#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//float vertices[] =
//{
//	-0.5f, -0.5f, 0.0f,
//	0.5f, -0.5f, 0.0f,
//	0.0f, 0.5f, 0.0f
//};

//float vertices[] = 
//{
//	0.5f, 0.5f, 0.0f,   // ���Ͻ�
//	0.5f, -0.5f, 0.0f,  // ���½�
//	-0.5f, -0.5f, 0.0f, // ���½�
//	-0.5f, 0.5f, 0.0f   // ���Ͻ�
//};
//unsigned int indices[] = 
//{
//	0, 1, 3, // ��һ��������
//	1, 2, 3  // �ڶ���������
//};

float vertices_A[] = 
{
	-1.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	-0.5f, 1.0f, 0.0f,
};

float vertices_B[] =
{
	0.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.5f, 1.0f, 0.0f,
};


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource_yellow = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";


void frame_buffer_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void check_shader_Fail(GLuint shader, GLenum status)
{
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		if (status == GL_COMPILE_STATUS)
		{
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		if (status == GL_LINK_STATUS)
		{
			std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
		}
	}
}

int main()
{
	// 1. GLFW ��ʼ��������
	glfwInit();
	// ȷ��OpenGL�汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ʹ��OpenGL����ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 2. GLFW ����һ������
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_callback);

	// 3. GLAD ��ʼ�� load all OpenGL function pointers
	// glfwGetProcAddress�᷵�ص�ǰ����ϵͳOpenGLʹ�õĺ�����ַ�����غ���ָ��
	// �����(GLADloadproc)ǿת��Ϊ�˶���gladLoadGLLoader�Ĳ�������
	// gladLoadGLLoader��Ϊ��ά��OpenGL����ָ����򻯵��ã�����ƽ̨��ش��룩
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // TODO ����û����
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//void* ptr = glfwGetProcAddress("glDrawElements");
	//std::cout << ptr << std::endl; // 00007FFAFFE609E0
	//std::cout << glDrawElements << std::endl; // 00007FFAFFE609E0

	// 4. �����ͱ���shader program
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	check_shader_Fail(vertexShader, GL_COMPILE_STATUS);
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);
	check_shader_Fail(fragShader, GL_COMPILE_STATUS);
	// link shaders
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
	check_shader_Fail(shaderProgram, GL_LINK_STATUS);

	// �ڶ���
	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	unsigned int fragshaderyellow;
	fragshaderyellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragshaderyellow, 1, &fragmentShaderSource_yellow, NULL);
	glCompileShader(fragshaderyellow);
	check_shader_Fail(shaderProgram2, GL_COMPILE_STATUS);
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragshaderyellow);
	glLinkProgram(shaderProgram2);
	check_shader_Fail(shaderProgram2, GL_LINK_STATUS);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	glDeleteShader(fragshaderyellow);


	//// ʹ��VAO
	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);
	//// ��VAO
	//glBindVertexArray(VAO);
	////glBindVertexArray(0); // ���VAO Ҳ���ǰ�һ���յ�VAO

	//unsigned int VBO;
	//// TODO��Ϊʲô�����������ã����治�ǣ���ΪglGenBuffers������������һ��buffer��Ӧ��ID������Ҫ�������������ID���������ʹ��
	//glGenBuffers(1, &VBO); // ���� 1 ��buffer��Ȼ��ͨ�����÷���һ����ӦID
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//// �����ݸ��Ƶ��󶨵Ļ�����
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	////unsigned int EBO; // Element Buffer Object => Index Buffer Object
	////glGenBuffers(1, &EBO);
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	////glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// ���ö�������ָ��
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // TODO ����еڶ���������Ӧ����ôд��
	//glEnableVertexAttribArray(0); // ����location = 0 �����ԣ����ú�Opengl�Ż��VBO����������ݣ���Ȼ����Ĭ��ֵ��0, 0, 0, 1��

	// Tri_A
	unsigned int VAO_A;
	glGenVertexArrays(1, &VAO_A);
	glBindVertexArray(VAO_A);
	unsigned int VBO_A;
	glGenBuffers(1, &VBO_A);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_A);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_A), vertices_A, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	// Tri_B
	unsigned int VAO_B;
	glGenVertexArrays(1, &VAO_B);
	glBindVertexArray(VAO_B);
	unsigned int VBO_B;
	glGenBuffers(1, &VBO_B);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_B);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_B), vertices_B, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);


	//// ���Ӷ�������
	//// 0 => layout(location = 0)
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);


	// �����߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Render Loop
	while (!glfwWindowShouldClose(window))
	{
		// ��������
		process_input(window);

		// Render Call
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6); // Use VBO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// ���һ�����������ǿ���ָ��EBO�е�ƫ���������ߴ���һ���������飬�������ǵ��㲻��ʹ��������������ʱ�򣩣��������ǻ���������д0��
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Use EBO
		//glBindVertexArray(0); // ���VAO

		glBindVertexArray(VAO_A);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO_B);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// ��鲢�����¼�������������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO_A);
	glDeleteBuffers(1, &VBO_A);
	glDeleteVertexArrays(1, &VAO_B);
	glDeleteBuffers(1, &VBO_B);

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}