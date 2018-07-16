#include <timer.h>

#include <GLFW/glfw3.h>

using namespace E3D;

namespace
{
    double currentTime = 0.0;
    double lastTime = 0.0;
    double deltaTime = 0.0;
    double millsecPerFrame = 0;
    double lastFrameTime = glfwGetTime();  
    unsigned int frameNum = 0;
}

void Timer::updateTime()
{
    frameNum++;

    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (currentTime - lastFrameTime >= 1.0)
    {
        millsecPerFrame = 1000.0 / double(frameNum);
        frameNum = 0;
        lastFrameTime = lastFrameTime + 1.0;
    }
}

double Timer::getDeltaSec()
{
    return deltaTime;
}

double Timer::getDeltaMillSec()
{
    return deltaTime * 1000;
}

// rely on this value for performance
// 30 FPS should give you 1/30 = 33.3333ms
// 60 FPS should give you 1/60 = 16.6666ms
double Timer::getMillSecPerFrame()
{
    return millsecPerFrame;
}
