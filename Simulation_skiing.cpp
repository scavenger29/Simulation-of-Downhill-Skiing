#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>
#include <common/texture.hpp>
#include<iostream>
GLFWwindow* window;

using namespace glm;
using namespace std;
class poses
{
public:
	poses()
	{
		Model_Torso = glm::mat4(1.0f);
		Model_Neck = glm::mat4(1.0f);
		Model_Shoulder = glm::mat4(1.0f);
		Model_LArm1 = glm::mat4(1.0f);
		Model_LArm2 = glm::mat4(1.0f);
		Model_RArm1 = glm::mat4(1.0f);
		Model_RArm2 = glm::mat4(1.0f);
		Model_Leg = glm::mat4(1.0f);
		Model_LLeg1 = glm::mat4(1.0f);
		Model_LLeg2 = glm::mat4(1.0f);
		Model_RLeg1 = glm::mat4(1.0f);
		Model_RLeg2 = glm::mat4(1.0f);
		Model_Ski1 = glm::mat4(1.0f);
		Model_Ski2 = glm::mat4(1.0f);
		Model_Pole1 = glm::mat4(1.0f);
		Model_Pole2 = glm::mat4(1.0f);

	}

	glm::mat4 Model_Torso;
	glm::mat4 Model_Neck;
	glm::mat4 Model_Shoulder;
	glm::mat4 Model_LArm1;
	glm::mat4 Model_LArm2;
	glm::mat4 Model_RArm1;
	glm::mat4 Model_RArm2;
	glm::mat4 Model_Leg;
	glm::mat4 Model_LLeg1;
	glm::mat4 Model_LLeg2;
	glm::mat4 Model_RLeg1;
	glm::mat4 Model_RLeg2;
	glm::mat4 Model_Ski1;
	glm::mat4 Model_Ski2;
	glm::mat4 Model_Pole1;
	glm::mat4 Model_Pole2;
};

class bezier
{
public:
	int n;
	int control_points[8][3];
};

long long factorial(long long n)
{
	if (n == 1)
		return 1;
	else
		return factorial(n - 1);
}

long long nCr(long long n, long long r)
{
	long long a = factorial(n);
	long long b = factorial(r)*factorial(n - r);
	return a / b;
}

