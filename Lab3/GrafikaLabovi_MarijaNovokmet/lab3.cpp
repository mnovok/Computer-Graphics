//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <sstream>
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
//struct Vertex {
//    float x, y, z;
//    Vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
//};
//
//struct Face {
//    int v1, v2, v3;
//    Face(int _v1, int _v2, int _v3) : v1(_v1), v2(_v2), v3(_v3) {}
//};
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//void writeOBJ(const std::string& fileName, const std::vector<Vertex>& vertices, const std::vector<Face>& faces);
//void readOBJ(const std::string& fileName, std::vector<Vertex>& vertices, std::vector<Face>& faces);
//void renderVertices(const std::vector<Vertex>& vertices, const std::vector<Face>& faces, unsigned int shaderProgram);
//
//int main(void) {
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL) {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    glViewport(0, 0, WIDTH, HEIGHT);
//
//    std::vector<Vertex> vertices;
//    std::vector<Face> faces;
//
//    /*  std::vector<Vertex> vertices = {
//           { 0.0f,  0.5f, 0.0f },
//           { -0.5f, -0.5f, 0.0f },
//           { 0.5f, -0.5f, 0.0f }
//      };*/
//
//      //for (const Vertex& vertex : vertices) {
//      //    std::cout << "Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
//      //}
//
//    std::cout << "Do you want to write (w) or read (r) an .obj file: ";
//    char choice;
//    std::cin >> choice;
//    std::cin.ignore();
//
//    if (choice == 'w') {
//        std::cout << "Enter vertex or face data (v or f) or type 'exit' to finish:" << std::endl;
//
//        bool continueInput = true;
//        std::string input;
//
//        while (continueInput) {
//            std::getline(std::cin, input);
//
//            if (input == "exit") {
//                continueInput = false;
//            }
//            else if (!input.empty()) {
//                if (input[0] == 'v') {
//                    float x, y, z;
//                    if (sscanf_s(input.c_str(), "v %f %f %f", &x, &y, &z) == 3) {
//                        vertices.push_back(Vertex(x, y, z));
//                    }
//                }
//                else if (input[0] == 'f') {
//                    int v1, v2, v3;
//                    if (sscanf_s(input.c_str(), "f %d %d %d", &v1, &v2, &v3) == 3) {
//                        faces.push_back(Face(v1, v2, v3));
//                    }
//                }
//            }
//        }
//
//        writeOBJ("output.obj", vertices, faces);
//    }
//
//    else if (choice == 'r') {
//        std::string fileName;
//        std::cout << "Enter the name of the .obj file to read: ";
//        std::cin >> fileName;
//        readOBJ(fileName, vertices, faces);
//
//        /*  for (const Vertex& vertex : vertices) {
//              std::cout << "Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
//          }
//
//          for (const Face& face : faces) {
//              std::cout << "Face: (" << face.v1 << ", " << face.v2 << ", " << face.v3 << ")\n";
//          }*/
//    }
//
//    else {
//        std::cout << "Invalid choice." << std::endl;
//    }
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
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(Face), faces.data(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//        renderVertices(vertices, faces, shaderProgram);
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
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
//
//void writeOBJ(const std::string& fileName, const std::vector<Vertex>& vertices, const std::vector<Face>& faces) {
//    std::ofstream objFile(fileName);
//
//    if (!objFile.is_open()) {
//        std::cerr << "Failed to open file " << fileName << " for writing." << std::endl;
//        return;
//    }
//
//    for (const Vertex& vertex : vertices) {
//        objFile << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
//    }
//
//    for (const Face& face : faces) {
//        objFile << "f " << face.v1 << " " << face.v2 << " " << face.v3 << "\n";
//    }
//
//    objFile.flush();
//    objFile.close();
//}
//
//void readOBJ(const std::string& fileName, std::vector<Vertex>& vertices, std::vector<Face>& faces) {
//    std::ifstream objFile(fileName);
//
//    if (!objFile.is_open()) {
//        std::cerr << "Failed to open file " << fileName << " for reading." << std::endl;
//        return;
//    }
//
//    std::string line;
//    while (std::getline(objFile, line)) {
//        std::istringstream iss(line);
//        std::string prefix;
//        iss >> prefix;
//
//        if (prefix == "v") {
//            float x, y, z;
//            if (iss >> x >> y >> z) {
//                vertices.push_back(Vertex(x, y, z));
//            }
//        }
//        else if (prefix == "f") {
//            int v1, v2, v3;
//            if (iss >> v1 >> v2 >> v3) {
//                faces.push_back(Face(v1 - 1, v2 - 1, v3 - 1));
//            }
//        }
//    }
//
//    objFile.close();
//}
//
//void renderVertices(const std::vector<Vertex>& vertices, const std::vector<Face>& faces, unsigned int shaderProgram) {
//
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glUseProgram(shaderProgram);
//
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
//
//
//}