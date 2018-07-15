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
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);

    view = cam->viewMatrix();
    projection = cam->projectionMatrix();

    shader->setUniform("ModelMatrix", m_affineTransformMatrix);
    shader->setUniform("ViewMatrix", view);
    shader->setUniform("ProjectionMatrix", projection);
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

void 
MeshLine::setAffineTransformMatrix(const glm::mat4& mat)
{
    m_affineTransformMatrix = mat;
}

glm::mat4 
MeshLine::getAffineTransformMatrix() const
{
    return m_affineTransformMatrix;
}

