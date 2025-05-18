// C++/OpenGL 应用程序
#include "Sphere.hpp"
#include "Utils.hpp"
#include "glm/fwd.hpp"
#include <vector>

using namespace std;

#define numVAOs 1
#define numVBOs 3
float cameraX, cameraY, cameraZ;
float sphLocX, sphLocY, sphLocZ;
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
//SphereModel
Sphere mySphere(48);

void setupVertices(void) { // 36个顶点，12个三角形，组成了放置在原点处的2×2×2立方体

	std::vector<int> ind = mySphere.getIndices();
	const auto& vert = mySphere.getVertices();
	const auto& tex = mySphere.getTexCoords();
	const auto& norm = mySphere.getNormals();

	//顶点位置
	std::vector<float> pvalues;
	//纹理坐标
	std::vector<float> tvalues;
	//法向量
	std::vector<float> nvalues;
	int numIndices = mySphere.getNumIndices(); //获取顶点数量

	for (int i = 0; i < numIndices; i++) {
		//position
		pvalues.push_back((vert[ind[i]]).x);
		pvalues.push_back((vert[ind[i]]).y);
		pvalues.push_back((vert[ind[i]]).z);

		//tex vec2用s,t来区分
		tvalues.push_back((tex[ind[i]]).s);
		tvalues.push_back((tex[ind[i]]).t);

		//normal
		nvalues.push_back((norm[ind[i]]).x);
		nvalues.push_back((norm[ind[i]]).y);
		nvalues.push_back((norm[ind[i]]).z);
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
}

void init(GLFWwindow* window) {
	renderingProgram = Utils::createShaderProgram(
			"Shader/Chapter6/Program1/vertShader.glsl",
			"Shader/Chapter6/Program1/fragShader.glsl");
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 2.0f;
	sphLocX = 0.0f;
	sphLocY = 0.0f;
	sphLocZ = -1.0f;
	setupVertices();

	//proj
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

	//LoadTexture
	// brickTexture = Utils::loadTexture(
	// 		"Assets/Textures/Chapter5/brick1.jpg");

	brickTexture = Utils::loadTexture(
			"Assets/Textures/Chapter6/earth.jpg");
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(sphLocX, sphLocY, sphLocZ));
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

	glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
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
			"Chapter 6 - program 1", NULL, NULL);
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
