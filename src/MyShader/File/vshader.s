#version 440 core
layout (location = 0) in vec3 apos;
uniform float xoffset, yoffset;
out vec4 vertexColor;

void main(){
    gl_Position = vec4(apos.x + xoffset, apos.y + yoffset, apos.z, 1.0);
    vertexColor = vec4(apos.x + xoffset, apos.y + yoffset, apos.z, 1.0);
}