#include <ImageSTB.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

using namespace E3D;

ImageSTB::ImageSTB( const char* filename )
{
    readFromFile(filename);
}

ImageSTB::~ImageSTB()
{
    stbi_image_free(m_data);
}

void
ImageSTB::readFromFile( const std::string& filePath)
{
    m_data = stbi_load( filePath.c_str(), &m_width, &m_height, &m_channels, 4 );
}

int
ImageSTB::writeToFile( const std::string& filePath )
{
    return stbi_write_png(filePath.c_str(), m_width, m_height, m_channels, m_data, 0);
}
