#include <WindowGL.h>

#include <iostream>

using namespace E3D;

WindowGL * WindowGL::m_windowGL = nullptr;

WindowGL::WindowGL()
    : m_glfWindow(nullptr)
{
    m_windowGL = this;
}

WindowGL::~WindowGL()
{
    if (m_windowGL)
        m_windowGL = nullptr;

    glfwDestroyWindow(m_glfWindow);
    glfwTerminate();
}

void 
WindowGL::initialize()
{
    // initialize GLFW
    glfwInit();

    // set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, m_multiSample);

    // needed for mac
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);

    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    // create glfw window and default openGL context
    m_glfWindow = glfwCreateWindow(m_width, m_height, "", nullptr, nullptr);
    if (m_glfWindow)
    {
        glfwMakeContextCurrent(m_glfWindow);
    }

    // setup callbacks
    glfwSetWindowSizeCallback(m_glfWindow, _onResize);
    glfwSetFramebufferSizeCallback(m_glfWindow, _onResizeFramebuffer);

    // setup GLAD
    if(gladLoadGL())
    {
        std::cout << "OpenGL Version: " << GLVersion.major << "." << GLVersion.minor << std::endl;
    }
    else
    {
        std::cout << "Glad failed!";
        return;
    }

    // client code
    init();

    makeCentered();
}

void
WindowGL::open(int w, int h, int multiSample)
{
    m_width = w;
    m_height = h;
    m_multiSample = multiSample;

    initialize();

    // client code
    preDraw();

    drawLoop();

    // client code
    postDraw();
}

void 
WindowGL::drawLoop()
{
    while (!glfwWindowShouldClose(m_glfWindow))
    {
        // event processing
        glfwPollEvents();

        // client code
        draw();
        
        glfwSwapBuffers(m_glfWindow);
    }

    glfwTerminate();
}

void 
WindowGL::_onResize(GLFWwindow* window, int width, int height)
{
    m_windowGL->m_width = width;
    m_windowGL->m_height = height;

    m_windowGL->onResize(window, width, height);
}

void 
WindowGL::_onResizeFramebuffer(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void 
WindowGL::setSize(int width, int height)
{
    m_width = width;
    m_height = height;
}

void WindowGL::makeCentered()
{
    const GLFWvidmode* windowMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int x = static_cast<int>((windowMode->width/ 2 - m_width / 2));
    int y = static_cast<int>((windowMode->height/2 - m_height/2));

    glfwSetWindowPos(m_glfWindow, x, y);
}
