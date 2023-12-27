#include <iostream>
#include <string>

#include "Window.h"
#include "Renderer.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window("Vjezba3", SCR_WIDTH, SCR_HEIGHT);

    Model cube("res/models/cube.obj");
    Model dragon("res/models/dragon.obj");

    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");

    Texture tex("res/textures/container.jpg");

    Renderer render;
    while (!window.isClosed())
    {
        window.ProcessInput();
        render.Clear();

        //model view projection
        glm::mat4 model_mat = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 1.0f);

        view = glm::lookAt(
            camera_position,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        shader.SetUniform4x4("model", model_mat);
        shader.SetUniform4x4("view", view);
        shader.SetUniform4x4("projection", projection);
        //ambient
        glm::vec3 light_color = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 object_color = glm::vec3(1.0f, 0.0f, 0.0f);
        float ambient_strength = 0.2f;

        shader.SetUniformVec3("light_color", light_color);
        shader.SetUniformVec3("object_color", object_color);
        shader.SetUniformFloat("ambient_strength", ambient_strength);

        // diffuse
        glm::vec3 light_position = glm::vec3(0.0f, 1.0f, 1.0f);

        shader.SetUniformVec3("light_position", light_position);
        // specular
        glm::vec3 view_position = camera_position;
        float specular_strength = 1.0f;

        shader.SetUniformVec3("view_position", view_position);
        shader.SetUniformFloat("specular_strength", specular_strength);

        dragon.Draw(shader, tex);

        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}