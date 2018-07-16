#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <string>
#include <memory>
#include <vector>

namespace E3D
{
    class ImageSTB;
    class Texture2D;
}

class E3D::Texture2D
{
public:
    Texture2D( std::vector<unsigned char>& );
    Texture2D( const std::string& );
    ~Texture2D();

    ImageSTB * image() const { return m_Image.get(); }
    uint32_t id() const { return m_id; }

    void bind(unsigned int);
    void unBind(unsigned int);

private:
    uint32_t m_id;
  
    std::unique_ptr<ImageSTB> m_Image;
};

#endif //TEXTURE_2D_H
