#include <windowGL.h>

#include <imageSTB.h>

#include <iostream>

using namespace E3D;

WindowGL * WindowGL::m_windowGL = nullptr;

WindowGL::WindowGL()
    : m_glfWindow(nullptr)
    , m_windowTitle("")
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

    // decide GL+GLSL versions
    #if __APPLE__
        const char* glsl_version = "#version 330";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #else
        const char* glsl_version = "#version 330";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    #endif

    glfwWindowHint(GLFW_SAMPLES, m_multiSample);

    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    // create glfw window and default openGL context
    m_glfWindow = glfwCreateWindow(m_width, m_height, m_windowTitle.c_str(), nullptr, nullptr);
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

    // setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_glfWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    init();

    guiSetup();

    makeCentered();
}

void
WindowGL::open(int w, int h, int multiSample)
{
    m_width = w;
    m_height = h;
    m_multiSample = multiSample;

    initialize();

    preDraw();

    drawLoop();

    postDraw();
}

void 
WindowGL::drawLoop()
{
    while (!glfwWindowShouldClose(m_glfWindow))
    {
        // event processing
        glfwPollEvents();

        // update timer
        Timer::updateTime();

        // start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        guiDraw();

        draw();

        // ImGui rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_glfWindow);
    }

    // cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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

void 
WindowGL::setTitle(const std::string& titleName)
{
    m_windowTitle = titleName;

    glfwSetWindowTitle(m_glfWindow, m_windowTitle.c_str());
}

void 
WindowGL::setWindowIcon(const char* imagePath)
{
    ImageSTB image(imagePath);
    GLFWimage imageGLFW { image.width(), image.height(), image.data() };
    glfwSetWindowIcon(m_glfWindow, 1, &imageGLFW);
}

void WindowGL::makeCentered()
{
    const GLFWvidmode* windowMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int x = static_cast<int>((windowMode->width/ 2 - m_width / 2));
    int y = static_cast<int>((windowMode->height/2 - m_height/2));

    glfwSetWindowPos(m_glfWindow, x, y);
}
