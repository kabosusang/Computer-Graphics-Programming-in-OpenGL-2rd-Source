// C++/OpenGL 应用程序
#include "Torus.hpp"
#include "Utils.hpp"

using namespace std;

float toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

#define numVAOs 1
#define numVBOs 4
float cameraX, cameraY, cameraZ;
float torLocX, torLocY, torLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// 分配在 display()函数中使用的变量空间，这样它们就不必在渲染过程中分配
GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;
//Texture
GLuint brickTexture;
float rotAmt = 0.0f;

//TorusModel
Torus myTorus{ 0.5f, 0.2f, 48 };
//Element
int numTorsIndices{};

void setupVertices(void) { // 36个顶点，12个三角形，组成了放置在原点处的2×2×2立方体

	const auto& ind = myTorus.getIndices();
	const auto& vert = myTorus.getVertices();
	const auto& tex = myTorus.getTexCoords();
	const auto& norm = myTorus.getNormals();

	//顶点位置
	std::vector<float> pvalues;
	//纹理坐标
	std::vector<float> tvalues;
	//法向量
	std::vector<float> nvalues;

	for (int i = 0; i < myTorus.getNumVertices(); i++) {
		//position
		pvalues.push_back((vert[i]).x);
		pvalues.push_back((vert[i]).y);
		pvalues.push_back((vert[i]).z);

		//tex vec2用s,t来区分
		tvalues.push_back((tex[i]).s);
		tvalues.push_back((tex[i]).t);

		//normal
		nvalues.push_back((norm[i]).x);
		nvalues.push_back((norm[i]).y);
		nvalues.push_back((norm[i]).z);
	}

	//Init Buffer
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	//输入position数据到Buffer缓冲区0
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, pvalues.data(), GL_STATIC_DRAW);

	//输入uv数据到Buffer缓冲区1
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, tvalues.data(), GL_STATIC_DRAW);

	//输入uv数据到Buffer缓冲区2
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, nvalues.data(), GL_STATIC_DRAW);

	//新增模型索引
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, ind.data(), GL_STATIC_DRAW);
}

void init(GLFWwindow* window) {
	renderingProgram = Utils::createShaderProgram(
			"Shader/Chapter6/Program1/vertShader.glsl",
			"Shader/Chapter6/Program1/fragShader.glsl");
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 2.0f;
	torLocX = 0.0f;
	torLocY = 0.0f;
	torLocZ = -0.5f;
	setupVertices();

	//proj
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

	//LoadTexture
	// brickTexture = Utils::loadTexture(
	// 		"Assets/Textures/Chapter5/brick1.jpg");

	brickTexture = Utils::loadTexture(
			"Assets/Textures/Chapter5/brick1.jpg");

	glBindTexture(GL_TEXTURE_2D, brickTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(torLocX, torLocY, torLocZ));
	//mMat *= glm::eulerAngleXYZ(toRadians(30.0f), 0.0f, 0.0f);
	mMat = glm::rotate(mMat, toRadians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	mvMat = vMat * mMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, brickTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW); //逆时针
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//glDrawArrays(GL_TRIANGLES, 0, myTorus.getNumIndices());

	//Elment 索引
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glDrawElements(GL_TRIANGLES, myTorus.getIndices().size(), GL_UNSIGNED_INT, 0);
}

void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
	aspect = (float)newWidth / (float)newHeight;
	glViewport(0, 0, newWidth, newHeight);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

int main(void) { // main()和之前的没有变化
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600,
			"Chapter 6 - program 2", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	glfwSetWindowSizeCallback(window, window_size_callback);
	init(window);

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
