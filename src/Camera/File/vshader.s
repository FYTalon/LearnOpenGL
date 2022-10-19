#version 440 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 transform;
out vec2 TexCoord;

void main(){
    gl_Position = transform * vec4(apos.x, apos.y, apos.z, 1.0);
    TexCoord = aTexCoord;
}