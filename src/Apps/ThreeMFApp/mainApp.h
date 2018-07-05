#ifndef MAIN_APP_H
#define MAIN_APP_H

#include <WindowGL.h>

namespace E3D
{
    class MainApp;
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
};

#endif //MAIN_APP_H