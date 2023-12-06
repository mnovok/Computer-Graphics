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
#include <Camera/Camera.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
unsigned int VAO, VBO, EBO;
unsigned int shaderProgram;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool isOrtho = false;

struct Vertex_ {
    float x, y, z, w, h;
    Vertex_(float _x, float _y, float _z, float _w, float _h) : x(_x), y(_y), z(_z), w(_w), h(_h) {}
};

struct Face_ {
    int v1, v2, v3;
    Face_(int _v1, int _v2, int _v3) : v1(_v1), v2(_v2), v3(_v3) {}
};

void framebuffer_size_callback2(GLFWwindow* window, int width, int height);
void processInput2(GLFWwindow* window, Shader& shader);
void writeOBJ(const std::string& fileName, const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces);
void readOBJ(const std::string& fileName, std::vector<Vertex_>& vertices, std::vector<Face_>& faces);
void renderVertices(const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces, unsigned int& shaderProgram);
void setTransformation(const glm::mat4& transform, unsigned int shaderProgram);
void renderMultipleCubes(Shader& shader, unsigned int VAO, unsigned int texture1, unsigned int texture2, unsigned int cubeCount, const glm::vec3 cubePositions[]);
void rotateCamera(Shader& shader, unsigned int VAO, const glm::vec3 cubePositions[], unsigned int cubeCount, float radius);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void toggleProjection(Shader& shader);

int main()
{
    Window window("Lab 4", SCR_WIDTH, SCR_HEIGHT);

    Renderer render;

    glfwMakeContextCurrent(window.getGLFWWindow());
    glfwSetFramebufferSizeCallback(window.getGLFWWindow(), framebuffer_size_callback);
    glfwSetCursorPosCallback(window.getGLFWWindow(), mouse_callback);
    glfwSetScrollCallback(window.getGLFWWindow(), scroll_callback);

    glfwSetInputMode(window.getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

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

    //Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)offsetof(Vertex_, w));
    glEnableVertexAttribArray(1);

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
    glBindTexture(GL_TEXTURE_2D, texture2); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
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
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    while (!window.isClosed())
    {
        // per-frame time logic
          // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /*window.ProcessInput();*/
        processInput2(window.getGLFWWindow(), ourShader);
        render.Clear();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();

        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        //FOURTH TASK
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
        window.SwapAndPoll();
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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

void rotateCamera(Shader& shader, unsigned int VAO, const glm::vec3 cubePositions[], unsigned int cubeCount, float radius) {
    static float time = 0.0f; // Static variable to keep track of time for rotation

    glm::mat4 view = glm::mat4(1.0f);
    float camX = static_cast<float>(sin(time) * radius);
    float camZ = static_cast<float>(cos(time) * radius);
    view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    shader.use();
    shader.setMat4("view", view);

    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < cubeCount; i++) {
        glm::mat4 model = glm::mat4(1.0f); //change positions
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    time += 0.001f; // Adjust the rotation speed here as needed
}

void processInput2(GLFWwindow* window, Shader& shader)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        toggleProjection(shader);
    }
}

void framebuffer_size_callback2(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void toggleProjection(Shader& shader) {
    isOrtho = !isOrtho; 

    if (isOrtho) {
        //Orthogonal projection
        float orthoSize = 10.0f; 
        glm::mat4 projection = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, 0.1f, 100.0f);
        shader.use(); 
        shader.setMat4("projection", projection);
    }
    else {
        //Perspective projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.use();
        shader.setMat4("projection", projection);
    }
}
