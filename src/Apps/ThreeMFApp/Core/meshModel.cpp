#include <meshModel.h>

#include <camera.h>
#include <meshData.h>
#include <shaderLoaderGL.h>

#include <iostream>

using namespace E3D;

MeshModel::MeshModel( const MeshData& meshData)
        : m_meshData(meshData)
        , m_name("")
{
   sendDataToGPU();
}

MeshModel::~MeshModel()
{
}

void
MeshModel::sendDataToGPU()
{
    uint32_t VBO = 0;
    uint32_t EBO = 0;

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_meshData.vertices.size() * sizeof(Vertex), &m_meshData.vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshData.indices.size() * sizeof(uint32_t), &m_meshData.indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void 
MeshModel::updatMatrices(std::shared_ptr<Camera>& cam, std::shared_ptr<ShaderLoaderGL>& shader)
{
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);

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

    model = model * affineTransformMatrix;

    model = T * Rz * Ry * Rx * S * model;

    view = cam->viewMatrix();
    projection = cam->projectionMatrix();

    // shader uniforms
    shader->setUniform("ModelMatrix", model);
    shader->setUniform("ViewMatrix", view);
    shader->setUniform("ProjectionMatrix", projection);
}

void
MeshModel::draw(std::shared_ptr<Camera>& cam, std::shared_ptr<ShaderLoaderGL>& shader)
{
    updatMatrices(cam, shader);

    shader->enable();

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(m_meshData.indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shader->disable();
}

uint32_t
MeshModel::getNumVertices() const
{
    return static_cast<uint32_t>(m_meshData.vertices.size());
}

uint32_t
MeshModel::getNumTriangles() const
{
    return static_cast<uint32_t>(m_meshData.indices.size() / 3);
}

void 
MeshModel::setName(const std::string& name)
{
    m_name = name;
}

std::string 
MeshModel::getName() const
{
    return m_name;
}
