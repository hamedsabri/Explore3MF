#include <MainApp.h>

#include <glm/glm.hpp>
#include <iostream>
#include <string>

using namespace E3D;

namespace
{
    glm::vec4 kBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);
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
}

void
MainApp::postDraw()
{
}

void
MainApp::onResize(GLFWwindow* window, int width, int height)
{
}
