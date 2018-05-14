#include "stdafx.h"
////////#include <stdio.h>
////////#include <string.h>
////////#include <glew.h>
////////#include <freeglut.h>
////////
////////#include "ogldev_util.h" //这里要添加作者的工具类用于读取文本文件 Need add author's tool to read file
////////#include "ogldev_math_3d.h"
////////
////////GLuint VBO;
////////
////////// 定义要读取的顶点着色器脚本和片断着色器脚本的文件名，作为文件读取路径（这样的话shader.vs和shader.fs文件要放到工程的根目录下，保证下面定义的是这两个文件的文件路径）
////////// Define the shader files, need put these two file under the same directory as the cpp file
////////const char* pVSFileName = "shader.vs";
////////const char* pFSFileName = "shader.fs";
////////
////////static void RenderSceneCB()
////////{
////////	glClear(GL_COLOR_BUFFER_BIT);
////////
////////	glEnableVertexAttribArray(0);
////////	glBindBuffer(GL_ARRAY_BUFFER, VBO);
////////	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
////////
////////	// 依然还是绘制一个三角形 Still drawing an triangle
////////	glDrawArrays(GL_TRIANGLES, 0, 3);
////////
////////	glDisableVertexAttribArray(0);
////////
////////	glutSwapBuffers();
////////}
////////
////////
////////static void InitializeGlutCallbacks()
////////{
////////	glutDisplayFunc(RenderSceneCB);
////////}
////////
////////static void CreateVertexBuffer()
////////{
////////	Vector3f Vertices[3];
////////	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
////////	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
////////	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
////////
////////	glGenBuffers(1, &VBO);
////////	glBindBuffer(GL_ARRAY_BUFFER, VBO);
////////	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
////////}
////////
////////// 使用shader文本编译shader对象，并绑定shader都想到着色器程序中
////////// Use the shader file to compile the shader object and bind it to the program object
////////static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
////////{
////////	// 根据shader类型参数定义两个shader对象
////////	// Define two shader objects according to the shader type
////////	GLuint ShaderObj = glCreateShader(ShaderType);
////////	// 检查是否定义成功 Check if shader is created successfully
////////	if (ShaderObj == 0) {
////////		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
////////		exit(0);
////////	}
////////
////////	// 定义shader的代码源 define the source of shade 
////////	const GLchar* p[1];
////////	p[0] = pShaderText;
////////	GLint Lengths[1];
////////	Lengths[0] = strlen(pShaderText);
////////	glShaderSource(ShaderObj, 1, p, Lengths);
////////	glCompileShader(ShaderObj);// 编译shader对象 compile the shade object
////////
////////							   // 检查和shader相关的错误 check the errors related to the shader
////////	GLint success;
////////	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
////////	if (!success) {
////////		GLchar InfoLog[1024];
////////		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
////////		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
////////		exit(1);
////////	}
////////
////////	// 将编译好的shader对象绑定到program object程序对象上 Bind the compiled shader object the program object
////////	glAttachShader(ShaderProgram, ShaderObj);
////////}
////////
////////// 编译着色器函数 Compile the shaders
////////static void CompileShaders()
////////{
////////	// 创建着色器程序 Create shader program
////////	GLuint ShaderProgram = glCreateProgram();
////////	// 检查是否创建成功 check if ShaderProgram is created successfully.
////////	if (ShaderProgram == 0) {
////////		fprintf(stderr, "Error creating shader program\n");
////////		exit(1);
////////	}
////////
////////	// 存储着色器文本的字符串缓冲 Strings to store the shader files
////////	string vs, fs;
////////	// 分别读取着色器文件中的文本到字符串缓冲区 Read shader file to string
////////	if (!ReadFile(pVSFileName, vs)) {
////////		exit(1);
////////	};
////////	if (!ReadFile(pFSFileName, fs)) {
////////		exit(1);
////////	};
////////
////////	// 添加顶点着色器和片段着色器 Add vertex shader and fragment shader
////////	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
////////	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);
////////
////////	// 链接shader着色器程序，并检查程序相关错误 Link the shader program and check if there is any error
////////	GLint Success = 0;
////////	GLchar ErrorLog[1024] = { 0 };
////////	glLinkProgram(ShaderProgram);
////////	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
////////	if (Success == 0) {
////////		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
////////		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
////////		exit(1);
////////	}
////////
////////	// 检查验证在当前的管线状态程序是否可以被执行 Check and verify the Pipeline status
////////	glValidateProgram(ShaderProgram);
////////	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
////////	if (!Success) {
////////		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
////////		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
////////		exit(1);
////////	}
////////
////////	// 设置到管线声明中来使用上面成功建立的shader程序 Start use the ShaderProgram
////////	glUseProgram(ShaderProgram);
////////}
//////// 
////////// 主函数 Main function
////////int main(int argc, char** argv)
////////{
////////	glutInit(&argc, argv);
////////	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
////////	glutInitWindowSize(1024, 768);
////////	glutInitWindowPosition(100, 100);
////////	glutCreateWindow("Tutorial 04");
////////
////////	InitializeGlutCallbacks();
////////	 
////////	// 必须在glut初始化后！ Must init after the initialization of glut
////////	GLenum res = glewInit();
////////	if (res != GLEW_OK) {
////////		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
////////		return 1;
////////	}
////////
////////	printf("GL version: %s\n", glGetString(GL_VERSION));
////////
////////	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
////////
////////	CreateVertexBuffer();
////////
////////	// 编译着色器 Copile the shaders
////////	CompileShaders();
////////
////////	glutMainLoop();
////////
////////	return 0;
////////}