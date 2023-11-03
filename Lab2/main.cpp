//#include <iostream>
//#include <string>
//
//#include "Window/Window.h"
//#include "Renderer/Renderer.h"
//#include "Model/Model.h"
//#include "Shader/Shader.h"
//#include "Texture/Texture.h"
//
//#include "vendor/glm/glm.hpp"
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//
//
//int main()
//{
//    Window window("Lab3", SCR_WIDTH, SCR_HEIGHT);
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