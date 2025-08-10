#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Shader.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//float vertices[] = {
////     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//};
//float vertices[] = {
//	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // ����
//		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // ����
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // ����
//};
//float vertices[] = {
//	// positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f, // top right
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f, // bottom right
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f, // bottom left
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f  // top left 
//};
unsigned int indices[] = 
{
	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};

float texCoords[] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.5f, 1.0f,
};

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

//float vertices_A[] = 
//{
//	-1.0f, -1.0f, 0.0f,
//	0.0f, -1.0f, 0.0f,
//	-0.5f, 1.0f, 0.0f,
//};
//
//float vertices_B[] =
//{
//	0.0f, -1.0f, 0.0f,
//	1.0f, -1.0f, 0.0f,
//	0.5f, 1.0f, 0.0f,
//};

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

	//// 4. �����ͱ���shader program
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//check_shader_Fail(vertexShader, GL_COMPILE_STATUS);
	//unsigned int fragShader;
	//fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragShader);
	//check_shader_Fail(fragShader, GL_COMPILE_STATUS);
	//// link shaders
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragShader);
	//glLinkProgram(shaderProgram);
	//check_shader_Fail(shaderProgram, GL_LINK_STATUS);

	//// �ڶ���
	//unsigned int shaderProgram2;
	//shaderProgram2 = glCreateProgram();
	//unsigned int fragshaderyellow;
	//fragshaderyellow = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragshaderyellow, 1, &fragmentShaderSource_yellow, NULL);
	//glCompileShader(fragshaderyellow);
	//check_shader_Fail(shaderProgram2, GL_COMPILE_STATUS);
	//glAttachShader(shaderProgram2, vertexShader);
	//glAttachShader(shaderProgram2, fragshaderyellow);
	//glLinkProgram(shaderProgram2);
	//check_shader_Fail(shaderProgram2, GL_LINK_STATUS);

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragShader);
	//glDeleteShader(fragshaderyellow);

	stbi_set_flip_vertically_on_load(true);
	// gen tex
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// �趨��������wrap��filter����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width;
	int height;
	int nrChannels;
	unsigned char* data = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data); // �ͷ��ڴ�

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// TODO��Ҫ��Ҫ������һ�Σ�
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width1;
	int height1;
	int nrChannels1;
	unsigned char* data1 = stbi_load("Textures/awesomeface.png", &width1, &height1, &nrChannels1, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1); // �ͷ��ڴ�

	Shader shader("Shaders/shader.vs", "Shaders/shader.fs");
	float mixFactor = 0.0f;

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

	//// ���ö�������ָ��
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // TODO ����еڶ���������Ӧ����ôд��
	//glEnableVertexAttribArray(0); // ����location = 0 �����ԣ����ú�Opengl�Ż��VBO����������ݣ���Ȼ����Ĭ��ֵ��0, 0, 0, 1��

	//// Tri_A
	//unsigned int VAO_A;
	//glGenVertexArrays(1, &VAO_A);
	//glBindVertexArray(VAO_A);
	//unsigned int VBO_A;
	//glGenBuffers(1, &VBO_A);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_A);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_A), vertices_A, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindVertexArray(0);

	//// Tri_B
	//unsigned int VAO_B;
	//glGenVertexArrays(1, &VAO_B);
	//glBindVertexArray(VAO_B);
	//unsigned int VBO_B;
	//glGenBuffers(1, &VBO_B);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_B);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_B), vertices_B, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindVertexArray(0);


	//// ���Ӷ�������
	//// 0 => layout(location = 0)
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int EBO; // Element Buffer Object => Index Buffer Object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	shader.use();
	shader.setInt("tex1", 0);
	shader.setInt("tex2", 1);

	// �����߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	//std::cout << vec.x << vec.y << vec.z << std::endl;

	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	//unsigned int transformLoc = glGetUniformLocation(shader.Id, "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	float fov = 10.0f;
	float aspect = 0.1f;
	float xx = 0.0f;
	float yy = 0.0f;
	float zz = 0.0f;

	// Render Loop
	while (!glfwWindowShouldClose(window))
	{
		// ��������
		process_input(window);

		// Render Call
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		//glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		//unsigned int transformLoc = glGetUniformLocation(shader.Id, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		//float timeValue = glfwGetTime();
		//float movePos = ((sin(timeValue) / 2.0f) + 0.5f) * 0.5f;
		//shader.setFloat3("movePos", movePos, 0.0f, 0.0f);
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f; // [0, 1]
		//int vertexColorLocation = glGetUniformLocation(shader.Id, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		//shader.setFloat("ourColor", greenValue);
		//glUseProgram(shaderProgram);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6); // Use VBO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// ���һ�����������ǿ���ָ��EBO�е�ƫ���������ߴ���һ���������飬�������ǵ��㲻��ʹ��������������ʱ�򣩣��������ǻ���������д0��
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Use EBO
		//glBindVertexArray(0); // ���VAO

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
	
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glm::mat4 trans1 = glm::mat4(1.0f);
		//trans1 = glm::translate(trans1, glm::vec3(-0.5f, 0.5f, 0.0f));
		//float time = abs(sin(glfwGetTime()));
		//trans1 = glm::scale(trans1, glm::vec3(time, time, time));
		//transformLoc = glGetUniformLocation(shader.Id, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans1));
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		shader.use();

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			zz += 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			zz -= 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			//xx -= 0.1f; // ��������
			xx += 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			xx -= 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			//yy += 0.1f; // ��������
			yy -= 0.1f;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			//yy -= 0.1f;
			yy += 0.1f;
		}

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		view = glm::translate(view, glm::vec3(xx, yy, zz));
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		//projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
		//int modelLoc = glGetUniformLocation(shader.Id, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shader.Id, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projectionLoc = glGetUniformLocation(shader.Id, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			bool r = i == 0 || i % 3 == 0;
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = r ? 20.0f : 0;
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//glUseProgram(shaderProgram2);
		//glBindVertexArray(VAO_B);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);

		// ��鲢�����¼�������������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//glDeleteVertexArrays(1, &VAO_A);
	//glDeleteBuffers(1, &VBO_A);
	//glDeleteVertexArrays(1, &VAO_B);
	//glDeleteBuffers(1, &VBO_B);

	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	//glDeleteProgram(shaderProgram);
	glDeleteProgram(shader.Id);

	glfwTerminate();
	return 0;
}