#version 440 core
layout (location = 0) in vec3 apos;
uniform mat4 model, view, projection;

void main(){
    gl_Position = projection * view * model * vec4(apos, 1.0);
}