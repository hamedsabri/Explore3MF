#ifndef MESH_DRAW_H
#define MESH_DRAW_H

#include <glad/glad.h>

#include <memory>

namespace E3D
{
    class MeshDraw;
    class ShaderLoaderGL;
    class Camera;
}

class E3D::MeshDraw
{
public:
    virtual void draw(std::shared_ptr<Camera>&, 
                      std::shared_ptr<ShaderLoaderGL>&) = 0;

    virtual ~MeshDraw() 
    { 
        glDeleteVertexArrays(1, &m_VAO); 
    }

protected:
    virtual void sendDataToGPU() = 0;

    virtual void updatMatrices( std::shared_ptr<Camera>&, 
                                std::shared_ptr<ShaderLoaderGL>&) = 0;

    uint32_t m_VAO = 0;
};

#endif //MESH_DRAW_H