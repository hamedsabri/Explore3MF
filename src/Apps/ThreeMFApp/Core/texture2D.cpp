#include <texture2D.h>
#include <imageSTB.h>

#include <glad/glad.h>

using namespace E3D;

Texture2D::Texture2D( std::vector<unsigned char>& buffer )
{
    m_Image = std::make_unique<ImageSTB>(buffer);

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D( GL_TEXTURE_2D, 
                  0, 
                  GL_RGBA8, 
                  m_Image->width(), 
                  m_Image->height(), 
                  0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image->data());

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

Texture2D::Texture2D( const std::string& filePath )
    : m_id(0)
{
    m_Image = std::make_unique<ImageSTB>(filePath.c_str());

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D( GL_TEXTURE_2D, 
                  0, 
                  GL_RGBA8, 
                  m_Image->width(), 
                  m_Image->height(), 
                  0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image->data());

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_id);
}

void 
Texture2D::bind(unsigned int unitIndex)
{
    glActiveTexture(GL_TEXTURE0 + unitIndex);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void 
Texture2D::unBind(unsigned int unitIndex)
{
    glActiveTexture(GL_TEXTURE0 + unitIndex);
    glBindTexture(GL_TEXTURE_2D, 0);
}