void render(GLuint MatrixID, GLuint vertexbuffer, GLuint uvbuffer, glm::mat4 MVP, GLuint Texture, GLuint TextureID)
{
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(TextureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

int main(void)
{
	poses p1 = poses();
	poses p2 = poses();
	poses p3 = poses();
	poses p4 = poses();
	poses p5 = poses();
	bezier b1;
	b1.n = 7;
	b1.control_points[0][0] = 0; b1.control_points[0][1] = 0; b1.control_points[0][2] = -5;
	b1.control_points[1][0] = -8; b1.control_points[1][1] = 0; b1.control_points[1][2] = -8;
	b1.control_points[2][0] = -8; b1.control_points[2][1] = 0; b1.control_points[2][2] = -13;
	b1.control_points[3][0] = 0; b1.control_points[3][1] = 0; b1.control_points[3][2] = -16;
	b1.control_points[4][0] = 0; b1.control_points[4][1] = 0; b1.control_points[4][2] = -16;
	b1.control_points[5][0] = 8; b1.control_points[5][1] = 0; b1.control_points[5][2] = -19;
	b1.control_points[6][0] = 8; b1.control_points[6][1] = 0; b1.control_points[6][2] = -24;
	b1.control_points[7][0] = 0; b1.control_points[7][1] = 0; b1.control_points[7][2] = -27;

	int coeff[8] = { 1, 7, 21, 35, 35, 21, 7, 1 };


	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	
	//faltu initialization
	{
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		window = glfwCreateWindow(1024, 768, "Tutorial 04 - Colored Cube", NULL, NULL);
		if (window == NULL) {
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			getchar();
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);


		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			getchar();
			glfwTerminate();
			return -1;
		}


		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		glEnable(GL_DEPTH_TEST);

		glDepthFunc(GL_LESS);
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");


	GLuint Texture_Torso = loadBMP_custom("camo.bmp");
	GLuint Texture_Neck = loadBMP_custom("Dirt03.bmp");
	GLuint Texture_Arm = loadBMP_custom("bricks.bmp");
	GLuint Texture_Leg = loadBMP_custom("TEXTVRA.bmp");
	GLuint Texture_Equip = loadBMP_custom("futuresquare1.bmp");
	GLuint Texture = loadBMP_custom("paper.bmp");
	//GLuint Texture = loadDDS("Shirt.DDS");
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};


	static const GLfloat g_uv_buffer_data[] = {
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};


	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	glm::mat4 Model_Track = glm::mat4(1.0f);
	glm::mat4 Model_Torso = glm::mat4(1.0f);
	glm::mat4 Model_Neck = glm::mat4(1.0f);
	glm::mat4 Model_LLeg1 = glm::mat4(1.0f);
	glm::mat4 Model_LLeg2 = glm::mat4(1.0f);
	glm::mat4 Model_RLeg1 = glm::mat4(1.0f);
	glm::mat4 Model_RLeg2 = glm::mat4(1.0f);
	glm::mat4 Model_LArm1 = glm::mat4(1.0f);
	glm::mat4 Model_LArm2 = glm::mat4(1.0f);
	glm::mat4 Model_RArm1 = glm::mat4(1.0f);
	glm::mat4 Model_RArm2 = glm::mat4(1.0f);

	glm::mat4 Model_Ski1 = glm::mat4(1.0f);
	glm::mat4 Model_Ski2 = glm::mat4(1.0f);
	glm::mat4 Model_Pole1 = glm::mat4(1.0f);
	glm::mat4 Model_Pole2 = glm::mat4(1.0f);
	glm::mat4 Model_Flag1 = glm::mat4(1.0f);
	glm::mat4 Model_Flag2 = glm::mat4(1.0f);
	glm::mat4 Model_Flag3 = glm::mat4(1.0f);
	glm::mat4 Model_Flag4 = glm::mat4(1.0f);
	glm::mat4 Model_Flag5 = glm::mat4(1.0f);
	glm::mat4 Model_Flag6 = glm::mat4(1.0f);
	glm::mat4 Model_Flag7 = glm::mat4(1.0f);
	glm::mat4 Model_Flag8 = glm::mat4(1.0f);

	glm::mat4 MVP_Track;
	glm::mat4 MVP_Torso;
	glm::mat4 MVP_Neck ;
	glm::mat4 MVP_LLeg1;
	glm::mat4 MVP_LLeg2;
	glm::mat4 MVP_RLeg1;
	glm::mat4 MVP_RLeg2;
	glm::mat4 MVP_LArm1;
	glm::mat4 MVP_LArm2;
	glm::mat4 MVP_RArm1;
	glm::mat4 MVP_RArm2;

	glm::mat4 MVP_Ski1;
	glm::mat4 MVP_Ski2;
	glm::mat4 MVP_Pole1;
	glm::mat4 MVP_Pole2;
	glm::mat4 MVP_Flag1;
	glm::mat4 MVP_Flag2;
	glm::mat4 MVP_Flag3;
	glm::mat4 MVP_Flag4;
	glm::mat4 MVP_Flag5;
	glm::mat4 MVP_Flag6;
	glm::mat4 MVP_Flag7;
	glm::mat4 MVP_Flag8;

	glm::mat4 scaleMatrix;
	glm::mat4 translateMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 rotateMatrix_LLeg2;
	glm::mat4 rotateMatrix_LLeg1;
	glm::mat4 rotateMatrix_RLeg1;
	glm::mat4 rotateMatrix_RLeg2;
	glm::mat4 rotateMatrix_LArm2;
	glm::mat4 rotateMatrix_LArm1;
	glm::mat4 rotateMatrix_RArm2;
	glm::mat4 rotateMatrix_RArm1;
	glm::mat4 rotatePole1;
	glm::mat4 rotatePole2;


	glm::mat4 Projection = glm::perspective(glm::radians(150.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(5, 0,0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 0.1f, 100.0f));
	translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -4.5f, 0.0f));
	rotateMatrix = glm::rotate(glm::mat4(), glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
	Model_Track = rotateMatrix * translateMatrix * scaleMatrix * Model_Track;
	MVP_Track = Projection * View * Model_Track;

	//p1
	{
		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 1.5f, 0.6f));
		p1.Model_Torso = scaleMatrix * p1.Model_Torso;

		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.9f, 0.5f, 0.7f));
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 1.5f, 0.0f));
		p1.Model_Neck = translateMatrix * scaleMatrix * p1.Model_Neck;

		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
		p1.Model_LLeg1 = scaleMatrix * p1.Model_LLeg1;
		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.00f, 0.3f));
		rotateMatrix_LLeg2 = glm::rotate(glm::mat4(), glm::radians(-15.0f), glm::vec3(0.0, 0.0, 1.0));
		p1.Model_LLeg2 = rotateMatrix_LLeg2 * scaleMatrix * p1.Model_LLeg2;
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.2f, -1.5f, 0.0f));
		p1.Model_LLeg2 = translateMatrix * p1.Model_LLeg2;
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.35f, -2.0f, 0.2f));
		rotateMatrix_LLeg1 = glm::rotate(glm::mat4(), glm::radians(15.0f), glm::vec3(0.0, 0.0, 1.0));
		p1.Model_LLeg2 = translateMatrix * rotateMatrix_LLeg1 * p1.Model_LLeg2;
		p1.Model_LLeg1 = translateMatrix * rotateMatrix_LLeg1 * p1.Model_LLeg1;

		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
		p1.Model_RLeg1 = scaleMatrix * p1.Model_RLeg1;
		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.00f, 0.3f));
		rotateMatrix_RLeg2 = glm::rotate(glm::mat4(), glm::radians(15.0f), glm::vec3(0.0, 0.0, 1.0));
		p1.Model_RLeg2 = rotateMatrix_RLeg2 * scaleMatrix * p1.Model_RLeg2;
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.2f, -1.5f, 0.0f));
		p1.Model_RLeg2 = translateMatrix * p1.Model_RLeg2;
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.35f, -2.0f, 0.2f));
		rotateMatrix_RLeg1 = glm::rotate(glm::mat4(), glm::radians(-15.0f), glm::vec3(0.0, 0.0, 1.0));
		p1.Model_RLeg2 = translateMatrix * rotateMatrix_RLeg1 * p1.Model_RLeg2;
		p1.Model_RLeg1 = translateMatrix * rotateMatrix_RLeg1 * p1.Model_RLeg1;

		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
		p1.Model_LArm1 = scaleMatrix * p1.Model_LArm1;
		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.0f, 0.3f));
		rotateMatrix_LArm2 = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		p1.Model_LArm2 = rotateMatrix_LArm2 * scaleMatrix * p1.Model_LArm2;
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.65f, -0.45f, 0.0f));
		p1.Model_LArm2 = translateMatrix * p1.Model_LArm2;
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(1.0f, 0.7f, 0.2f));
		rotateMatrix_LArm1 = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		p1.Model_LArm2 = translateMatrix * rotateMatrix_LArm1 * p1.Model_LArm2;
		p1.Model_LArm1 = translateMatrix * rotateMatrix_LArm1 * p1.Model_LArm1;


		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
		p1.Model_RArm1 = scaleMatrix * p1.Model_RArm1;
		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.0f, 0.3f));
		rotateMatrix_RArm2 = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
		p1.Model_RArm2 = rotateMatrix_RArm2 * scaleMatrix * p1.Model_RArm2;
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.65f, -0.45f, 0.0f));
		p1.Model_RArm2 = translateMatrix * p1.Model_RArm2;
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(-1.0f, 0.7f, 0.2f));
		rotateMatrix_RArm1 = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
		p1.Model_RArm2 = translateMatrix * rotateMatrix_RArm1 * p1.Model_RArm2;
		p1.Model_RArm1 = translateMatrix * rotateMatrix_RArm1 * p1.Model_RArm1;

		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.000001f, 1.9f));
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.5f, -4.35f, 0.2f));
		p1.Model_Ski1 = translateMatrix * scaleMatrix * p1.Model_Ski1;

		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.000001f, 1.9f));
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.5f, -4.35f, 0.2f));
		p1.Model_Ski2 = translateMatrix * scaleMatrix * p1.Model_Ski2;

		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 1.8f, 0.1f));
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(1.6f, -2.4f, 0.2f));
		p1.Model_Pole1 = translateMatrix * scaleMatrix * p1.Model_Pole1;

		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 1.8f, 0.1f));
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(-1.6f, -2.4f, 0.2f));
		p1.Model_Pole2 = translateMatrix * scaleMatrix * p1.Model_Pole2;
	}
	
	//p2
	{
		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 1.5f, 0.6f));
		translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 1.5f, 0.0f));
		p2.Model_Torso = scaleMatrix * p2.Model_Torso;
		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.9f, 0.5f, 0.7f));
		p2.Model_Neck = translateMatrix * scaleMatrix * p2.Model_Neck;
		rotateMatrix = glm::rotate(glm::mat4(), glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		rotateMatrix_LArm1 = glm::rotate(glm::mat4(), glm::radians(50.0f), glm::vec3(0.0, 1.0, 0.0));
		rotateMatrix_RArm1 = glm::rotate(glm::mat4(), glm::radians(-50.0f), glm::vec3(0.0, 1.0, 0.0));
		p2.Model_Torso = rotateMatrix * p2.Model_Torso;
		p2.Model_Neck = rotateMatrix * p2.Model_Neck;
		p2.Model_LLeg1 = p1.Model_LLeg1;
		p2.Model_LLeg2 = p1.Model_LLeg2;
		p2.Model_RLeg1 = p1.Model_RLeg1;
		p2.Model_RLeg2 = p1.Model_RLeg2;
		p2.Model_LArm1 = rotateMatrix_LArm1 * rotateMatrix * p1.Model_LArm1;
		p2.Model_LArm2 = rotateMatrix_LArm1 * rotateMatrix * p1.Model_LArm2;
		p2.Model_RArm1 = rotateMatrix_RArm1 * rotateMatrix * p1.Model_RArm1;
		p2.Model_RArm2 = rotateMatrix_RArm1 * rotateMatrix * p1.Model_RArm2;
		p2.Model_Ski1 = p1.Model_Ski1;
		p2.Model_Ski2 = p1.Model_Ski2;
		p2.Model_Pole1 = rotateMatrix_LArm1 * rotateMatrix * p1.Model_Pole1;
		p2.Model_Pole2 = rotateMatrix_RArm1 * rotateMatrix * p1.Model_Pole2;
	}

	//p3
	{

		p3.Model_Torso = p2.Model_Torso;
		p3.Model_Neck = p2.Model_Neck;

		//LLeg
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));
			rotateMatrix_LLeg1 = glm::rotate(glm::mat4(), glm::radians(60.0f), glm::vec3(1.0, 0.0, 0.0));
			p3.Model_LLeg1 = rotateMatrix_LLeg1 * scaleMatrix * p3.Model_LLeg1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.00f, 0.3f));
			rotateMatrix_LLeg2 = glm::rotate(glm::mat4(), glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
			p3.Model_LLeg2 = rotateMatrix_LLeg2 * scaleMatrix * p3.Model_LLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -1.0f, -0.5f));
			p3.Model_LLeg2 = translateMatrix * p3.Model_LLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.35f, -1.5f, -0.5f));
			p3.Model_LLeg2 = translateMatrix * p3.Model_LLeg2;
			p3.Model_LLeg1 = translateMatrix * p3.Model_LLeg1;
		}

		//RLeg
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));
			rotateMatrix_RLeg1 = glm::rotate(glm::mat4(), glm::radians(60.0f), glm::vec3(1.0, 0.0, 0.0));
			p3.Model_RLeg1 = rotateMatrix_RLeg1 * scaleMatrix * p3.Model_RLeg1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.00f, 0.3f));
			rotateMatrix_RLeg2 = glm::rotate(glm::mat4(), glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
			p3.Model_RLeg2 = rotateMatrix_RLeg2 * scaleMatrix * p3.Model_RLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -1.0f, -0.5f));
			p3.Model_RLeg2 = translateMatrix * p3.Model_RLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.35f, -1.5f, -0.5f));
			p3.Model_RLeg2 = translateMatrix * p3.Model_RLeg2;
			p3.Model_RLeg1 = translateMatrix * p3.Model_RLeg1;
		}

		//LArm
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
			p3.Model_LArm1 = scaleMatrix * p3.Model_LArm1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.0f, 0.3f));
			rotateMatrix_LArm2 = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
			p3.Model_LArm2 = rotateMatrix_LArm2 * scaleMatrix * p3.Model_LArm2;
			rotateMatrix_LArm2 = glm::rotate(glm::mat4(), glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
			p3.Model_LArm2 = rotateMatrix_LArm2 * p3.Model_LArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -0.5f, -0.7f));
			p3.Model_LArm2 = translateMatrix * p3.Model_LArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(1.0f, 0.2f, -0.2f));
			rotateMatrix_LArm1 = glm::rotate(glm::mat4(), glm::radians(30.0f), glm::vec3(0.0, 0.0, 1.0));
			p3.Model_LArm2 = translateMatrix * rotateMatrix * rotateMatrix_LArm1 * p3.Model_LArm2;
			p3.Model_LArm1 = translateMatrix * rotateMatrix* rotateMatrix_LArm1 * p3.Model_LArm1;
		}

		//RArm
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
			p3.Model_RArm1 = scaleMatrix * p3.Model_RArm1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.0f, 0.3f));
			rotateMatrix_RArm2 = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
			p3.Model_RArm2 = rotateMatrix_RArm2 * scaleMatrix * p3.Model_RArm2;
			rotateMatrix_RArm2 = glm::rotate(glm::mat4(), glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
			p3.Model_RArm2 = rotateMatrix_RArm2 * p3.Model_RArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -0.5f, -0.7f));
			p3.Model_RArm2 = translateMatrix * p3.Model_RArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-1.0f, 0.2f, -0.2f));
			rotateMatrix_RArm1 = glm::rotate(glm::mat4(), glm::radians(-30.0f), glm::vec3(0.0, 0.0, 1.0));
			p3.Model_RArm2 = translateMatrix * rotateMatrix * rotateMatrix_RArm1 * p3.Model_RArm2;
			p3.Model_RArm1 = translateMatrix * rotateMatrix * rotateMatrix_RArm1 * p3.Model_RArm1;
		}

		//Ski
		{
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.1f, 0.8f, -0.8f));
			p3.Model_Ski1 = translateMatrix * p1.Model_Ski1;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.1f, 0.8f, -0.8f));
			p3.Model_Ski2 = translateMatrix * p1.Model_Ski2;
		}

		//Pole
		{
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.2f, 0.1f, -1.75f));
			p3.Model_Pole1 = translateMatrix * p1.Model_Pole1;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.2f, 0.1f, -1.75f));
			p3.Model_Pole2 = translateMatrix * p1.Model_Pole2;
		}
	}

	//p4
	{

		rotateMatrix = glm::rotate(glm::mat4(), glm::radians(-15.0f), glm::vec3(0.0, 0.0, 1.0));
		//torso
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 1.5f, 0.6f));
			p4.Model_Torso = rotateMatrix * scaleMatrix * p4.Model_Torso;
		}

		//neck
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.9f, 0.5f, 0.7f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 1.5f, 0.0f));
			p4.Model_Neck = rotateMatrix * translateMatrix * scaleMatrix * p4.Model_Neck;
		}

		//LLeg
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));
			rotateMatrix_LLeg1 = glm::rotate(glm::mat4(), glm::radians(60.0f), glm::vec3(1.0, 0.0, 0.0));
			p4.Model_LLeg1 = rotateMatrix_LLeg1 * scaleMatrix * p4.Model_LLeg1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.00f, 0.3f));
			rotateMatrix_LLeg2 = glm::rotate(glm::mat4(), glm::radians(-30.0f), glm::vec3(0.0, 0.0, 1.0));
			p4.Model_LLeg2 = rotateMatrix_LLeg2 * scaleMatrix * p4.Model_LLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.4f, -1.0f, -0.5f));
			p4.Model_LLeg2 = translateMatrix * p4.Model_LLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.35f, -1.5f, -0.5f));
			p4.Model_LLeg2 = rotateMatrix * translateMatrix * p4.Model_LLeg2;
			p4.Model_LLeg1 = rotateMatrix * translateMatrix * p4.Model_LLeg1;
		}

		//RLeg
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));
			rotateMatrix_RLeg1 = glm::rotate(glm::mat4(), glm::radians(60.0f), glm::vec3(1.0, 0.0, 0.0));
			p4.Model_RLeg1 = rotateMatrix_RLeg1 * scaleMatrix * p4.Model_RLeg1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.00f, 0.3f));
			rotateMatrix_RLeg2 = glm::rotate(glm::mat4(), glm::radians(-30.0f), glm::vec3(0.0, 0.0, 1.0));
			p4.Model_RLeg2 = rotateMatrix_RLeg2 * scaleMatrix * p4.Model_RLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.4f, -1.0f, -0.5f));
			p4.Model_RLeg2 = translateMatrix * p4.Model_RLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.35f, -1.5f, -0.5f));
			p4.Model_RLeg2 = rotateMatrix * translateMatrix * p4.Model_RLeg2;
			p4.Model_RLeg1 = rotateMatrix * translateMatrix * p4.Model_RLeg1;
		}


		//LArm
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
			p4.Model_LArm1 = scaleMatrix * p4.Model_LArm1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.0f, 0.3f));
			rotateMatrix_LArm2 = glm::rotate(glm::mat4(), glm::radians(120.0f), glm::vec3(0.0, 0.0, 1.0));
			p4.Model_LArm2 = rotateMatrix_LArm2 * scaleMatrix * p4.Model_LArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.65f, -0.7f, 0.0f));
			p4.Model_LArm2 = translateMatrix * p4.Model_LArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(1.0f, 0.7f, 0.2f));
			rotateMatrix_LArm1 = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
			p4.Model_LArm2 = rotateMatrix * translateMatrix * rotateMatrix_LArm1 * p4.Model_LArm2;
			p4.Model_LArm1 = rotateMatrix * translateMatrix * rotateMatrix_LArm1 * p4.Model_LArm1;
		}

		//RArm
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
			p4.Model_RArm1 = scaleMatrix * p4.Model_RArm1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.0f, 0.3f));
			rotateMatrix_RArm2 = glm::rotate(glm::mat4(), glm::radians(-120.0f), glm::vec3(0.0, 0.0, 1.0));
			p4.Model_RArm2 = rotateMatrix_RArm2 * scaleMatrix * p4.Model_RArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.55f, -0.75f, 0.0f));
			p4.Model_RArm2 = translateMatrix * p4.Model_RArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-1.0f, 0.7f, 0.2f));
			rotateMatrix_RArm1 = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
			p4.Model_RArm2 = rotateMatrix * translateMatrix * rotateMatrix_RArm1 * p4.Model_RArm2;
			p4.Model_RArm1 = rotateMatrix * translateMatrix * rotateMatrix_RArm1 * p4.Model_RArm1;
		}

		//ski
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.000001f, 1.9f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-1.2f, -3.2f, -0.2f));
			p4.Model_Ski1 = translateMatrix * rotateMatrix_LLeg2 * rotateMatrix * scaleMatrix * p4.Model_Ski1;

			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.000001f, 1.9f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-1.7f, -2.7f, -0.2f));
			p4.Model_Ski2 = translateMatrix * rotateMatrix_LLeg2 * rotateMatrix * scaleMatrix * p4.Model_Ski2;
		}

		//pole
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 1.8f, 0.1f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(1.6f, -2.4f, 0.2f));
			p4.Model_Pole1 = translateMatrix * rotateMatrix * scaleMatrix * p4.Model_Pole1;

			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 1.8f, 0.1f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-3.4f, -1.5f, 0.2f));
			rotatePole1 = glm::rotate(glm::mat4(), glm::radians(-30.0f), glm::vec3(0.0, 0.0, 1.0));
			p4.Model_Pole2 = translateMatrix * rotatePole1 * rotateMatrix * scaleMatrix * p4.Model_Pole2;
		}
	}

	{
	//kuch nahi :P
	}
	//p5
	{
		rotateMatrix = glm::rotate(glm::mat4(), glm::radians(15.0f), glm::vec3(0.0, 0.0, 1.0));
		//torso
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 1.5f, 0.6f));
			p5.Model_Torso = rotateMatrix * scaleMatrix * p5.Model_Torso;
		}

		//neck
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.9f, 0.5f, 0.7f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 1.5f, 0.0f));
			p5.Model_Neck = rotateMatrix * translateMatrix * scaleMatrix * p5.Model_Neck;
		}

		//LLeg
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));
			rotateMatrix_LLeg1 = glm::rotate(glm::mat4(), glm::radians(60.0f), glm::vec3(1.0, 0.0, 0.0));
			p5.Model_LLeg1 = rotateMatrix_LLeg1 * scaleMatrix * p5.Model_LLeg1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.00f, 0.3f));
			rotateMatrix_LLeg2 = glm::rotate(glm::mat4(), glm::radians(30.0f), glm::vec3(0.0, 0.0, 1.0));
			p5.Model_LLeg2 = rotateMatrix_LLeg2 * scaleMatrix * p5.Model_LLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.4f, -1.0f, -0.5f));
			p5.Model_LLeg2 = translateMatrix * p5.Model_LLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.35f, -1.5f, -0.5f));
			p5.Model_LLeg2 = rotateMatrix * translateMatrix * p5.Model_LLeg2;
			p5.Model_LLeg1 = rotateMatrix * translateMatrix * p5.Model_LLeg1;
		}

		//RLeg
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.8f, 0.3f));
			rotateMatrix_RLeg1 = glm::rotate(glm::mat4(), glm::radians(60.0f), glm::vec3(1.0, 0.0, 0.0));
			p5.Model_RLeg1 = rotateMatrix_RLeg1 * scaleMatrix * p5.Model_RLeg1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.00f, 0.3f));
			rotateMatrix_RLeg2 = glm::rotate(glm::mat4(), glm::radians(30.0f), glm::vec3(0.0, 0.0, 1.0));
			p5.Model_RLeg2 = rotateMatrix_RLeg2 * scaleMatrix * p5.Model_RLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.4f, -1.0f, -0.5f));
			p5.Model_RLeg2 = translateMatrix * p5.Model_RLeg2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.35f, -1.5f, -0.5f));
			p5.Model_RLeg2 = rotateMatrix * translateMatrix * p5.Model_RLeg2;
			p5.Model_RLeg1 = rotateMatrix * translateMatrix * p5.Model_RLeg1;
		}


		//LArm
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
			p5.Model_LArm1 = scaleMatrix * p5.Model_LArm1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.0f, 0.3f));
			rotateMatrix_LArm2 = glm::rotate(glm::mat4(), glm::radians(120.0f), glm::vec3(0.0, 0.0, 1.0));
			p5.Model_LArm2 = rotateMatrix_LArm2 * scaleMatrix * p5.Model_LArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-0.65f, -0.7f, 0.0f));
			p5.Model_LArm2 = translateMatrix * p5.Model_LArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(1.0f, 0.7f, 0.2f));
			rotateMatrix_LArm1 = glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
			p5.Model_LArm2 = rotateMatrix * translateMatrix * rotateMatrix_LArm1 * p5.Model_LArm2;
			p5.Model_LArm1 = rotateMatrix * translateMatrix * rotateMatrix_LArm1 * p5.Model_LArm1;
		}

		//RArm
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.8f, 0.3f));
			p5.Model_RArm1 = scaleMatrix * p5.Model_RArm1;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 1.0f, 0.3f));
			rotateMatrix_RArm2 = glm::rotate(glm::mat4(), glm::radians(-120.0f), glm::vec3(0.0, 0.0, 1.0));
			p5.Model_RArm2 = rotateMatrix_RArm2 * scaleMatrix * p5.Model_RArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.55f, -0.75f, 0.0f));
			p5.Model_RArm2 = translateMatrix * p5.Model_RArm2;
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-1.3f, 0.7f, 0.2f));
			rotateMatrix_RArm1 = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
			p5.Model_RArm2 = rotateMatrix * translateMatrix * rotateMatrix_RArm1 * p5.Model_RArm2;
			p5.Model_RArm1 = rotateMatrix * translateMatrix * rotateMatrix_RArm1 * p5.Model_RArm1;
		}

		//ski
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.000001f, 1.9f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(2.0f, -2.5f, -0.5f));
			p5.Model_Ski1 = translateMatrix * rotateMatrix_LLeg2 * rotateMatrix * scaleMatrix * p5.Model_Ski1;

			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.000001f, 1.9f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(1.45f, -3.0f, -0.5f));
			p5.Model_Ski2 = translateMatrix * rotateMatrix_LLeg2 * rotateMatrix * scaleMatrix * p5.Model_Ski2;
		}

		//pole
		{
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 1.8f, 0.1f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(3.7f, -1.2f, 0.2f));
			rotatePole1 = glm::rotate(glm::mat4(), glm::radians(30.0f), glm::vec3(0.0, 0.0, 1.0));
			p5.Model_Pole1 = translateMatrix * rotatePole1 * rotateMatrix * scaleMatrix * p5.Model_Pole1;

			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 1.8f, 0.1f));
			translateMatrix = glm::translate(glm::mat4(), glm::vec3(-2.8f, -2.4f, 0.2f));
			rotatePole1 = glm::rotate(glm::mat4(), glm::radians(-30.0f), glm::vec3(0.0, 0.0, 1.0));
			p5.Model_Pole2 = translateMatrix * rotatePole1 * rotateMatrix * scaleMatrix * p5.Model_Pole2;
		}
	
	}
	

	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.75f, 0.05f));
	translateMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, -3.5f, -6.0f));
	Model_Flag1 = translateMatrix * scaleMatrix * Model_Flag1;
	MVP_Flag1 = Projection * View * Model_Flag1;

	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.75f, 0.05f));
	translateMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, -3.5f, -30.0f));
	Model_Flag2 = translateMatrix * scaleMatrix * Model_Flag2;
	MVP_Flag2 = Projection * View * Model_Flag2;

	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 1.0f, 0.5f));
	translateMatrix = glm::translate(glm::mat4(), glm::vec3(3.0f, -3.5f, -50.0f));
	Model_Flag3 = translateMatrix * scaleMatrix * Model_Flag3;
	MVP_Flag3 = Projection * View * Model_Flag3;

	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 1.0f, 0.5f));
	translateMatrix = glm::translate(glm::mat4(), glm::vec3(30.0f, -3.5f, -205.0f));
	Model_Flag8 = translateMatrix * scaleMatrix * Model_Flag8;
	MVP_Flag8 = Projection * View * Model_Flag8;

	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.0f, 1.5f));
	translateMatrix = glm::translate(glm::mat4(), glm::vec3(-15.0f, -3.5f, -150.0f));
	Model_Flag7 = translateMatrix * scaleMatrix * Model_Flag7;
	MVP_Flag7 = Projection * View * Model_Flag7;

	glm::mat4 rotateflag = glm::rotate(glm::mat4(), glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
	int i = -400;
	float t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, t7=0, t8 =0,t9=0,  mov = -10;
	float trans_x = 0, trans_y = 0, trans_z = 0;
	float init_trans_z = -0.005, init_trans_x = -0.005, init_trans_y = 0.0;
	glm::mat4 myMatrix;

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		if (i < 2100)
		{
			if (i <= 200 || (i>=1200 && i<1700))
			{
				myMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, init_trans_z));
				trans_z += init_trans_z;
			}
			else if(i>200 || i<1200)
			{
				init_trans_z = init_trans_z - 0.00003;
				myMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, init_trans_z));
				trans_z += init_trans_z;
			}
			else if (i > 1700)
			{
				init_trans_z = init_trans_z + 0.00001;
				myMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, init_trans_z));
				trans_z += init_trans_z;
			}

			if (i == 100)
			{
				View = glm::lookAt(
					glm::vec3(5, 0, -5),
					glm::vec3(0, 0, 0),
					glm::vec3(0, 1, 0)
				);
			}
			if (i == 500)
			{
				View = glm::lookAt(
					glm::vec3(-5, 0, -20),
					glm::vec3(0, 0, -5),
					glm::vec3(0, 1, 0)
				);
			}
			if (i == 800)
			{
				View = glm::lookAt(
					glm::vec3(0, 0, -40),
					glm::vec3(0, 0, -30),
					glm::vec3(0, 1, 0)
				);
			}
			if (i == 1500)
			{
				View = glm::lookAt(
					glm::vec3(5, 0, -30),
					glm::vec3(0, 0, -50),
					glm::vec3(0, 1, 0)
				);
			}
			if (i == 1800)
			{
				View = glm::lookAt(
					glm::vec3(5, 0, -60),
					glm::vec3(0, 0, -50),
					glm::vec3(0, 1, 0)
				);
			}
			if (i == 1950)
			{
				View = glm::lookAt(
					glm::vec3(-5, 0,-70 ),
					glm::vec3(0, 0, -50),
					glm::vec3(0, 1, 0)
				);
			}

			if (i == 200)
			{
				
				translateMatrix = glm::translate(glm::mat4(), glm::vec3(3.0f, 3.5f, 6.0f));
				Model_Flag1 = rotateflag * translateMatrix * Model_Flag1;
				translateMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, -3.5f, -6.0f));
				Model_Flag1 = translateMatrix * Model_Flag1;
			}
			if (i == 1300)
			{
				translateMatrix = glm::translate(glm::mat4(), glm::vec3(3.0f, 3.5f, 30.0f));
				Model_Flag2 = rotateflag * translateMatrix * Model_Flag2;
				translateMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, -3.5f, -30.0f));
				Model_Flag2 = translateMatrix * Model_Flag2;
			}

			if (i == 2090)
			{
				translateMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, 3.5f, 50.0f));
				Model_Flag3 = rotateflag * translateMatrix * Model_Flag3;
				translateMatrix = glm::translate(glm::mat4(), glm::vec3(3.0f, -3.5f, -50.0f));
				Model_Flag3 = translateMatrix * Model_Flag3;
			}
			//basic translation
			{
				p1.Model_Torso = myMatrix * p1.Model_Torso;
				p1.Model_Neck = myMatrix * p1.Model_Neck;
				p1.Model_LLeg1 = myMatrix * p1.Model_LLeg1;
				p1.Model_LLeg2 = myMatrix * p1.Model_LLeg2;
				p1.Model_RLeg1 = myMatrix * p1.Model_RLeg1;
				p1.Model_RLeg2 = myMatrix * p1.Model_RLeg2;
				p1.Model_LArm1 = myMatrix * p1.Model_LArm1;
				p1.Model_LArm2 = myMatrix * p1.Model_LArm2;
				p1.Model_RArm1 = myMatrix * p1.Model_RArm1;
				p1.Model_RArm2 = myMatrix * p1.Model_RArm2;
				p1.Model_Ski1 = myMatrix * p1.Model_Ski1;
				p1.Model_Ski2 = myMatrix * p1.Model_Ski2;
				p1.Model_Pole1 = myMatrix * p1.Model_Pole1;
				p1.Model_Pole2 = myMatrix * p1.Model_Pole2;

				p2.Model_Torso = myMatrix * p2.Model_Torso;
				p2.Model_Neck = myMatrix * p2.Model_Neck;
				p2.Model_LLeg1 = myMatrix * p2.Model_LLeg1;
				p2.Model_LLeg2 = myMatrix * p2.Model_LLeg2;
				p2.Model_RLeg1 = myMatrix * p2.Model_RLeg1;
				p2.Model_RLeg2 = myMatrix * p2.Model_RLeg2;
				p2.Model_LArm1 = myMatrix * p2.Model_LArm1;
				p2.Model_LArm2 = myMatrix * p2.Model_LArm2;
				p2.Model_RArm1 = myMatrix * p2.Model_RArm1;
				p2.Model_RArm2 = myMatrix * p2.Model_RArm2;
				p2.Model_Ski1 = myMatrix * p2.Model_Ski1;
				p2.Model_Ski2 = myMatrix * p2.Model_Ski2;
				p2.Model_Pole1 = myMatrix * p2.Model_Pole1;
				p2.Model_Pole2 = myMatrix * p2.Model_Pole2;

				p3.Model_Torso = myMatrix * p3.Model_Torso;
				p3.Model_Neck = myMatrix * p3.Model_Neck;
				p3.Model_LLeg1 = myMatrix * p3.Model_LLeg1;
				p3.Model_LLeg2 = myMatrix * p3.Model_LLeg2;
				p3.Model_RLeg1 = myMatrix * p3.Model_RLeg1;
				p3.Model_RLeg2 = myMatrix * p3.Model_RLeg2;
				p3.Model_LArm1 = myMatrix * p3.Model_LArm1;
				p3.Model_LArm2 = myMatrix * p3.Model_LArm2;
				p3.Model_RArm1 = myMatrix * p3.Model_RArm1;
				p3.Model_RArm2 = myMatrix * p3.Model_RArm2;
				p3.Model_Ski1 = myMatrix * p3.Model_Ski1;
				p3.Model_Ski2 = myMatrix * p3.Model_Ski2;
				p3.Model_Pole1 = myMatrix * p3.Model_Pole1;
				p3.Model_Pole2 = myMatrix * p3.Model_Pole2;

				p4.Model_Torso = myMatrix * p4.Model_Torso;
				p4.Model_Neck = myMatrix * p4.Model_Neck;
				p4.Model_LLeg1 = myMatrix * p4.Model_LLeg1;
				p4.Model_LLeg2 = myMatrix * p4.Model_LLeg2;
				p4.Model_RLeg1 = myMatrix * p4.Model_RLeg1;
				p4.Model_RLeg2 = myMatrix * p4.Model_RLeg2;
				p4.Model_LArm1 = myMatrix * p4.Model_LArm1;
				p4.Model_LArm2 = myMatrix * p4.Model_LArm2;
				p4.Model_RArm1 = myMatrix * p4.Model_RArm1;
				p4.Model_RArm2 = myMatrix * p4.Model_RArm2;
				p4.Model_Ski1 = myMatrix * p4.Model_Ski1;
				p4.Model_Ski2 = myMatrix * p4.Model_Ski2;
				p4.Model_Pole1 = myMatrix * p4.Model_Pole1;
				p4.Model_Pole2 = myMatrix * p4.Model_Pole2;

				p5.Model_Torso = myMatrix * p5.Model_Torso;
				p5.Model_Neck = myMatrix * p5.Model_Neck;
				p5.Model_LLeg1 = myMatrix * p5.Model_LLeg1;
				p5.Model_LLeg2 = myMatrix * p5.Model_LLeg2;
				p5.Model_RLeg1 = myMatrix * p5.Model_RLeg1;
				p5.Model_RLeg2 = myMatrix * p5.Model_RLeg2;
				p5.Model_LArm1 = myMatrix * p5.Model_LArm1;
				p5.Model_LArm2 = myMatrix * p5.Model_LArm2;
				p5.Model_RArm1 = myMatrix * p5.Model_RArm1;
				p5.Model_RArm2 = myMatrix * p5.Model_RArm2;
				p5.Model_Ski1 = myMatrix * p5.Model_Ski1;
				p5.Model_Ski2 = myMatrix * p5.Model_Ski2;
				p5.Model_Pole1 = myMatrix * p5.Model_Pole1;
				p5.Model_Pole2 = myMatrix * p5.Model_Pole2;
			}

			//accelerating the skier
			if (i > 200 && i<1200 && i % 200 < 100)
			{
				t2 = 0;
				Model_Torso = (1.0f - t1)*p1.Model_Torso + (t1)*(p2.Model_Torso);
				Model_Neck = (1.0f - t1)*p1.Model_Neck + (t1)*(p2.Model_Neck);
				Model_LLeg1 = (1.0f - t1)*p1.Model_LLeg1 + (t1)*(p2.Model_LLeg1);
				Model_LLeg2 = (1.0f - t1)*p1.Model_LLeg2 + (t1)*(p2.Model_LLeg2);
				Model_RLeg1 = (1.0f - t1)*p1.Model_RLeg1 + (t1)*(p2.Model_RLeg1);
				Model_RLeg2 = (1.0f - t1)*p1.Model_RLeg2 + (t1)*(p2.Model_RLeg2);
				Model_LArm1 = (1.0f - t1)*p1.Model_LArm1 + (t1)*(p2.Model_LArm1);
				Model_LArm2 = (1.0f - t1)*p1.Model_LArm2 + (t1)*(p2.Model_LArm2);
				Model_RArm1 = (1.0f - t1)*p1.Model_RArm1 + (t1)*(p2.Model_RArm1);
				Model_RArm2 = (1.0f - t1)*p1.Model_RArm2 + (t1)*(p2.Model_RArm2);
				Model_Ski1 = (1.0f - t1)*p1.Model_Ski1 + (t1)*(p2.Model_Ski1);
				Model_Ski2 = (1.0f - t1)*p1.Model_Ski2 + (t1)*(p2.Model_Ski2);
				Model_Pole1 = (1.0f - t1)*p1.Model_Pole1 + (t1)*(p2.Model_Pole1);
				Model_Pole2 = (1.0f - t1)*p1.Model_Pole2 + (t1)*(p2.Model_Pole2);

				t1 = t1 + 0.01f;
			}
			else if (i > 200 && i<1200 && i % 200 > 99)
			{
				t1 = 0;
				Model_Torso = (1.0f - t2)*p2.Model_Torso + (t2)*(p1.Model_Torso);
				Model_Neck = (1.0f - t2)*p2.Model_Neck + (t2)*(p1.Model_Neck);
				Model_LLeg1 = (1.0f - t2)*p2.Model_LLeg1 + (t2)*(p1.Model_LLeg1);
				Model_LLeg2 = (1.0f - t2)*p2.Model_LLeg2 + (t2)*(p1.Model_LLeg2);
				Model_RLeg1 = (1.0f - t2)*p2.Model_RLeg1 + (t2)*(p1.Model_RLeg1);
				Model_RLeg2 = (1.0f - t2)*p2.Model_RLeg2 + (t2)*(p1.Model_RLeg2);
				Model_LArm1 = (1.0f - t2)*p2.Model_LArm1 + (t2)*(p1.Model_LArm1);
				Model_LArm2 = (1.0f - t2)*p2.Model_LArm2 + (t2)*(p1.Model_LArm2);
				Model_RArm1 = (1.0f - t2)*p2.Model_RArm1 + (t2)*(p1.Model_RArm1);
				Model_RArm2 = (1.0f - t2)*p2.Model_RArm2 + (t2)*(p1.Model_RArm2);
				Model_Ski1 = (1.0f - t2)*p2.Model_Ski1 + (t2)*(p1.Model_Ski1);
				Model_Ski2 = (1.0f - t2)*p2.Model_Ski2 + (t2)*(p1.Model_Ski2);
				Model_Pole1 = (1.0f - t2)*p2.Model_Pole1 + (t2)*(p1.Model_Pole1);
				Model_Pole2 = (1.0f - t2)*p2.Model_Pole2 + (t2)*(p1.Model_Pole2);

				t2 = t2 + 0.01f;
			}

			//normal p1 pose
			else if( i<=200 || (i>=1200 && i<=1300))
			{
				Model_Torso = p1.Model_Torso;
				Model_Neck = p1.Model_Neck;
				Model_LLeg1 = p1.Model_LLeg1;
				Model_LLeg2 = p1.Model_LLeg2;
				Model_RLeg1 = p1.Model_RLeg1;
				Model_RLeg2 = p1.Model_RLeg2;
				Model_LArm1 = p1.Model_LArm1;
				Model_LArm2 = p1.Model_LArm2;
				Model_RArm1 = p1.Model_RArm1;
				Model_RArm2 = p1.Model_RArm2;
				Model_Ski1 = p1.Model_Ski1;
				Model_Ski2 = p1.Model_Ski2;
				Model_Pole1 = p1.Model_Pole1;
				Model_Pole2 = p1.Model_Pole2;
			}

			// p1->p3 pose
			else if(i>1300 && i<1400)
			{
				Model_Torso = (1.0f - t3)*p1.Model_Torso + (t3)*(p3.Model_Torso);
				Model_Neck = (1.0f - t3)*p1.Model_Neck + (t3)*(p3.Model_Neck);
				Model_LLeg1 = (1.0f - t3)*p1.Model_LLeg1 + (t3)*(p3.Model_LLeg1);
				Model_LLeg2 = (1.0f - t3)*p1.Model_LLeg2 + (t3)*(p3.Model_LLeg2);
				Model_RLeg1 = (1.0f - t3)*p1.Model_RLeg1 + (t3)*(p3.Model_RLeg1);
				Model_RLeg2 = (1.0f - t3)*p1.Model_RLeg2 + (t3)*(p3.Model_RLeg2);
				Model_LArm1 = (1.0f - t3)*p1.Model_LArm1 + (t3)*(p3.Model_LArm1);
				Model_LArm2 = (1.0f - t3)*p1.Model_LArm2 + (t3)*(p3.Model_LArm2);
				Model_RArm1 = (1.0f - t3)*p1.Model_RArm1 + (t3)*(p3.Model_RArm1);
				Model_RArm2 = (1.0f - t3)*p1.Model_RArm2 + (t3)*(p3.Model_RArm2);
				Model_Ski1 = (1.0f - t3)*p1.Model_Ski1 + (t3)*(p3.Model_Ski1);
				Model_Ski2 = (1.0f - t3)*p1.Model_Ski2 + (t3)*(p3.Model_Ski2);
				Model_Pole1 = (1.0f - t3)*p1.Model_Pole1 + (t3)*(p3.Model_Pole1);
				Model_Pole2 = (1.0f - t3)*p1.Model_Pole2 + (t3)*(p3.Model_Pole2);

				t3 = t3 + 0.01f;
			}

			//p3 pose
			else if (i<2000)
			{
				Model_Torso = p3.Model_Torso;
				Model_Neck = p3.Model_Neck;
				Model_LLeg1 = p3.Model_LLeg1;
				Model_LLeg2 = p3.Model_LLeg2;
				Model_RLeg1 = p3.Model_RLeg1;
				Model_RLeg2 = p3.Model_RLeg2;
				Model_LArm1 = p3.Model_LArm1;
				Model_LArm2 = p3.Model_LArm2;
				Model_RArm1 = p3.Model_RArm1;
				Model_RArm2 = p3.Model_RArm2;
				Model_Ski1 = p3.Model_Ski1;
				Model_Ski2 = p3.Model_Ski2;
				Model_Pole1 = p3.Model_Pole1;
				Model_Pole2 = p3.Model_Pole2;
			}
			else if(i>2000)
			{
				Model_Torso = (1.0f - t5)*p3.Model_Torso + (t5)*(p5.Model_Torso);
				Model_Neck = (1.0f - t5)*p3.Model_Neck + (t5)*(p5.Model_Neck);
				Model_LLeg1 = (1.0f - t5)*p3.Model_LLeg1 + (t5)*(p5.Model_LLeg1);
				Model_LLeg2 = (1.0f - t5)*p3.Model_LLeg2 + (t5)*(p5.Model_LLeg2);
				Model_RLeg1 = (1.0f - t5)*p3.Model_RLeg1 + (t5)*(p5.Model_RLeg1);
				Model_RLeg2 = (1.0f - t5)*p3.Model_RLeg2 + (t5)*(p5.Model_RLeg2);
				Model_LArm1 = (1.0f - t5)*p3.Model_LArm1 + (t5)*(p5.Model_LArm1);
				Model_LArm2 = (1.0f - t5)*p3.Model_LArm2 + (t5)*(p5.Model_LArm2);
				Model_RArm1 = (1.0f - t5)*p3.Model_RArm1 + (t5)*(p5.Model_RArm1);
				Model_RArm2 = (1.0f - t5)*p3.Model_RArm2 + (t5)*(p5.Model_RArm2);
				Model_Ski1 = (1.0f - t5)*p3.Model_Ski1 + (t5)*(p5.Model_Ski1);
				Model_Ski2 = (1.0f - t5)*p3.Model_Ski2 + (t5)*(p5.Model_Ski2);
				Model_Pole1 = (1.0f - t5)*p3.Model_Pole1 + (t5)*(p5.Model_Pole1);
				Model_Pole2 = (1.0f - t5)*p3.Model_Pole2 + (t5)*(p5.Model_Pole2);

				t5 = t5 + 0.01;
			}

		}
		else if (i >= 2100 && i<5000)
		{
			if(i==2100)
				init_trans_z = -0.005;
			if (i == 2300)
			{
				View = glm::lookAt(
					glm::vec3(-15, 0, -65),
					glm::vec3(0, 0, -90),
					glm::vec3(0, 1, 0)
				);
			}

			if (i == 2700)
			{
				View = glm::lookAt(
					glm::vec3(-15, 0, -105),
					glm::vec3(0, 0, -80),
					glm::vec3(0, 1, 0)
				);
			}
			if (i == 3300)
			{
				View = glm::lookAt(
					glm::vec3(-5, 0, -110),
					glm::vec3(0, 0, -130),
					glm::vec3(0, 1, 0)
				);
			}
			
			if (i == 4000)
			{
				View = glm::lookAt(
					glm::vec3(20, 0, -210),
					glm::vec3(20, 0, -180),
					glm::vec3(0, 1, 0)
				);
			}

			if (i <= 2500)
			{	
				myMatrix = glm::translate(glm::mat4(), glm::vec3(init_trans_x, 0.0f, init_trans_z));
				init_trans_x += -0.00005;
				init_trans_z += -0.00005;
				trans_z += init_trans_z;
			}

			else if (i > 2500 && i < 3000)
			{
				myMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, init_trans_z));
				init_trans_x = 0.005;
				init_trans_z += -0.00005;
				trans_z += init_trans_z;
			}
			else if (i > 3000 && i < 4000)
			{
				myMatrix = glm::translate(glm::mat4(), glm::vec3(init_trans_x, 0.0f, init_trans_z));
				init_trans_x += 0.00005;
				init_trans_z += -0.00005;
				trans_z += init_trans_z;
			}
			else
			{
				myMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0.0f, init_trans_z));
				if(init_trans_z <0)
				init_trans_z += 0.0001;
				trans_z += init_trans_z;
			}
			//basic translation
			{
				p1.Model_Torso = myMatrix * p1.Model_Torso;
				p1.Model_Neck = myMatrix * p1.Model_Neck;
				p1.Model_LLeg1 = myMatrix * p1.Model_LLeg1;
				p1.Model_LLeg2 = myMatrix * p1.Model_LLeg2;
				p1.Model_RLeg1 = myMatrix * p1.Model_RLeg1;
				p1.Model_RLeg2 = myMatrix * p1.Model_RLeg2;
				p1.Model_LArm1 = myMatrix * p1.Model_LArm1;
				p1.Model_LArm2 = myMatrix * p1.Model_LArm2;
				p1.Model_RArm1 = myMatrix * p1.Model_RArm1;
				p1.Model_RArm2 = myMatrix * p1.Model_RArm2;
				p1.Model_Ski1 = myMatrix * p1.Model_Ski1;
				p1.Model_Ski2 = myMatrix * p1.Model_Ski2;
				p1.Model_Pole1 = myMatrix * p1.Model_Pole1;
				p1.Model_Pole2 = myMatrix * p1.Model_Pole2;

				p2.Model_Torso = myMatrix * p2.Model_Torso;
				p2.Model_Neck = myMatrix * p2.Model_Neck;
				p2.Model_LLeg1 = myMatrix * p2.Model_LLeg1;
				p2.Model_LLeg2 = myMatrix * p2.Model_LLeg2;
				p2.Model_RLeg1 = myMatrix * p2.Model_RLeg1;
				p2.Model_RLeg2 = myMatrix * p2.Model_RLeg2;
				p2.Model_LArm1 = myMatrix * p2.Model_LArm1;
				p2.Model_LArm2 = myMatrix * p2.Model_LArm2;
				p2.Model_RArm1 = myMatrix * p2.Model_RArm1;
				p2.Model_RArm2 = myMatrix * p2.Model_RArm2;
				p2.Model_Ski1 = myMatrix * p2.Model_Ski1;
				p2.Model_Ski2 = myMatrix * p2.Model_Ski2;
				p2.Model_Pole1 = myMatrix * p2.Model_Pole1;
				p2.Model_Pole2 = myMatrix * p2.Model_Pole2;

				p3.Model_Torso = myMatrix * p3.Model_Torso;
				p3.Model_Neck = myMatrix * p3.Model_Neck;
				p3.Model_LLeg1 = myMatrix * p3.Model_LLeg1;
				p3.Model_LLeg2 = myMatrix * p3.Model_LLeg2;
				p3.Model_RLeg1 = myMatrix * p3.Model_RLeg1;
				p3.Model_RLeg2 = myMatrix * p3.Model_RLeg2;
				p3.Model_LArm1 = myMatrix * p3.Model_LArm1;
				p3.Model_LArm2 = myMatrix * p3.Model_LArm2;
				p3.Model_RArm1 = myMatrix * p3.Model_RArm1;
				p3.Model_RArm2 = myMatrix * p3.Model_RArm2;
				p3.Model_Ski1 = myMatrix * p3.Model_Ski1;
				p3.Model_Ski2 = myMatrix * p3.Model_Ski2;
				p3.Model_Pole1 = myMatrix * p3.Model_Pole1;
				p3.Model_Pole2 = myMatrix * p3.Model_Pole2;

				p4.Model_Torso = myMatrix * p4.Model_Torso;
				p4.Model_Neck = myMatrix * p4.Model_Neck;
				p4.Model_LLeg1 = myMatrix * p4.Model_LLeg1;
				p4.Model_LLeg2 = myMatrix * p4.Model_LLeg2;
				p4.Model_RLeg1 = myMatrix * p4.Model_RLeg1;
				p4.Model_RLeg2 = myMatrix * p4.Model_RLeg2;
				p4.Model_LArm1 = myMatrix * p4.Model_LArm1;
				p4.Model_LArm2 = myMatrix * p4.Model_LArm2;
				p4.Model_RArm1 = myMatrix * p4.Model_RArm1;
				p4.Model_RArm2 = myMatrix * p4.Model_RArm2;
				p4.Model_Ski1 = myMatrix * p4.Model_Ski1;
				p4.Model_Ski2 = myMatrix * p4.Model_Ski2;
				p4.Model_Pole1 = myMatrix * p4.Model_Pole1;
				p4.Model_Pole2 = myMatrix * p4.Model_Pole2;

				p5.Model_Torso = myMatrix * p5.Model_Torso;
				p5.Model_Neck = myMatrix * p5.Model_Neck;
				p5.Model_LLeg1 = myMatrix * p5.Model_LLeg1;
				p5.Model_LLeg2 = myMatrix * p5.Model_LLeg2;
				p5.Model_RLeg1 = myMatrix * p5.Model_RLeg1;
				p5.Model_RLeg2 = myMatrix * p5.Model_RLeg2;
				p5.Model_LArm1 = myMatrix * p5.Model_LArm1;
				p5.Model_LArm2 = myMatrix * p5.Model_LArm2;
				p5.Model_RArm1 = myMatrix * p5.Model_RArm1;
				p5.Model_RArm2 = myMatrix * p5.Model_RArm2;
				p5.Model_Ski1 = myMatrix * p5.Model_Ski1;
				p5.Model_Ski2 = myMatrix * p5.Model_Ski2;
				p5.Model_Pole1 = myMatrix * p5.Model_Pole1;
				p5.Model_Pole2 = myMatrix * p5.Model_Pole2;
			}
			if (i < 2500)
			{
				Model_Torso = p5.Model_Torso;
				Model_Neck = p5.Model_Neck;
				Model_LLeg1 = p5.Model_LLeg1;
				Model_LLeg2 = p5.Model_LLeg2;
				Model_RLeg1 = p5.Model_RLeg1;
				Model_RLeg2 = p5.Model_RLeg2;
				Model_LArm1 = p5.Model_LArm1;
				Model_LArm2 = p5.Model_LArm2;
				Model_RArm1 = p5.Model_RArm1;
				Model_RArm2 = p5.Model_RArm2;
				Model_Ski1 = p5.Model_Ski1;
				Model_Ski2 = p5.Model_Ski2;
				Model_Pole1 = p5.Model_Pole1;
				Model_Pole2 = p5.Model_Pole2;
			}
			else if (i > 2500 && i < 2700)
			{
				Model_Torso = (1.0f - t6)*p5.Model_Torso + (t6)*(p1.Model_Torso);
				Model_Neck = (1.0f - t6)*p5.Model_Neck + (t6)*(p1.Model_Neck);
				Model_LLeg1 = (1.0f - t6)*p5.Model_LLeg1 + (t6)*(p1.Model_LLeg1);
				Model_LLeg2 = (1.0f - t6)*p5.Model_LLeg2 + (t6)*(p1.Model_LLeg2);
				Model_RLeg1 = (1.0f - t6)*p5.Model_RLeg1 + (t6)*(p1.Model_RLeg1);
				Model_RLeg2 = (1.0f - t6)*p5.Model_RLeg2 + (t6)*(p1.Model_RLeg2);
				Model_LArm1 = (1.0f - t6)*p5.Model_LArm1 + (t6)*(p1.Model_LArm1);
				Model_LArm2 = (1.0f - t6)*p5.Model_LArm2 + (t6)*(p1.Model_LArm2);
				Model_RArm1 = (1.0f - t6)*p5.Model_RArm1 + (t6)*(p1.Model_RArm1);
				Model_RArm2 = (1.0f - t6)*p5.Model_RArm2 + (t6)*(p1.Model_RArm2);
				Model_Ski1 = (1.0f - t6)*p5.Model_Ski1 + (t6)*(p1.Model_Ski1);
				Model_Ski2 = (1.0f - t6)*p5.Model_Ski2 + (t6)*(p1.Model_Ski2);
				Model_Pole1 = (1.0f - t6)*p5.Model_Pole1 + (t6)*(p1.Model_Pole1);
				Model_Pole2 = (1.0f - t6)*p5.Model_Pole2 + (t6)*(p1.Model_Pole2);
				t6 += 0.005;

			}
			else if( i>2700 && i<3000)
			{
				Model_Torso = p1.Model_Torso;
				Model_Neck = p1.Model_Neck;
				Model_LLeg1 = p1.Model_LLeg1;
				Model_LLeg2 = p1.Model_LLeg2;
				Model_RLeg1 = p1.Model_RLeg1;
				Model_RLeg2 = p1.Model_RLeg2;
				Model_LArm1 = p1.Model_LArm1;
				Model_LArm2 = p1.Model_LArm2;
				Model_RArm1 = p1.Model_RArm1;
				Model_RArm2 = p1.Model_RArm2;
				Model_Ski1 = p1.Model_Ski1;
				Model_Ski2 = p1.Model_Ski2;
				Model_Pole1 = p1.Model_Pole1;
				Model_Pole2 = p1.Model_Pole2;
			}
			else if (i > 3000 && i < 3200)
			{
				Model_Torso = (1.0f - t7)*p1.Model_Torso + (t7)*(p4.Model_Torso);
				Model_Neck = (1.0f - t7)*p1.Model_Neck + (t7)*(p4.Model_Neck);
				Model_LLeg1 = (1.0f - t7)*p1.Model_LLeg1 + (t7)*(p4.Model_LLeg1);
				Model_LLeg2 = (1.0f - t7)*p1.Model_LLeg2 + (t7)*(p4.Model_LLeg2);
				Model_RLeg1 = (1.0f - t7)*p1.Model_RLeg1 + (t7)*(p4.Model_RLeg1);
				Model_RLeg2 = (1.0f - t7)*p1.Model_RLeg2 + (t7)*(p4.Model_RLeg2);
				Model_LArm1 = (1.0f - t7)*p1.Model_LArm1 + (t7)*(p4.Model_LArm1);
				Model_LArm2 = (1.0f - t7)*p1.Model_LArm2 + (t7)*(p4.Model_LArm2);
				Model_RArm1 = (1.0f - t7)*p1.Model_RArm1 + (t7)*(p4.Model_RArm1);
				Model_RArm2 = (1.0f - t7)*p1.Model_RArm2 + (t7)*(p4.Model_RArm2);
				Model_Ski1 = (1.0f - t7)*p1.Model_Ski1 + (t7)*(p4.Model_Ski1);
				Model_Ski2 = (1.0f - t7)*p1.Model_Ski2 + (t7)*(p4.Model_Ski2);
				Model_Pole1 = (1.0f - t7)*p1.Model_Pole1 + (t7)*(p4.Model_Pole1);
				Model_Pole2 = (1.0f - t7)*p1.Model_Pole2 + (t7)*(p4.Model_Pole2);

				t7 += 0.005;
			}
			else if (i > 3200 && i < 3500)
			{
				Model_Torso = p4.Model_Torso;
				Model_Neck = p4.Model_Neck;
				Model_LLeg1 = p4.Model_LLeg1;
				Model_LLeg2 = p4.Model_LLeg2;
				Model_RLeg1 = p4.Model_RLeg1;
				Model_RLeg2 = p4.Model_RLeg2;
				Model_LArm1 = p4.Model_LArm1;
				Model_LArm2 = p4.Model_LArm2;
				Model_RArm1 = p4.Model_RArm1;
				Model_RArm2 = p4.Model_RArm2;
				Model_Ski1 = p4.Model_Ski1;
				Model_Ski2 = p4.Model_Ski2;
				Model_Pole1 = p4.Model_Pole1;
				Model_Pole2 = p4.Model_Pole2;
			}
			else if (i > 3500 && i < 3700)
			{
				Model_Torso = (1.0f - t8)*p4.Model_Torso + (t8)*(p3.Model_Torso);
				Model_Neck = (1.0f - t8)*p4.Model_Neck + (t8)*(p3.Model_Neck);
				Model_LLeg1 = (1.0f - t8)*p4.Model_LLeg1 + (t8)*(p3.Model_LLeg1);
				Model_LLeg2 = (1.0f - t8)*p4.Model_LLeg2 + (t8)*(p3.Model_LLeg2);
				Model_RLeg1 = (1.0f - t8)*p4.Model_RLeg1 + (t8)*(p3.Model_RLeg1);
				Model_RLeg2 = (1.0f - t8)*p4.Model_RLeg2 + (t8)*(p3.Model_RLeg2);
				Model_LArm1 = (1.0f - t8)*p4.Model_LArm1 + (t8)*(p3.Model_LArm1);
				Model_LArm2 = (1.0f - t8)*p4.Model_LArm2 + (t8)*(p3.Model_LArm2);
				Model_RArm1 = (1.0f - t8)*p4.Model_RArm1 + (t8)*(p3.Model_RArm1);
				Model_RArm2 = (1.0f - t8)*p4.Model_RArm2 + (t8)*(p3.Model_RArm2);
				Model_Ski1 = (1.0f - t8)*p4.Model_Ski1 + (t8)*(p3.Model_Ski1);
				Model_Ski2 = (1.0f - t8)*p4.Model_Ski2 + (t8)*(p3.Model_Ski2);
				Model_Pole1 = (1.0f - t8)*p4.Model_Pole1 + (t8)*(p3.Model_Pole1);
				Model_Pole2 = (1.0f - t8)*p4.Model_Pole2 + (t8)*(p3.Model_Pole2);

				t8 += 0.005;
			}
			else if (i > 3700 && i<4600)
			{
				Model_Torso = p3.Model_Torso;
				Model_Neck = p3.Model_Neck;
				Model_LLeg1 = p3.Model_LLeg1;
				Model_LLeg2 = p3.Model_LLeg2;
				Model_RLeg1 = p3.Model_RLeg1;
				Model_RLeg2 = p3.Model_RLeg2;
				Model_LArm1 = p3.Model_LArm1;
				Model_LArm2 = p3.Model_LArm2;
				Model_RArm1 = p3.Model_RArm1;
				Model_RArm2 = p3.Model_RArm2;
				Model_Ski1 = p3.Model_Ski1;
				Model_Ski2 = p3.Model_Ski2;
				Model_Pole1 = p3.Model_Pole1;
				Model_Pole2 = p3.Model_Pole2;
			}
			else if (i > 4600)
			{
				Model_Torso = (1.0f - t9)*p3.Model_Torso + (t9)*(p1.Model_Torso);
				Model_Neck = (1.0f - t9)*p3.Model_Neck + (t9)*(p1.Model_Neck);
				Model_LLeg1 = (1.0f - t9)*p3.Model_LLeg1 + (t9)*(p1.Model_LLeg1);
				Model_LLeg2 = (1.0f - t9)*p3.Model_LLeg2 + (t9)*(p1.Model_LLeg2);
				Model_RLeg1 = (1.0f - t9)*p3.Model_RLeg1 + (t9)*(p1.Model_RLeg1);
				Model_RLeg2 = (1.0f - t9)*p3.Model_RLeg2 + (t9)*(p1.Model_RLeg2);
				Model_LArm1 = (1.0f - t9)*p3.Model_LArm1 + (t9)*(p1.Model_LArm1);
				Model_LArm2 = (1.0f - t9)*p3.Model_LArm2 + (t9)*(p1.Model_LArm2);
				Model_RArm1 = (1.0f - t9)*p3.Model_RArm1 + (t9)*(p1.Model_RArm1);
				Model_RArm2 = (1.0f - t9)*p3.Model_RArm2 + (t9)*(p1.Model_RArm2);
				Model_Ski1 = (1.0f - t9)*p3.Model_Ski1 + (t9)*(p1.Model_Ski1);
				Model_Ski2 = (1.0f - t9)*p3.Model_Ski2 + (t9)*(p1.Model_Ski2);
				Model_Pole1 = (1.0f - t9)*p3.Model_Pole1 + (t9)*(p1.Model_Pole1);
				Model_Pole2 = (1.0f - t9)*p3.Model_Pole2 + (t9)*(p1.Model_Pole2);

				t9 += 0.0025;
			}

			if (i == 4900)
			{
				translateMatrix = glm::translate(glm::mat4(), glm::vec3(-30.0f, 3.5f, 205.0f));
				Model_Flag8 = rotateflag * translateMatrix * Model_Flag8;
				translateMatrix = glm::translate(glm::mat4(), glm::vec3(30.0f, -3.5f, -205.0f));
				Model_Flag8 = translateMatrix * Model_Flag8;
			}
		}
		i++;
		MVP_Torso = Projection * View * Model_Torso;
		MVP_Neck = Projection * View * Model_Neck;
		MVP_LLeg1 = Projection * View * Model_LLeg1;
		MVP_LLeg2 = Projection * View * Model_LLeg2;
		MVP_RLeg1 = Projection * View * Model_RLeg1;
		MVP_RLeg2 = Projection * View * Model_RLeg2;
		MVP_LArm1 = Projection * View * Model_LArm1;
		MVP_LArm2 = Projection * View * Model_LArm2;
		MVP_RArm1 = Projection * View * Model_RArm1;
		MVP_RArm2 = Projection * View * Model_RArm2;

		MVP_Ski1 = Projection * View * Model_Ski1;
		MVP_Ski2 = Projection * View * Model_Ski2;
		MVP_Pole1 = Projection * View * Model_Pole1;
		MVP_Pole2 = Projection * View * Model_Pole2;
		MVP_Flag1 = Projection * View * Model_Flag1;
		MVP_Flag2 = Projection * View * Model_Flag2;
		MVP_Flag3 = Projection * View * Model_Flag3;
		MVP_Flag8 = Projection * View * Model_Flag8;
		//MVP_Flag7 = Projection * View * Model_Flag7;
		//MVP_Flag1 = Projection * View * Model_Flag4;
		
		render(MatrixID, vertexbuffer, uvbuffer, MVP_Torso, Texture_Torso, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_Neck, Texture_Neck, TextureID);

		render(MatrixID, vertexbuffer, uvbuffer, MVP_LLeg1, Texture_Leg, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_LLeg2, Texture_Leg, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_RLeg1, Texture_Leg, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_RLeg2, Texture_Leg, TextureID);

		render(MatrixID, vertexbuffer, uvbuffer, MVP_LArm1, Texture_Arm, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_LArm2, Texture_Arm, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_RArm1, Texture_Arm, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_RArm2, Texture_Arm, TextureID);

		render(MatrixID, vertexbuffer, uvbuffer, MVP_Ski1, Texture_Equip, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_Ski2, Texture_Equip, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_Pole1, Texture_Equip, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_Pole2, Texture_Equip, TextureID);

		render(MatrixID, vertexbuffer, uvbuffer, MVP_Flag1, Texture_Equip, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_Flag2, Texture_Equip, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_Flag3, Texture_Equip, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_Flag8, Texture_Equip, TextureID);
		render(MatrixID, vertexbuffer, uvbuffer, MVP_Track, Texture, TextureID);

		glfwSwapBuffers(window);
		glfwPollEvents();
		//cout << Model_Torso[3][0] << endl << Model_Torso[3][1] << endl << Model_Torso[3][2] << endl;
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}

