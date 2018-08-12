#include <shaderLoaderGL.h>

#include <vector>
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

using namespace E3D;

ShaderLoaderGL::ShaderLoaderGL(const std::string& vertex_path, const std::string& fragment_path) 
    : m_programID(0)
    , m_activeProgram(0)
{
    loadShader(vertex_path, fragment_path);
}

ShaderLoaderGL::ShaderLoaderGL(const std::string& vertex_path, const std::string& fragment_path, const std::string& geometry_path) 
    : m_programID(0)
    , m_activeProgram(0)
{
    loadShader(vertex_path, fragment_path, geometry_path);
}

std::string 
ShaderLoaderGL::readFile(const std::string& filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "could not read file " << filePath << ". file does not exist." << '\n';
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n"); 
    }

    fileStream.close();
    return content;
}

void 
ShaderLoaderGL::loadShader(const std::string& vertex_path, const std::string& fragment_path)
{
    unsigned int vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // read shaders
    const std::string& vertShaderStr = readFile(vertex_path);
    const std::string& fragShaderStr = readFile(fragment_path);
    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    int result = GL_FALSE;
    int logLength;

    // compile vertex shader
    glShaderSource(vertShaderID, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShaderID);

    // check vertex shader
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShaderID, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << '\n';

    // compile fragment shader
    glShaderSource(fragShaderID, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShaderID);

    // check fragment shader
    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShaderID, logLength, NULL, &fragShaderError[0]);
    std::cout << &fragShaderError[0] << '\n';

    // create program and link 
    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertShaderID);
    glAttachShader(m_programID, fragShaderID);
    glLinkProgram(m_programID);

    // check program
    glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
    glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError((logLength > 1) ? logLength : 1);
    glGetProgramInfoLog(m_programID, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << '\n';

    // clean up
    glDetachShader(m_programID, vertShaderID);
    glDetachShader(m_programID, fragShaderID);

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);
}

void 
ShaderLoaderGL::loadShader(const std::string& vertex_path, const std::string& fragment_path, const std::string& geometry_path)
{
    unsigned int vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int geomShaderID = glCreateShader(GL_GEOMETRY_SHADER);

    // read shaders
    const std::string& vertShaderStr = readFile(vertex_path);
    const std::string& fragShaderStr = readFile(fragment_path);
    const std::string& geomShaderStr = readFile(geometry_path);
    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();
    const char* geomShaderSrc = geomShaderStr.c_str();

    int result = GL_FALSE;
    int logLength;

    // compile vertex shader
    glShaderSource(vertShaderID, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShaderID);

    // check vertex shader
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShaderID, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << '\n';

    // compile fragment shader
    glShaderSource(fragShaderID, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShaderID);

    // check fragment shader
    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShaderID, logLength, NULL, &fragShaderError[0]);
    std::cout << &fragShaderError[0] << '\n';

    // compile geom shader
    glShaderSource(geomShaderID, 1, &geomShaderSrc, NULL);
    glCompileShader(geomShaderID);

    // check geom shader
    glGetShaderiv(geomShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(geomShaderID, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> geomShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(geomShaderID, logLength, NULL, &geomShaderError[0]);
    std::cout << &geomShaderError[0] << '\n';

    // create program and link
    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertShaderID);
    glAttachShader(m_programID, fragShaderID);
    glAttachShader(m_programID, geomShaderID);
    glLinkProgram(m_programID);

    // check program
    glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
    glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError((logLength > 1) ? logLength : 1);
    glGetProgramInfoLog(m_programID, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << '\n';

    // clean up
    glDetachShader(m_programID, vertShaderID);
    glDetachShader(m_programID, fragShaderID);
    glDetachShader(m_programID, geomShaderID);

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);
    glDeleteShader(geomShaderID);
}

int 
ShaderLoaderGL::getAttribLocation(const char* attributeName) const
{
    int result = glGetAttribLocation(m_programID, (const GLchar *)attributeName);
  
    if (result == -1) 
    {
        std::cout << "Error getting attribute location:" << attributeName << '\n';
    }

    return result;
}

int
ShaderLoaderGL::getUniformLocation(const char* uniformName) const
{
    return glGetUniformLocation(m_programID, (const GLchar *)uniformName);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, int i)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&m_activeProgram);
    glUseProgram(m_programID);
    GLint uniformLocation = getUniformLocation(uniformName);
    glUniform1i(uniformLocation, i);
    glUseProgram(m_activeProgram);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, unsigned int i)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&m_activeProgram);
    glUseProgram(m_programID);
    GLint uniformLocation = getUniformLocation(uniformName);
    glUniform1ui(uniformLocation, i);
    glUseProgram(m_activeProgram);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, float f)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&m_activeProgram);
    glUseProgram(m_programID);
    GLint uniformLocation = getUniformLocation(uniformName);
    glUniform1f(uniformLocation, f);
    glUseProgram(m_activeProgram);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, float x, float y)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&m_activeProgram);
    glUseProgram(m_programID);
    GLint uniformLocation = getUniformLocation(uniformName);
    glUniform2f(uniformLocation, x, y);
    glUseProgram(m_activeProgram);  
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, float x, float y, float z)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&m_activeProgram);
    glUseProgram(m_programID);
    GLint uniformLocation = getUniformLocation(uniformName);
    glUniform3f(uniformLocation, x, y, z);
    glUseProgram(m_activeProgram);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, float x, float y, float z, float w)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&m_activeProgram);
    glUseProgram(m_programID);
    GLint uniformLocation = getUniformLocation(uniformName);
    glUniform4f(uniformLocation, x, y, z, w);
    glUseProgram(m_activeProgram);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, const glm::vec2& v)
{
    setUniform(uniformName, v.x, v.y);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, const glm::vec3& v)
{
    setUniform(uniformName, v.x, v.y, v.z);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, const glm::vec4& v)
{
    setUniform(uniformName, v.x, v.y, v.z, v.z);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, const glm::mat2& m)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&m_activeProgram);
    glUseProgram(m_programID);
    GLint uniformLocation = getUniformLocation(uniformName);
    glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m));
    glUseProgram(m_activeProgram);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, const glm::mat3& m)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&m_activeProgram);
    glUseProgram(m_programID);
    GLint uniformLocation = getUniformLocation(uniformName);
    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m));
    glUseProgram(m_activeProgram);
}

void 
ShaderLoaderGL::setUniform(const char* uniformName, const glm::mat4& m)
{
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&m_activeProgram);
    glUseProgram(m_programID);
    GLint uniformLocation = getUniformLocation(uniformName);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m));
    glUseProgram(m_activeProgram);
}

void 
ShaderLoaderGL::enable() const
{
    glUseProgram(m_programID);
}

void 
ShaderLoaderGL::disable() const
{
    glUseProgram(0);
}
