#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

float xoffset = 0.0;
float yoffset = 0.0;
float alpha = 0.2;

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        xoffset -= 0.01f;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        xoffset += 0.01f;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        yoffset += 0.01f;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        yoffset -= 0.01f;
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        alpha -= 0.01f;
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        alpha += 0.01f;
}

int Wwidth = 800, Wheight = 600;

float vertices[] = {
     0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,      1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,      0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,      0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(Wwidth, Wheight, "LearnOpenGL", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader MyShader("../src/Texture/File/vshader.s", "../src/Texture/File/fshader.s");
    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    int width, height, nrChannels;
    char* name[] = {
        "../src/Texture/File/container.jpg",
        "../src/Texture/File/awesomeface.png"
    };
    unsigned char* data;

    unsigned int texture[2];

    glGenTextures(2, texture);
    stbi_set_flip_vertically_on_load(true);
    for(int i = 0; i < 2; i++){
        data = stbi_load(name[i], &width, &height, &nrChannels, 0);
        glBindTexture(GL_TEXTURE_2D, texture[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        if(data){
            auto c = !i ? GL_RGB : GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, c, width, height, 0, c, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        else {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
        
    }
    
    MyShader.use();
    MyShader.setInt("texture1", 0);
    MyShader.setInt("texture2", 1);

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        MyShader.use();
        MyShader.setFloat("xoffset", xoffset);
        MyShader.setFloat("yoffset", yoffset);
        MyShader.setFloat("alpha", alpha);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
