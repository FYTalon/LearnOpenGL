#version 440 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform float xoffset, yoffset;
uniform mat4 transform;
out vec3 ourColor;
out vec2 TexCoord;

void main(){
    gl_Position = transform * vec4(apos.x + xoffset, apos.y + yoffset, apos.z, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}