//link https://learnopengl-cn.github.io/


#include <iostream>
#include<vector>
#include<string.h>

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
#include"objSportLight.h"
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
objLight* dirLight;
objLight* pointLight;
const int POINT_LIGHTS = 4;
objSportLight* sportLight;
bool openSportLight;

float lastX, lastY;
bool firstMouse = true;
float deltaTime, lastTime;


int main() {

	 initWindow(); //初始化窗口,回调事件

	camera = Camera(glm::vec3(0.0f, 0.0f, 6.0f)); //创建相机

	dirLight =new objLight(glm::vec3(0.0f, -2.0, -2));
	dirLight->color = glm::vec4(1);
	dirLight->material.ambient = glm::vec3(1);
	dirLight->material.diffuse = glm::vec3(1);
	dirLight->material.specular = glm::vec3(1);
	dirLight->isDirection = true;

	pointLight = new objLight[POINT_LIGHTS]{
		 objLight(glm::vec3(0.0f, -.0, -2)),
		 objLight(glm::vec3(0.0f, -2.0, -4)),
		 objLight(glm::vec3(0.0f, -4.0, -6)),
		 objLight(glm::vec3(0.0f, -6.0, -7)),
	};
	for (size_t i = 0; i < POINT_LIGHTS; i++)
	{
		auto plight =&pointLight[i];
		plight->color = glm::vec4(1);
		plight->material.ambient = glm::vec3(1);
		plight->material.diffuse = glm::vec3(1);
		plight->material.specular = glm::vec3(1);
		plight->isDirection = false;
		plight->genVertex();
		plight->setScale(0.5);
		plight->setShader("res/vert.glsl", "res/fragforlight.glsl");
	}
	

	sportLight=new objSportLight();

	sportLight->color = glm::vec4(1);
	sportLight->material.ambient = glm::vec3(1);
	sportLight->material.diffuse = glm::vec3(1);
	sportLight->material.specular = glm::vec3(1);
	sportLight->isDirection = false;
	sportLight->cutoff = 5;
	sportLight->outCutOff = 10;

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
		cube.setShader("res/vert.glsl", "res/frag_lights.glsl");
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

		glClearColor(0.7, 0.5, 0.1, 1);    //清除颜色
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
			
			if (dirLight!=NULL)
			{
				objs[i].shader.setVec4("dirlight.position", dirLight->postion.x, dirLight->postion.y, dirLight->postion.z, 0);
				objs[i].shader.setVec3("dirlight.color", dirLight->color.r, dirLight->color.g, dirLight->color.b);
				objs[i].shader.setVec3("dirlight.ambient", dirLight->material.ambient.r, dirLight->material.ambient.g, dirLight->material.ambient.b);
				objs[i].shader.setVec3("dirlight.diffuse", dirLight->material.diffuse.r, dirLight->material.diffuse.g, dirLight->material.diffuse.b);
				objs[i].shader.setVec3("dirlight.specular", dirLight->material.specular.r, dirLight->material.specular.g, dirLight->material.specular.b);
			}
				
			if (pointLight!=NULL)
			{
				for (int j = 0; j < POINT_LIGHTS; j++)
				{
					auto plight = &pointLight[j];
					string key = "poilight[" + to_string(j) +"]";
					plight->postion = glm::vec3(glm::sin(glfwGetTime())*(i+1),cos(glfwGetTime())*(i+1), cos(glfwGetTime())*(2 + 1));
					objs[i].shader.setVec4(key+".position", plight->postion.x, plight->postion.y, plight->postion.z, 1);
					objs[i].shader.setVec3(key + ".color", plight->color.r, plight->color.g, plight->color.b);
					objs[i].shader.setVec3(key + ".ambient", plight->material.ambient.r, plight->material.ambient.g, plight->material.ambient.b);
					objs[i].shader.setVec3(key + ".diffuse", plight->material.diffuse.r, plight->material.diffuse.g, plight->material.diffuse.b);
					objs[i].shader.setVec3(key + ".specular", plight->material.specular.r, plight->material.specular.g, plight->material.specular.b);

					objs[i].shader.setFloat(key + ".constant", 1);
					objs[i].shader.setFloat(key + ".linear", 0.09f);
					objs[i].shader.setFloat(key + ".quadratic", 0.03f);

				}
			
			}

			if (sportLight != NULL)
			{
				//聚光灯
				objs[i].shader.setVec4("spolight.position", camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z, 1);
				objs[i].shader.setVec3("spolight.direction", camera.front.x, camera.front.y, camera.front.z);
				objs[i].shader.setFloat("spolight.cutoff", glm::cos(glm::radians(sportLight->cutoff)));
				objs[i].shader.setFloat("spolight.outcutoff", glm::cos(glm::radians(sportLight->outCutOff)));


				objs[i].shader.setVec3("spolight.color", sportLight->color.r, sportLight->color.g, sportLight->color.b);
				objs[i].shader.setVec3("spolight.ambient", sportLight->material.ambient.r, sportLight->material.ambient.g, sportLight->material.ambient.b);
				objs[i].shader.setVec3("spolight.diffuse", sportLight->material.diffuse.r, sportLight->material.diffuse.g, sportLight->material.diffuse.b);
				objs[i].shader.setVec3("spolight.specular", sportLight->material.specular.r, sportLight->material.specular.g, sportLight->material.specular.b);
			}

	
			
			glBindVertexArray(objs[i].VAO);
			glDrawArrays(GL_TRIANGLES, 0, objs[i].vertCount);  //画顶点
		
		}

	

		glfwSwapBuffers(window);//交换缓冲,绘制
		glfwPollEvents();//检查事件
	}

	for (size_t i = 0; i < objs.size(); i++) {
		glDeleteVertexArrays(1, &objs[i].VAO);
		glDeleteBuffers(1, &objs[i].VBO);
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



