#ifndef MESH_LINE_H
#define MESH_LINE_H

#include <meshData.h>
#include <meshDraw.h>

#include <array>

namespace E3D
{
    class MeshLine;
    class Camera;
    class ShaderLoaderGL;
}

class E3D::MeshLine : public MeshDraw
{
public:
    MeshLine(const std::array<Vertex, 2>&);
    virtual ~MeshLine();

    void draw( std::shared_ptr<Camera>&, 
               std::shared_ptr<ShaderLoaderGL>& ) override;

    void setAffineTransformMatrix(const glm::mat4&) override;
    glm::mat4 getAffineTransformMatrix() const override;

protected:
    void sendDataToGPU() override;
    void updatMatrices( std::shared_ptr<Camera>&, 
                        std::shared_ptr<ShaderLoaderGL>& ) override;
private:
    std::array<Vertex, 2> m_vertices;
};

#endif //MESH_LINE_H