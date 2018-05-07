#version 330

// 接受vs传来的插值后的颜色值
in vec4 Color;

out vec4 FragColor;

void main()
{
    // 颜色值作为片段着色器fs的输出
    FragColor = Color;
}