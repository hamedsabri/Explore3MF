#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace E3D
{
    class Camera;
} 

class E3D::Camera
{
public:
    Camera(glm::vec3 eyePos, glm::vec3 lookAtPos, int w, int h) 
        : m_width(w)
        , m_height(h)
		, m_eyePos(eyePos)
		, m_lookAtPos(lookAtPos)
    {
    }

    ~Camera() = default;

    void 
    updateViewSize(int w, int h)
    {
        // w,h become zero when glfw window is minimized
        if (w == 0) w = 1;
        if (h == 0) h = 1;

        m_width = w;
        m_height = h;
    }

    glm::mat4 
    viewMatrix() const
    {
        return glm::lookAt( m_eyePos, 
                            m_lookAtPos, 
                            glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 
    projectionMatrix() const
    {
        return glm::perspectiveFov(45.0f, 
                                   static_cast<float>(m_width), 
                                   static_cast<float>(m_height), 
                                   0.1f, 10000.0f);
    }

private:
    int m_width;
    int m_height;

    glm::vec3 m_eyePos;
    glm::vec3 m_lookAtPos;
};

#endif //CAMERA_H
