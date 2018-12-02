#include <meshLine.h>

#include <camera.h>
#include <meshData.h>
#include <shaderLoaderGL.h>

using namespace E3D;

MeshLine::MeshLine(const std::array<Vertex, 2>& vertices)
    : m_vertices(vertices)
{
    sendDataToGPU();
}

MeshLine::~MeshLine()
{
}

void
MeshLine::sendDataToGPU()
{
    unsigned int VBO = 0;
    unsigned int EBO = 0;

    unsigned char indices[2] = {0, 1};

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void
MeshLine::updatMatrices(std::shared_ptr<Camera>& cam, std::shared_ptr<ShaderLoaderGL>& shader)
{
    glm::mat4 T = glm::mat4(1.0f);
    T = glm::translate(T, translate);

    glm::mat4 Rx = glm::mat4(1.0f);
    Rx = glm::rotate(Rx, glm::radians(rotate.x), glm::vec3(1, 0, 0));

    glm::mat4 Ry = glm::mat4(1.0f);
    Ry = glm::rotate(Ry, glm::radians(rotate.y), glm::vec3(0, 1, 0));

    glm::mat4 Rz = glm::mat4(1.0f);
    Rz = glm::rotate(Rz, glm::radians(rotate.z), glm::vec3(0, 0, 1));

    glm::mat4 S = glm::mat4(1.0f);
    S = glm::scale(S, scale);

    model = T * Rz * Ry * Rx * S * affineTransformMatrix;

    shader->setUniform("ModelMatrix", model);
    shader->setUniform("ViewMatrix", cam->viewMatrix());
    shader->setUniform("ProjectionMatrix", cam->projectionMatrix());
}

void
MeshLine::draw(std::shared_ptr<Camera>& cam, std::shared_ptr<ShaderLoaderGL>& shader)
{
    updatMatrices(cam, shader);

    shader->enable();

    glBindVertexArray(m_VAO);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, 0);
    
    shader->disable();
}
