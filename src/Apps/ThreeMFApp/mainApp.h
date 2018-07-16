#ifndef MAIN_APP_H
#define MAIN_APP_H

#include <WindowGL.h>
#include <memory>

namespace E3D
{
    class MainApp;
    class Camera;
    class ShaderLoaderGL;
    class MeshQuadColor;
    class Import3MF;
}

class E3D::MainApp : public WindowGL
{
public:
    MainApp();
    ~MainApp();

private:
    void guiSetup() override;
    void guiDraw() override;
    void init() override;
    void preDraw() override;
    void draw() override;
    void postDraw() override;
    void onResize(GLFWwindow* window, int width, int height) override;

    void worldAxisDraw(std::shared_ptr<Camera>&, std::shared_ptr<ShaderLoaderGL>&);

private:
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<ShaderLoaderGL> m_vertexShader;
    std::shared_ptr<ShaderLoaderGL> m_facetedShader;

    std::unique_ptr<Import3MF> m_model3MF;
};

#endif //MAIN_APP_H