#version 430
in vec3 tc;
out vec4 color;

uniform mat4 v_matrix;
uniform mat4 proj_matrix;

layout (binding=0) uniform samplerCube samp;

void main(void)
{	
    color = texture(samp, tc);
}
