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
	
	using RawVertices = std::vector<Vertex>;
	using RawIndices = std::vector<uint32_t>;

    struct MeshData
    {
        RawVertices vertices;
        RawIndices indices;
    };
}

#endif //MESH_DATA_H