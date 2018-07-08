#include <mainApp.h>

#include <meshLine.h>
#include <camera.h>
#include <shaderLoaderGL.h>

#include <glm/glm.hpp>

using namespace E3D;

namespace
{
    glm::vec4 kBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

    float kWorldAxisLenght(0.5f);
}

MainApp::MainApp()
{
}

MainApp::~MainApp()
{
}

void
MainApp::init()
{
    m_camera = std::make_shared<Camera>( glm::vec3(0.0f, 4.0f, 4.0f), 
                                         glm::vec3(0.0f, 0.0f, 0.0f), 
                                         width(), height());

    std::string path(RESOURCEDIR_PATH);
    m_vertexShader = std::make_shared<ShaderLoaderGL>(path + "Shaders/vertexColorShader.vert",
                                                      path + "Shaders/vertexColorShader.frag");
}

void 
MainApp::preDraw()
{
}

void
MainApp::draw()
{
    glClearColor(kBackgroundColor[0],
                 kBackgroundColor[1],
                 kBackgroundColor[2],
                 kBackgroundColor[3]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    worldAxisDraw(m_camera, m_vertexShader);
}

void
MainApp::postDraw()
{
}

void
MainApp::onResize(GLFWwindow* window, int width, int height)
{
    m_camera->updateViewSize(width, height);
}

void 
MainApp::worldAxisDraw(std::shared_ptr<Camera>& cam, std::shared_ptr<ShaderLoaderGL>& shader)
{
    std::array<Vertex, 2> vertices;

    // X- Red
    {
        vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f) * kWorldAxisLenght;
        vertices[1].position = glm::vec3(1.f, 0.0f, 0.0f) * kWorldAxisLenght;

        vertices[0].setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        vertices[1].setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        auto meshLine = std::make_unique<MeshLine>(vertices);
        meshLine->draw(cam, shader);
    }

    // Y- Green
    {
        vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f) * kWorldAxisLenght;
        vertices[1].position = glm::vec3(0.0f, 1.f, 0.0f) * kWorldAxisLenght;

        vertices[0].setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        vertices[1].setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

        auto meshLine = std::make_unique<MeshLine>(vertices);
        meshLine->draw(cam, shader);
    }

    // Z-Blue
    {
        vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f) * kWorldAxisLenght;
        vertices[1].position = glm::vec3(0.0f, 0.0f, 1.f) * kWorldAxisLenght;

        vertices[0].setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        vertices[1].setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

        auto meshLine = std::make_unique<MeshLine>(vertices);
        meshLine->draw(cam, shader);
    }
}
