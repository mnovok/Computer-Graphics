//#include "glad/glad.h"
//#include "Model.h"
//
//#include <assert.h>
//
//Vertex::Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 texCor) 
//	: position(pos), normal(norm), textureCordinates(texCor) { }
//
//Mesh::Mesh(const std::string& meshPath)
//{
//	LoadMesh(meshPath);
//	SetupMesh();
//}
//
//Mesh::~Mesh()
//{
//    glDeleteBuffers(1, &m_EBO);
//    glDeleteBuffers(1, &m_VBO);
//    glDeleteVertexArrays(1, &m_RenderID);
//}
//
//void Mesh::LoadMesh(const std::string& meshPath)
//{
//    std::vector<glm::vec3> positions;
//    std::vector<glm::vec3> normals;
//    std::vector<glm::vec2> texCord;
//
//    std::stringstream streamBuf;
//    std::string readLine;
//    std::string attribute;
//
//    std::ifstream objFile{ meshPath, std::ios::in };
//    if (!objFile)
//        std::cerr << "FILE COULD NOT OPEN\n";
//
//    float x, y, z;
//    int f1, f2, f3;
//    while (std::getline(objFile, readLine))
//    {
//        streamBuf.clear();
//        streamBuf.str(readLine);
//
//        std::getline(streamBuf, attribute, streamBuf.widen(' '));
//
//        if (attribute.compare("v") == 0)
//        {
//            std::getline(streamBuf, readLine);
//            streamBuf.clear();
//            streamBuf.str(readLine);
//
//            streamBuf >> x >> y >> z;
//            positions.push_back(glm::vec3(x, y, z));
//        }
//        else if (attribute.compare("vn") == 0)
//        {
//            std::getline(streamBuf, readLine);
//            streamBuf.clear();
//            streamBuf.str(readLine);
//
//            streamBuf >> x >> y >> z;
//            normals.push_back(glm::vec3(x, y, z));
//        }
//        else if (attribute.compare("vt") == 0)
//        {
//            std::getline(streamBuf, readLine);
//            streamBuf.clear();
//            streamBuf.str(readLine);
//
//            streamBuf >> x >> y;
//            texCord.push_back(glm::vec2(x, y));
//        }
//        else if (attribute.compare("f") == 0)
//        {
//            std::getline(streamBuf, readLine);
//            streamBuf.clear();
//            streamBuf.str(readLine);
//
//            streamBuf >> f1 >> f2 >> f3;
//            m_Indices.push_back(f1 - 1);
//            m_Indices.push_back(f2 - 1);
//            m_Indices.push_back(f3 - 1);
//        }
//    }
//    objFile.close();
//
//    for (int pos = 0; pos < positions.size(); pos++)
//    {
//        m_Mesh.push_back(Vertex(positions[pos], normals[pos], texCord[pos]));
//    }
//}
//
//void Mesh::SetupMesh()
//{
//    glGenVertexArrays(1, &m_RenderID);
//    glGenBuffers(1, &m_VBO);
//    glGenBuffers(1, &m_EBO);
//    glBindVertexArray(m_RenderID);
//
//    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Mesh.size(), m_Mesh.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
//    glEnableVertexAttribArray(1);
//
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(glm::vec3)));
//    glEnableVertexAttribArray(2);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glBindVertexArray(0);
//}
//
//void Mesh::Draw(const Shader& shader, const Texture& texture) const
//{
//    shader.Bind();
//    texture.Bind();
//    glBindVertexArray(m_RenderID);
//
//    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
//
//    glBindVertexArray(0);
//}
//
//
//Model::Model(const std::string& meshPath) 
//    : m_Mesh(std::make_unique<Mesh>(meshPath)) { }
//
//Model::~Model() {}
//
//void Model::Draw(const Shader& shader, const Texture& texture) const
//{
//    m_Mesh->Draw(shader, texture);
//}