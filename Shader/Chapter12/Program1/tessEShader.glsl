#version 430

//与曲面细分控制着色器layout (vertices = 1) out;无关
layout (quads, equal_spacing, ccw) in;

uniform mat4 mvp_matrix;

void main (void)
{
    //自动计算的UV坐标
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	gl_Position = mvp_matrix * vec4(u,0,v,1);
}