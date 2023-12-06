#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Window.h"
#include "Renderer.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "glm/glm.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_s.h>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
unsigned int VAO, VBO, EBO;
unsigned int shaderProgram;

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    void main() {
        gl_Position =  transform * vec4(aPos, 1.0f);
	    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 TexCoord;

    uniform sampler2D texture1;
    uniform sampler2D texture2;

    void main() {
        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    }
)";

struct Vertex_ {
    float x, y, z, w, h;
    Vertex_(float _x, float _y, float _z, float _w, float _h) : x(_x), y(_y), z(_z), w(_w), h(_h) {}
};

struct Face_ {
    int v1, v2, v3;
    Face_(int _v1, int _v2, int _v3) : v1(_v1), v2(_v2), v3(_v3) {}
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void writeOBJ(const std::string& fileName, const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces);
void readOBJ(const std::string& fileName, std::vector<Vertex_>& vertices, std::vector<Face_>& faces);
void renderVertices(const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces, unsigned int& shaderProgram);
void setTransformation(const glm::mat4& transform, unsigned int shaderProgram);
void renderMultipleCubes(Shader& shader, unsigned int VAO, unsigned int texture1, unsigned int texture2, unsigned int cubeCount, const glm::vec3 cubePositions[]);


int main()
{
    Window window("Lab 4", SCR_WIDTH, SCR_HEIGHT);

    //Model model("res/models/rectangle.obj");

    //Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");

    //Texture tex("res/textures/container.jpg");

    Renderer render;

    Shader ourShader("src/coordinateVs.glsl", "src/coordinateFs.glsl");

    std::vector<Vertex_> vertices;
    std::vector<Face_> faces;


   /* std::cout << "Do you want to write (w) or read (r) an .obj file: ";

    char choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 'w') {
        std::cout << "Enter vertex or face data (v or f) or type 'exit' to finish:" << std::endl;

        bool continueInput = true;
        std::string input;

        while (continueInput) {
            std::getline(std::cin, input);

            if (input == "exit") {
                continueInput = false;
            }
            else if (!input.empty()) {
                if (input[0] == 'v') {
                    float x, y, z, r, g, b, w, h;
                    if (sscanf_s(input.c_str(), "v %f %f %f", &x, &y, &z) == 3) {
                        vertices.push_back(Vertex_(x, y, z));
                    }
                }
                else if (input[0] == 'f') {
                    int v1, v2, v3;
                    if (sscanf_s(input.c_str(), "f %d %d %d", &v1, &v2, &v3) == 3) {
                        faces.push_back(Face_(v1, v2, v3));
                    }
                }
            }
        }

        writeOBJ("output.obj", vertices, faces);
    }

    else if (choice == 'r') {
        std::string fileName;
        std::cout << "Enter the name of the .obj file to read: ";
        std::cin >> fileName;
        readOBJ(fileName, vertices, faces);

        std::cout << "[x y z]" << std::endl;

        for (const Vertex_& vertex : vertices) {
            std::cout << "Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
        }

        for (const Face_& face : faces) {
            std::cout << "Face: (" << face.v1 << ", " << face.v2 << ", " << face.v3 << ")\n";
        }
    }

    else {
        std::cout << "Invalid choice." << std::endl;
    }*/
    readOBJ("src/a2.obj", vertices, faces);


    //unsigned int vertexShader, fragmentShader;
    //int success;
    //char infoLog[512];

    ////Vertex shader
    //vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //glCompileShader(vertexShader);

    //glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //if (!success) {
    //    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //    std::cout << "Vertex shader compilation failed: " << infoLog << std::endl;
    //}

    ////Fragment shader
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //glCompileShader(fragmentShader);

    //glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    //if (!success) {
    //    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //    std::cout << "Fragment shader compilation failed: " << infoLog << std::endl;
    //}

    ////Shader program
    //unsigned int shaderProgram;
    //shaderProgram = glCreateProgram();
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);

