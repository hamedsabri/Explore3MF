#include <meshModel.h>

#include <camera.h>
#include <meshData.h>
#include <shaderLoaderGL.h>

#include <iostream>

using namespace E3D;

MeshModel::MeshModel( const MeshData& meshData)
        : m_meshData(meshData)
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
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);

    view = cam->viewMatrix();
    projection = cam->projectionMatrix();

    // shader uniforms
    shader->setUniform("ModelMatrix", m_affineTransformMatrix);
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

void 
MeshModel::setAffineTransformMatrix( const glm::mat4& mat )
{
    m_affineTransformMatrix = mat;
}

glm::mat4 
MeshModel::getAffineTransformMatrix() const
{
    return m_affineTransformMatrix;
}

uint32_t
MeshModel::numVertices() const
{
    return static_cast<uint32_t>(m_meshData.vertices.size());
}

uint32_t
MeshModel::numTriangles() const
{
    return static_cast<uint32_t>(m_meshData.indices.size() / 3);
}

