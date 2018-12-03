#ifndef WINDOW_GL_H
#define WINDOW_GL_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <timer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace E3D
{
    class WindowGL;
    class ImageSTB;
}

class E3D::WindowGL
{
public:
    WindowGL();
    virtual ~WindowGL();

    void open(int, int, int multiSample = 4 );

    virtual void init() = 0;
    virtual void preDraw() = 0;
    virtual void draw() = 0;
    virtual void postDraw() = 0;
    virtual void onResize(GLFWwindow*, int, int) = 0;
    
    virtual void guiSetup() = 0;
    virtual void guiDraw() = 0;

    void setSize(int, int);
    void setTitle(const std::string&);
    void setWindowIcon(const char*);

    int width(){ return m_width; }
    int height(){ return m_height; }

    static WindowGL * m_windowGL;

private:
    void initialize();
    void drawLoop();
    void makeCentered();

    static void _onResize(GLFWwindow*, int, int);
    static void _onResizeFramebuffer(GLFWwindow*, int, int);

protected:
    GLFWwindow * m_glfWindow;

private:
    std::string m_windowTitle;

    int m_width;
    int m_height;
    int m_multiSample;
};

static E3D::WindowGL* windowGL()
{
    return E3D::WindowGL::m_windowGL;
}

#endif // WINDOW_GL_H