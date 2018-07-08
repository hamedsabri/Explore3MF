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

    void worldAxisDraw(std::shared_ptr<Camera>&, std::shared_ptr<ShaderLoaderGL>&);

private:
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<ShaderLoaderGL> m_vertexShader;
};

#endif //MAIN_APP_H