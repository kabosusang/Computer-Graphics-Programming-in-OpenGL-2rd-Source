#version 430
uniform float offset;

void main(void){
    if(gl_VertexID==0)gl_Position=vec4(0.25 + offset,-.25,0.,1.);
    else if(gl_VertexID==1)gl_Position=vec4(-0.25 + offset,-.25,0.,1.);
    else gl_Position=vec4(0.25 + offset,.25,0.,1.);
}