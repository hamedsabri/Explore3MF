#ifndef WORLD_GRID_H
#define WORLD_GRID_H

#include <MeshData.h>

#include <memory>

enum class Axis : uint8_t
{
    X = 0,
    Y,
    Z
};

namespace E3D
{
    class WorldGrid;
    class ShaderLoaderGL;
    class Camera;
    class MeshLine;
}

class E3D::WorldGrid
{
public:
    WorldGrid(int _size = 18, int _highlightBreaks = 9, float _breakUnit = 2.0f);
    ~WorldGrid();

    void draw( std::shared_ptr<Camera>&, std::shared_ptr<ShaderLoaderGL>& ); 

    void setGridSize(int);
    int getGridSize() const; 

    void setGridBreakUnit(float);
    float getGridBreakUnit() const; 

    void setGridHighlightUnit(int);
    int getGridHighlightUnit() const; 

    void setEnableGrid(bool);
    void setWorldAxisLenght(float);

    void setAxis(Axis);
    Axis getAxis() const;
    
    glm::vec3 setAxisOrder(float, float, float);

private:
    WorldGrid( const WorldGrid& ) = delete;
    WorldGrid& operator=( const WorldGrid& ) = delete;

    void build();

private:  
    int m_iSize;    
    int m_iHighlightBreaks;
    float m_fBreakUnit;
    float m_worldAxisLenght;

    bool m_bEnableGrid;

    Axis m_Axis;

    std::vector<std::unique_ptr<MeshLine>> m_worldAxis;
    std::vector<std::unique_ptr<MeshLine>> m_gridLines;
};

#endif //WORLD_GRID_H
