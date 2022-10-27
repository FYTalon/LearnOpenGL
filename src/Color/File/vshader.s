#version 440 core
layout (location = 0) in vec3 apos;
uniform mat4 transform;

void main(){
    gl_Position = transform * vec4(apos, 1.0);
}