    //glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    //if (!success) {
    //    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //    std::cout << "Shader program linking failed: " << infoLog << std::endl;
    //}

    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);
   
     // world space positions of our cubes
     glm::vec3 cubePositions[] = {
         glm::vec3(0.0f,  0.0f,  0.0f),
         glm::vec3(2.0f,  5.0f, -15.0f),
         glm::vec3(-1.5f, -2.2f, -2.5f),
         glm::vec3(-3.8f, -2.0f, -12.3f),
         glm::vec3(2.4f, -0.4f, -3.5f),
         glm::vec3(-1.7f,  3.0f, -7.5f),
         glm::vec3(1.3f, -2.0f, -2.5f),
         glm::vec3(1.5f,  2.0f, -2.5f),
         glm::vec3(1.5f,  0.2f, -1.5f),
         glm::vec3(-1.3f,  1.0f, -1.5f)
     };

    const unsigned int cubeCount = sizeof(cubePositions) / sizeof(cubePositions[0]);

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex_), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(Face_), faces.data(), GL_STATIC_DRAW);

    //Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Colour attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex_, r));
    //glEnableVertexAttribArray(1);

    //Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)offsetof(Vertex_, w));
    glEnableVertexAttribArray(1);


    // Texture wrapping mode (mirroring)
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //tex.Bind();

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

     // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("res/textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("res/textures/spongebob.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


   /* glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    float xOffsetValue = 0.0f;
    float yOffsetValue = 0.0f;
    int xOffsetLocation = glGetUniformLocation(shaderProgram, "xOffset");
    int yOffsetLocation = glGetUniformLocation(shaderProgram, "yOffset");*/

    while (!window.isClosed())
    {
        window.ProcessInput();
        render.Clear();

       /* glUseProgram(shaderProgram);*/
        //shader.Bind();
        //shader.SetUniformInt("texture", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // pass transformation matrices to the shader
        ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader.setMat4("view", view);

        renderMultipleCubes(ourShader, VAO, texture1, texture2, cubeCount, cubePositions);

        //glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        //setTransformation(transform, ourShader.ID);

        //glUniform1f(xOffsetLocation, xOffsetValue);
        //glUniform1f(yOffsetLocation, yOffsetValue);

        //int textureUnit = 0;
        //glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), textureUnit);
        //glActiveTexture(GL_TEXTURE0 + textureUnit);
        //glBindTexture(GL_TEXTURE_2D, texture);

        // create transformations
        //glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 view = glm::mat4(1.0f);
        //glm::mat4 projection = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        //projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //// retrieve the matrix uniform locations
        //unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        //unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        //// pass them to the shaders (3 different ways)
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        //// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        //shader.SetUniform4x4("projection", projection);

        //// create transformations
        //glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        // get matrix's uniform location and set matrix


        //renderVertices(vertices, faces, shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
        window.SwapAndPoll();
        glfwPollEvents();

        //Render triangle
        //glBindVertexArray(VAO);
        ///*      glDrawArrays(GL_TRIANGLES, 0, 3);*/

        //glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
        ////model.Draw(shader, tex);

        //window.SwapAndPoll();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
}

void writeOBJ(const std::string& fileName, const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces) {
    std::ofstream objFile(fileName);

    if (!objFile.is_open()) {
        std::cerr << "Failed to open file " << fileName << " for writing." << std::endl;
        return;
    }

    for (const Vertex_& vertex : vertices) {
        objFile << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }

    for (const Face_& face : faces) {
        objFile << "f " << face.v1 << " " << face.v2 << " " << face.v3 << "\n";
    }

    objFile.flush();
    objFile.close();
}

void readOBJ(const std::string& fileName, std::vector<Vertex_>& vertices, std::vector<Face_>& faces) {
    std::ifstream objFile(fileName);

    if (!objFile.is_open()) {
        std::cerr << "Failed to open file " << fileName << " for reading." << std::endl;
        perror("Error");
        return;
    }

    std::string line;

    while (std::getline(objFile, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            float x, y, z, w, h;
            if (iss >> x >> y >> z >> w >> h) {
                vertices.push_back(Vertex_(x, y, z, w, h));
            }
        }
        else if (prefix == "f") {
            int v1, v2, v3;
            if (iss >> v1 >> v2 >> v3) {
                faces.push_back(Face_(v1 - 1, v2 - 1, v3 - 1));
            }
        }
    }

    objFile.close();
}



void renderVertices(const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces, unsigned int& shaderProgram) {

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
}

void setTransformation(const glm::mat4& transform, unsigned int shaderProgram) {
    glUseProgram(shaderProgram);
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void renderMultipleCubes(Shader& shader, unsigned int VAO, unsigned int texture1, unsigned int texture2, unsigned int cubeCount, const glm::vec3 cubePositions[]) {
    shader.use();

    for (unsigned int i = 0; i < cubeCount; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        shader.setMat4("model", model);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}