#include <worldGrid.h>
#include <camera.h>
#include <meshData.h>
#include <meshLine.h>
#include <shaderLoaderGL.h>

using namespace E3D;

WorldGrid::WorldGrid( int _size, int _highlightBreaks, float _breakUnit) 
    : m_iSize(_size)
    , m_iHighlightBreaks(_highlightBreaks)
    , m_fBreakUnit(2.0f)
    , m_worldAxisLenght(0.5f)
    , m_bEnableGrid(true)
    , m_Axis(Axis::Y)
{
    build();
}

void 
WorldGrid::build()
{
    std::array<Vertex, 2> vertices;

    // grid lines
    //X
    for (int x=0; x<=m_iSize; x++)
    {  
        if (x % m_iHighlightBreaks != 0)
        {
            vertices[0].position = setAxisOrder(((x*m_fBreakUnit)-m_iSize)/(2*m_fBreakUnit), 0.0f, -m_iSize/(2*m_fBreakUnit)); // +X , 0 , -Z
            vertices[1].position = setAxisOrder(((x*m_fBreakUnit)-m_iSize)/(2*m_fBreakUnit), 0.0f,  m_iSize/(2*m_fBreakUnit)); // +X , 0 , +Z

            vertices[0].setColor(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
            vertices[1].setColor(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

            std::unique_ptr<MeshLine> meshLine = std::make_unique<MeshLine>(vertices);
            m_gridLines.push_back(std::move(meshLine));
        }
    }

    //Z
    for (int z=0; z<=m_iSize; z++)
    { 
        if (z % m_iHighlightBreaks != 0)
        {
            vertices[0].position = setAxisOrder( -m_iSize/(2*m_fBreakUnit), 0.0f,((z*m_fBreakUnit)-m_iSize)/(2*m_fBreakUnit)); // -X , 0 , +Z
            vertices[1].position = setAxisOrder(  m_iSize/(2*m_fBreakUnit), 0.0f,((z*m_fBreakUnit)-m_iSize)/(2*m_fBreakUnit)); // +X , 0 , +Z

            vertices[0].setColor(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
            vertices[1].setColor(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));

            std::unique_ptr<MeshLine> meshLine = std::make_unique<MeshLine>(vertices);
            m_gridLines.push_back(std::move(meshLine));
        }
    }

    //X
    for (int x=0; x<=m_iSize; x+=m_iHighlightBreaks)
    {
        vertices[0].position = setAxisOrder(((x*m_fBreakUnit)-m_iSize)/(2*m_fBreakUnit), 0.0f, -m_iSize/(2*m_fBreakUnit)); // +X , 0 , -Z
        vertices[1].position = setAxisOrder(((x*m_fBreakUnit)-m_iSize)/(2*m_fBreakUnit), 0.0f,  m_iSize/(2*m_fBreakUnit)); // +X , 0 , +Z

        vertices[0].setColor(glm::vec4(0.0, 0.0f, 0.0f, 1.0f));
        vertices[1].setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        std::unique_ptr<MeshLine> meshLine = std::make_unique<MeshLine>(vertices);
        m_gridLines.push_back(std::move(meshLine));
    }

    //Z
    for (int z=0; z<=m_iSize; z+=m_iHighlightBreaks)
    {
        vertices[0].position = setAxisOrder( -m_iSize/(2*m_fBreakUnit), 0.0f,((z*m_fBreakUnit)-m_iSize)/(2*m_fBreakUnit)); // -X , 0 , +Z
        vertices[1].position = setAxisOrder(  m_iSize/(2*m_fBreakUnit), 0.0f,((z*m_fBreakUnit)-m_iSize)/(2*m_fBreakUnit)); // +X , 0 , +Z

        vertices[0].setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        vertices[1].setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        std::unique_ptr<MeshLine> meshLine = std::make_unique<MeshLine>(vertices);
        m_gridLines.push_back(std::move(meshLine));
    }

    // world Axis
    // X- Red
    {
        vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f) * m_worldAxisLenght;
        vertices[1].position = glm::vec3(1.f, 0.0f, 0.0f) * m_worldAxisLenght;

        vertices[0].setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        vertices[1].setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        std::unique_ptr<MeshLine> meshLine = std::make_unique<MeshLine>(vertices);
        m_worldAxis.push_back(std::move(meshLine));
    }

    // Y- Green
    {
        vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f) * m_worldAxisLenght;
        vertices[1].position = glm::vec3(0.0f, 1.f, 0.0f) * m_worldAxisLenght;

        vertices[0].setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        vertices[1].setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

        std::unique_ptr<MeshLine> meshLine = std::make_unique<MeshLine>(vertices);
        m_worldAxis.push_back(std::move(meshLine));
    }

    // Z-Blue
    {
        vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f) * m_worldAxisLenght;
        vertices[1].position = glm::vec3(0.0f, 0.0f, 1.f) * m_worldAxisLenght;

        vertices[0].setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        vertices[1].setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

        std::unique_ptr<MeshLine> meshLine = std::make_unique<MeshLine>(vertices);
        m_worldAxis.push_back(std::move(meshLine));
    }
}

WorldGrid::~WorldGrid()
{
}

void 
WorldGrid::draw(std::shared_ptr<Camera>& cam, std::shared_ptr<ShaderLoaderGL>& shader)
{
    if (!m_bEnableGrid)
        return;

    glLineWidth(1.0f);

    for ( const auto& axis : m_worldAxis )
       axis->draw(cam, shader);

    for ( const auto& gridLine : m_gridLines )
       gridLine->draw(cam, shader);
}

float 
WorldGrid::getGridBreakUnit() const
{
    return m_fBreakUnit;
}

int
WorldGrid::getGridHighlightUnit() const
{
    return m_iHighlightBreaks;
}

Axis 
WorldGrid::getAxis() const
{
    return m_Axis;
}

void 
WorldGrid::setAxis(Axis axis)
{ 
    m_Axis = axis;
}

void 
WorldGrid::setEnableGrid(bool enable_grid)
{
    m_bEnableGrid = enable_grid;
}

void 
WorldGrid::setWorldAxisLenght(float length)
{
    m_worldAxisLenght = length;
}

void 
WorldGrid::setGridSize(int iSize)
{
    m_iSize = iSize;
}

void 
WorldGrid::setGridHighlightUnit(int iHighlightBreaks)
{
    m_iHighlightBreaks = iHighlightBreaks;
}

glm::vec3 
WorldGrid::setAxisOrder(float x, float y, float z)
{
    //Specify the order of GRID X Y Z 
    if (m_Axis == Axis::Y)
    {
        return glm::vec3(x, y, z);
    }
    else if (m_Axis == Axis::Z)
    {
        return glm::vec3(z, x, y);
    }
    else 
    {
        return glm::vec3(y, z, x);
    }
}

int 
WorldGrid::getGridSize() const
{
    return m_iSize;
}
