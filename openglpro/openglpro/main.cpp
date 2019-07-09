//link https://learnopengl-cn.github.io/


#include <iostream>
#include<vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"stb_image.h"

#include<glm\glm\gtc\matrix_transform.hpp>
#include<glm/glm/glm.hpp>
#include<glm\glm\gtc\type_ptr.hpp>


#include"Shader.h"
#include"Camera.h"
#include"objTriangle.h"
#include"objCube.h"
#include"objLight.h"
#include"glBindTool.h"
using namespace std;

void processInput();	 //输入控制
void initWindow();//初始化窗口

void framebuffer_size_callback(GLFWwindow* window, int width, int height);	 //窗口大小变化回调
void glcursorPosCallback(GLFWwindow* window, double xpos, double ypos);      //鼠标位置回调
void glScrollCallback(GLFWwindow* window, double xoffset, double yoffset);   //鼠标滚轮回调
glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp); //自定义lookat matrix

void processObj1(vector<objBase> objs);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLFWwindow* window;
Camera camera;
objLight light;

float lastX, lastY;
bool firstMouse = true;
float deltaTime, lastTime;


int main() {

	 initWindow(); //初始化窗口,回调事件

	camera = Camera(glm::vec3(0.0f, 0.0f, 6.0f)); //创建相机

	light=objLight(glm::vec3(0.0f, 0.0, -2));
	light.color = glm::vec4(1);
	light.material = objBase::Material{
		glm::vec3(1),
		glm::vec3(1),
		glm::vec3(1),
		32
	};
	light.isDirection = false;

	light.name = "light";
	//light.setShader("vert.glsl", "light_frag.glsl");
	//light.shader = Shader(light.vs, light.fs);
	//light.genVertex();
	//light.setScale(0.5f);
	//light.processTexture("light1.jpg", &light.texture1, false);
	//light.processTexture("light2.jpg", &light.texture2, false);
	vector<objBase> objs;

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -5.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -2.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	for (size_t i = 0; i < 10; i++)
	{
		objCube cube= objCube(cubePositions[i]);  //创建一个cube
		cube.setShader("res/vert.glsl", "res/fragsportlight.glsl");
		cube.genVertex();
		cube.setScale(1);
		cube.processTexture("res/container2.png", &cube.texture1, true);
		cube.processTexture("res/container2_specular.png", &cube.texture2, true);
		cube.processTexture("res/matrix.jpg", &cube.texture3, false);

		cube.shader = Shader(cube.vs, cube.fs);
		cube.name = "cube";
		cube.color = glm::vec4(1, 1, 1, 1);
		cube.material = objBase::Material{
			glm::vec3(0.0f, 0.1f, 0.06f),
			glm::vec3(0.0f, 0.50980392f, 0.50980392f),
			glm::vec3(0.50196078f, 0.50196078f, 0.50196078f),
		/*	glm::vec3(1),
			glm::vec3(1),
			glm::vec3(1),*/
			32
		};

		objs.push_back(cube);
	}

	processObj1(objs);   //渲染

	glfwTerminate();//回收资源
	return 0;
}
void processObj1(vector<objBase> objs) {
	
	//渲染循环
	while (!glfwWindowShouldClose(window)) {

		processInput();	//输入							

		glClearColor(0.2, 0.1, 0.1, 1);    //清除颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓存和深度缓存
	
		for (size_t i = 0; i < objs.size(); i++)
		{			
			objs[i].shader.use();

			glm::mat4 model;
			model = glm::translate(model, objs[i].postion);
			model = glm::rotate(model, glm::radians((float)glfwGetTime()*5.0f*(i + 1)), objs[i].postion);
			model = glm::scale(model, objs[i].scale);
			objs[i].shader.setMatri4("model", model);   //模型矩阵


			glm::mat4 view;
			view = camera.GetViewMatrix();
			objs[i].shader.setMatri4("view", view);     //观察矩阵
			objs[i].shader.setVec3("viewPos", camera.cameraPos.x,camera.cameraPos.y,camera.cameraPos.z );

			glm::mat4	projection = camera.GetProjectionMatrix();
			objs[i].shader.setMatri4("projection", projection);  //投影矩阵

			
			objs[i].shader.setInt("material.diffuseTex", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, objs[i].texture1);

			objs[i].shader.setInt("material.specularTex", 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, objs[i].texture2);

			objs[i].shader.setInt("material.emissionTex", 2);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, objs[i].texture3);

		
			objs[i].shader.setVec3("material.color", objs[i].color.r, objs[i].color.g, objs[i].color.b);
			objs[i].shader.setVec3("material.ambient", objs[i].material.ambient.r, objs[i].material.ambient.g, objs[i].material.ambient.b);
			objs[i].shader.setVec3("material.diffuse", objs[i].material.diffuse.r, objs[i].material.diffuse.g, objs[i].material.diffuse.b);
			objs[i].shader.setVec3("material.specular", objs[i].material.specular.r, objs[i].material.specular.g, objs[i].material.specular.b);
			objs[i].shader.setFloat("material.shiness", objs[i].material.shiness);

			//light.setPos(glm::vec3(0, -5, sin(glfwGetTime()) * 10.0f));
			if (true)
			{
				//聚光灯
				objs[i].shader.setVec4("light.position", camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z, 1);
				objs[i].shader.setVec3("light.direction", camera.front.x, camera.front.y, camera.front.z);
				objs[i].shader.setFloat("light.cutoff", glm::cos(glm::radians(6.5)));
				objs[i].shader.setFloat("light.outcutoff", glm::cos(glm::radians(10.5)));
			}
			else
			{
				if (light.isDirection)
				{
					objs[i].shader.setVec4("light.position", light.postion.x, light.postion.y, light.postion.z, 0);
				}
				else
				{
					objs[i].shader.setVec4("light.position", light.postion.x, light.postion.y, light.postion.z, 1.0);
				}
			}
		


			objs[i].shader.setVec3("light.color",light.color.r, light.color.g, light.color.b);
			objs[i].shader.setVec3("light.ambient", light.material.ambient.r, light.material.ambient.g, light.material.ambient.b);
			objs[i].shader.setVec3("light.diffuse", light.material.diffuse.r, light.material.diffuse.g, light.material.diffuse.b);
			objs[i].shader.setVec3("light.specular", light.material.specular.r, light.material.specular.g, light.material.specular.b);
			objs[i].shader.setFloat("light.constant", 1);
			objs[i].shader.setFloat("light.linear", 0.09f);
			objs[i].shader.setFloat("light.quadratic", 0.03f);
			glBindVertexArray(objs[i].VAO);
			glDrawArrays(GL_TRIANGLES, 0, objs[i].vertCount);  //画顶点
		
		}

		glfwSwapBuffers(window);//交换缓冲,绘制
		glfwPollEvents();//检查事件
	}

	for (size_t i = 0; i < objs.size(); i++) {
		/*glDeleteVertexArrays(1, &objs[i].VAO);
		glDeleteBuffers(1, &objs[i].VBO);*/
	}



}



