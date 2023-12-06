//#include <iostream>
//#include <string>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <sstream>
//
//#include "Window.h"
//#include "Renderer.h"
//#include "Model.h"
//#include "Shader.h"
//#include "Texture.h"
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stb_image.h>
//
//#include "glm/glm.hpp"
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//const unsigned int WIDTH = 800;
//const unsigned int HEIGHT = 600;
//unsigned int VAO, VBO, EBO;
//unsigned int shaderProgram;
//
//const char* vertexShaderSource = R"(
//    #version 330 core
//    layout (location = 0) in vec3 aPos;
//    layout (location = 1) in vec3 aColor;
//    layout (location = 2) in vec2 aTexCoords;
//
//    out vec3 ourColor;
//    out vec2 TexCoords;
//
//    uniform float xOffset; 
//    uniform float yOffset; 
//
//    void main() {
//        gl_Position = vec4(aPos.x + xOffset, aPos.y + yOffset, aPos.z, 1.0); 
//        ourColor = aColor;
//        TexCoords = aTexCoords;
//    }
//)";
//
//const char* fragmentShaderSource = R"(
//    #version 330 core
//    out vec4 FragColor;
//  
//    in vec3 ourColor;
//    in vec2 TexCoords;
//
//    uniform sampler2D ourTexture;
//
//    void main() {
//        vec4 texColor = texture(ourTexture, TexCoords);
//
//        FragColor = texColor * vec4(ourColor, 1.0f);
//    }
//)";
//
//struct Vertex_ {
//    float x, y, z, r, g, b, w, h;
//    Vertex_(float _x, float _y, float _z, float _r, float _g, float _b, float _w, float _h) : x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), w(_w), h(_h) {}
//};
//
//struct Face_ {
//    int v1, v2, v3;
//    Face_(int _v1, int _v2, int _v3) : v1(_v1), v2(_v2), v3(_v3) {}
//};
//
//void writeOBJ(const std::string& fileName, const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces);
//void readOBJ(const std::string& fileName, std::vector<Vertex_>& vertices, std::vector<Face_>& faces);
//void renderVertices(const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces, unsigned int& shaderProgram);
//
//int main()
//{
//    Window window("Lab 3", SCR_WIDTH, SCR_HEIGHT);
//  
//    Model model("res/models/rectangle.obj");
//
//    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");
//
//    Texture tex("res/textures/container.jpg");
//
//    Renderer render;
//
//    std::vector<Vertex_> vertices;
//    std::vector<Face_> faces;
//
//    std::cout << "Do you want to write (w) or read (r) an .obj file: ";
//
//        char choice;
//        std::cin >> choice;
//        std::cin.ignore();
//    
//        if (choice == 'w') {
//            std::cout << "Enter vertex or face data (v or f) or type 'exit' to finish:" << std::endl;
//    
//            bool continueInput = true;
//            std::string input;
//    
//            while (continueInput) {
//                std::getline(std::cin, input);
//    
//                if (input == "exit") {
//                    continueInput = false;
//                }
//                else if (!input.empty()) {
//                    if (input[0] == 'v') {
//                        float x, y, z, r, g, b, w, h;
//                        if (sscanf_s(input.c_str(), "v %f %f %f %f %f %f", &x, &y, &z, &r, &g, &b) == 8) {
//                            vertices.push_back(Vertex_(x, y, z, r, g, b, w, h));
//                        }
//                    }
//                    else if (input[0] == 'f') {
//                        int v1, v2, v3;
//                        if (sscanf_s(input.c_str(), "f %d %d %d", &v1, &v2, &v3) == 3) {
//                            faces.push_back(Face_(v1, v2, v3));
//                        }
//                    }
//                }
//            }
//    
//            writeOBJ("output.obj", vertices, faces);
//        }
//    
//        else if (choice == 'r') {
//            std::string fileName;
//            std::cout << "Enter the name of the .obj file to read: ";
//            std::cin >> fileName;
//            readOBJ(fileName, vertices, faces);
//
//            std::cout << "[x y z r g b textureCoordX textureCoordY]" << std::endl;
//    
//              for (const Vertex_& vertex : vertices) {
//                  std::cout << "Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ", " << vertex.r << ", " << vertex.g << ", " << vertex.b << ", " << vertex.w << ", " << vertex.h << ")\n";
//              }
//    
//              for (const Face_& face : faces) {
//                  std::cout << "Face: (" << face.v1 << ", " << face.v2 << ", " << face.v3 << ")\n";
//              }
//        }
//    
//        else {
//            std::cout << "Invalid choice." << std::endl;
//        }
//
//    unsigned int vertexShader, fragmentShader;
//    int success;
//    char infoLog[512];
//
//    //Vertex shader
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "Vertex shader compilation failed: " << infoLog << std::endl;
//    }
//
//    //Fragment shader
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "Fragment shader compilation failed: " << infoLog << std::endl;
//    }
//
//    //Shader program
//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "Shader program linking failed: " << infoLog << std::endl;
//    }
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    //unsigned int VAO, VBO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex_), vertices.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(Face_), faces.data(), GL_STATIC_DRAW);
//
//    //Position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  8*sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    //Colour attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex_, r));
//    glEnableVertexAttribArray(1);
//
//    //Texture coord attribute
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex_, w));
//    glEnableVertexAttribArray(2);
//
//    // Texture wrapping mode (mirroring)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    tex.Bind();
//
//    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    //glEnableVertexAttribArray(0);
//
//     // load and create a texture 
//    // -------------------------
//    unsigned int texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    int width, height, nrChannels;
//    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//    unsigned char* data = stbi_load("res/textures/spongebob.jpg", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//    float xOffsetValue = 0.1f; 
//    float yOffsetValue = 0.5f; 
//    int xOffsetLocation = glGetUniformLocation(shaderProgram, "xOffset");
//    int yOffsetLocation = glGetUniformLocation(shaderProgram, "yOffset");
//
//    while (!window.isClosed())
//    {
//        window.ProcessInput();
//        render.Clear();
//
//        glUseProgram(shaderProgram);
//
//        glUniform1f(xOffsetLocation, xOffsetValue);
//        glUniform1f(yOffsetLocation, yOffsetValue);
//
//        int textureUnit = 0;
//        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), textureUnit);
//        glActiveTexture(GL_TEXTURE0 + textureUnit);
//        glBindTexture(GL_TEXTURE_2D, texture);
//
//        //float timeValue = glfwGetTime();
//        //float greenValue = sin(timeValue) / 2.0f + 0.5f;
//        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
//
//        renderVertices(vertices, faces, shaderProgram);
//
//        //Render triangle
//        glBindVertexArray(VAO);
//  /*      glDrawArrays(GL_TRIANGLES, 0, 3);*/
//
//        glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
//        //model.Draw(shader, tex);
//
//        window.SwapAndPoll();
//    }
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteProgram(shaderProgram);
//
//    glfwTerminate();
//
//    return 0;
//}
//
//void writeOBJ(const std::string& fileName, const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces) {
//    std::ofstream objFile(fileName);
//
//    if (!objFile.is_open()) {
//        std::cerr << "Failed to open file " << fileName << " for writing." << std::endl;
//        return;
//    }
//
//    for (const Vertex_& vertex : vertices) {
//        objFile << "v " << vertex.x << " " << vertex.y << " " << vertex.z << vertex.r << " "  << vertex.g << " " << vertex.b << " " << vertex.w << " " << vertex.h << " " << "\n";
//    }
//
//    for (const Face_& face : faces) {
//        objFile << "f " << face.v1 << " " << face.v2 << " " << face.v3 << "\n";
//    }
//
//    objFile.flush();
//    objFile.close();
//}
//
//void readOBJ(const std::string& fileName, std::vector<Vertex_>& vertices, std::vector<Face_>& faces) {
//    std::ifstream objFile(fileName);
//
//    if (!objFile.is_open()) {
//        std::cerr << "Failed to open file " << fileName << " for reading." << std::endl;
//        return;
//    }
//
//    std::string line;
//
//    while (std::getline(objFile, line)) {
//        std::istringstream iss(line);
//        std::string prefix;
//        iss >> prefix;
//
//        if (prefix == "v") {
//            float x, y, z, r, g, b, w, h;
//            if (iss >> x >> y >> z >> r >> g >> b >> w >> h) {
//                vertices.push_back(Vertex_(x, y, z, r, g, b, w, h));
//            }
//        }
//        else if (prefix == "f") {
//            int v1, v2, v3;
//            if (iss >> v1 >> v2 >> v3) {
//                faces.push_back(Face_(v1 - 1, v2 - 1, v3 - 1));
//            }
//        }
//    }
//
//    objFile.close();
//}
//
//
//void renderVertices(const std::vector<Vertex_>& vertices, const std::vector<Face_>& faces, unsigned int& shaderProgram) {
//
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glUseProgram(shaderProgram);
//
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
//}