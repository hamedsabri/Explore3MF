#ifndef IMAGE_STB_H
#define IMAGE_STB_H

#include <string>
#include <vector>

namespace E3D
{
    class ImageSTB;
    using PixelsBuffer = std::vector<unsigned char>;
}

class E3D::ImageSTB
{
public:
    ImageSTB( const PixelsBuffer& pixelsBuffer );
    ImageSTB( const char* );
    ~ImageSTB();

    int width() const { return m_width; }
    int height() const { return m_height; }

    PixelsBuffer pixels() const { return m_pixels; }
    unsigned char * data() const { return m_data; }

    int writeToFile( const std::string& );

private:
    ImageSTB( const ImageSTB& ) = delete;
    ImageSTB& operator=( const ImageSTB& ) = delete;

    void readFromMemory( const PixelsBuffer& );
    void readFromFile( const std::string& );
    
private:
    int m_width;
    int m_height;
    int m_channels;

    unsigned char * m_data;
    PixelsBuffer m_pixels;
};

#endif //IMAGE_STB_H
