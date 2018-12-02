#ifndef MAIN_APP_H
#define MAIN_APP_H

#include <windowGL.h>
#include <memory>

namespace E3D
{
    class MainApp;
    class Camera;
    class ShaderLoaderGL;
    class MeshQuadColor;
    class Import3MF;
    class WorldGrid;
}

class E3D::MainApp : public WindowGL
{
public:
    MainApp();
    ~MainApp();

private:
    void init() override;
    void preDraw() override;
    void draw() override;
    void postDraw() override;
    void onResize(GLFWwindow* window, int width, int height) override;

    void guiSetup() override;
    void guiDraw() override;

private:
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<ShaderLoaderGL> m_vertexShader;
    std::shared_ptr<ShaderLoaderGL> m_facetedShader;

    std::unique_ptr<Import3MF> m_importModel3MF;
    std::unique_ptr<WorldGrid> m_worldGrid;
};

#endif //MAIN_APP_H
