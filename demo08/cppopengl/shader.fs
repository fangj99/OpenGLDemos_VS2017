#version 330  //告诉编译器我们的目标GLSL编译器版本是3.3 Tell the compilte that our GLSL version is 3.3

out vec4 FragColor;  // 片段着色器的输出颜色变量 fragment shader's color output 

// 着色器的唯一入口函数 shader's only entry point
void main()
{
    // 定义输出颜色值 Dfine the output color
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}