void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);//设置视口
}

void processInput( ) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	float now = glfwGetTime();
	deltaTime = now - lastTime;
	lastTime = now;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void initWindow() {
	glfwInit();//初始化glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置major api
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置minor api
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);//创建窗口
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {//初始化opengl
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//设置窗口大小改变时回调,改变视口大小

	glEnable(GL_DEPTH_TEST);
	glfwSetCursorPosCallback(window, glcursorPosCallback);
	glfwSetScrollCallback(window, glScrollCallback);
}


void glcursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);

}

void glScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// Custom implementation of the LookAt function
glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	// 1. Position = known
	// 2. Calculate cameraDirection
	glm::vec3 zaxis = glm::normalize(position - target);
	// 3. Get positive right axis vector
	glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
	// 4. Calculate camera up vector
	glm::vec3 yaxis = glm::cross(zaxis, xaxis);

	// Create translation and rotation matrix
	// In glm we access elements as mat[col][row] due to column-major layout
	glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
	translation[3][0] = -position.x; // Third column, first row
	translation[3][1] = -position.y;
	translation[3][2] = -position.z;
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = xaxis.x; // First column, first row
	rotation[1][0] = xaxis.y;
	rotation[2][0] = xaxis.z;
	rotation[0][1] = yaxis.x; // First column, second row
	rotation[1][1] = yaxis.y;
	rotation[2][1] = yaxis.z;
	rotation[0][2] = zaxis.x; // First column, third row
	rotation[1][2] = zaxis.y;
	rotation[2][2] = zaxis.z;

	// Return lookAt matrix as combination of translation and rotation matrix
	return rotation * translation; // Remember to read from right to left (first translation then rotation)
}



