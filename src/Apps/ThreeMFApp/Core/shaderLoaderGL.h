#ifndef SHADER_LOADER_GL_H
#define SHADER_LOADER_GL_H

#include <glm/glm.hpp>
#include <string>

namespace E3D
{
    class ShaderLoaderGL;
}

class E3D::ShaderLoaderGL
{
public:
    ShaderLoaderGL(const std::string&, const std::string&);
    ShaderLoaderGL(const std::string&, const std::string&, const std::string&);

    ~ShaderLoaderGL() = default;
  
    int getAttribLocation(const char*) const;
    int getUniformLocation(const char*) const;
    
    void setUniform(const char*, int);
    void setUniform(const char*, unsigned int);
    void setUniform(const char*, float);
    void setUniform(const char*, float, float);
    void setUniform(const char*, float, float, float);
    void setUniform(const char*, float, float, float, float);
    void setUniform(const char*, const glm::vec2&);
    void setUniform(const char*, const glm::vec3&);
    void setUniform(const char*, const glm::vec4&);
    void setUniform(const char*, const glm::mat2&);
    void setUniform(const char*, const glm::mat3&);
    void setUniform(const char*, const glm::mat4&);

    void enable() const;
    void disable() const;

private:
    std::string readFile(const std::string&);
    void loadShader(const std::string&, const std::string&);
    void loadShader(const std::string&, const std::string&, const std::string&);
    
private:
    unsigned int m_programID;
    unsigned int m_activeProgram;
};

#endif //SHADER_LOADER_GL_H
