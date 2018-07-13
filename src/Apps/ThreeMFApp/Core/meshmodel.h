#ifndef MESH_MODEL_H
#define MESH_MODEL_H

#include <vector>

#include <Camera.h>
#include <MeshData.h>
#include <MeshDraw.h>

namespace E3D
{
    class MeshModel;
    class Camera;
    class ShaderLoaderGL;
}

class E3D::MeshModel : public MeshDraw
{
public:
    MeshModel(const MeshData&);
    ~MeshModel();

    void draw(std::shared_ptr<Camera>&, std::shared_ptr<ShaderLoaderGL>&) override;

    uint32_t numVertices() const;
    uint32_t numTriangles() const;

protected:
    void sendDataToGPU() override;
    void updatMatrices(std::shared_ptr<Camera>&, std::shared_ptr<ShaderLoaderGL>&) override;

private:
    MeshData m_meshData;
};

#endif //MESH_MODEL_H
