//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <sstream>
//
//#include "Window/Window.h"
//#include "Renderer/Renderer.h"
//#include "Model/Model.h"
//#include "Shader/Shader.h"
//#include "Texture/Texture.h"
//
//#include "vendor/glm/glm.hpp"
//
//const unsigned int WIDTH = 800;
//const unsigned int HEIGHT = 600;
//unsigned int VAO, VBO, EBO;
//unsigned int shaderProgram;
//
//const char* vertexShaderSource = R"(
//    #version 330 core
//    layout (location = 0) in vec3 aPos;
//    void main() {
//        gl_Position = vec4(aPos, 1.0);
//    }
//)";
//
//const char* fragmentShaderSource = R"(
//    #version 330 core
//    out vec4 FragColor;
//    void main() {
//        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
//    }
//)";
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//int main(void) {
//    Window window("Vjezba3", WIDTH, HEIGHT);
//
//    Model model("res/models/rectangle.obj");
//    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");
//    Texture tex("res/textures/container.jpg");
//
//    Renderer render;
//    while (!window.isClosed())
//    {
//        window.ProcessInput();
//        render.Clear();
//
//        model.Draw(shader, tex);
//
//        window.SwapAndPoll();
//    }
//
//    window.CloseWindow();
//
//    return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//    glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window) {
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//        glfwSetWindowShouldClose(window, true);
//    }
//}