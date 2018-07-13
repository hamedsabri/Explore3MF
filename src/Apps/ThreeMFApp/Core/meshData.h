#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <glm/glm.hpp>
#include <vector>

namespace E3D
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color; 

        void setPosition(const glm::vec3& _position)
        {
            position = _position;
        }

        void setColor(const glm::vec4& _color)
        {
            color = _color;
        }
    };

    struct MeshData
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
    };
}

#endif //MESH_DATA_H