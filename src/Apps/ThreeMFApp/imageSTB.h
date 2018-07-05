#ifndef IMAGE_STB_H
#define IMAGE_STB_H

#include <string>

namespace E3D
{
    class ImageSTB;
}

class E3D::ImageSTB
{
public:
    ImageSTB() = default;
    ImageSTB( const char* );
    ~ImageSTB();

    int width() const { return m_width; }
    int height() const { return m_height; }

    unsigned char * data() const { return m_data; }

    void readFromFile( const std::string& );
    int writeToFile( const std::string& );

private:
    ImageSTB( const ImageSTB& ) = delete;
    ImageSTB& operator=( const ImageSTB& ) = delete;
    
private:
    int m_width;
    int m_height;
    int m_channels;

    unsigned char * m_data;
};

#endif //IMAGE_STB_H
