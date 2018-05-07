﻿#include "stdafx.h"
////////#include <stdio.h>
////////#include <glew.h>        // GLEW扩展库
////////#include <freeglut.h>  // freeGLUT图形库
////////#include "ogldev_math_3d.h" // 用于OpenGL的3d数学库
////////
////////GLuint VBO;
////////
/////////**
////////* 渲染回调函数
////////*/
////////static void RenderScenceCB() {
////////	// 清空颜色缓存
////////	glClear(GL_COLOR_BUFFER_BIT);
////////
////////	// 开启顶点属性
////////	glEnableVertexAttribArray(0);
////////	// 绑定GL_ARRAY_BUFFER缓冲器
////////	glBindBuffer(GL_ARRAY_BUFFER, VBO);
////////	// 告诉管线怎样解析bufer中的数据
////////	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
////////
////////	// 开始绘制几何图形(绘制一个三角形，三个顶点)
////////	glDrawArrays(GL_TRIANGLES, 0, 3);
////////
////////	//  禁用顶点数据
////////	glDisableVertexAttribArray(0);
////////
////////	// 交换前后缓存
////////	glutSwapBuffers();
////////
////////	glFlush();
////////}
////////
/////////**
////////* 创建顶点缓冲器
////////*/
////////static void CreateVertexBuffer()
////////{
////////	// 创建含有3个顶点的顶点数组
////////	Vector3f Vertices[3];
////////	// 三角形的三个顶点位置
////////	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
////////	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
////////	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
////////
////////	// 创建缓冲器
////////	glGenBuffers(1, &VBO);
////////	// 绑定GL_ARRAY_BUFFER缓冲器
////////	glBindBuffer(GL_ARRAY_BUFFER, VBO);
////////	// 绑定顶点数据
////////	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
////////}
////////
/////////**
////////* 主函数
////////*/
////////int main(int argc, char ** argv) {
////////
////////	// 初始化GLUT
////////	glutInit(&argc, argv);
////////
////////	// 显示模式：双缓冲、RGBA
////////	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
////////
////////	// 窗口设置
////////	glutInitWindowSize(480, 320);      // 窗口尺寸
////////	glutInitWindowPosition(100, 100);  // 窗口位置
////////	glutCreateWindow("Tutorial 03");   // 窗口标题
////////
////////									   // 开始渲染
////////	glutDisplayFunc(RenderScenceCB);
////////
////////	// 缓存清空后的颜色值
////////	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
////////
////////	// 检查GLEW是否就绪，必须要在GLUT初始化之后！
////////	GLenum res = glewInit();
////////	if (res != GLEW_OK) {
////////		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
////////		return 1;
////////	}
////////
////////	// 创建顶点缓冲器
////////	CreateVertexBuffer();
////////
////////	// 通知开始GLUT的内部循环
////////	glutMainLoop();
////////
////////	return 0;
////////}