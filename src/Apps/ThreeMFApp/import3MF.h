#ifndef IMPORT_3MF_H
#define IMPORT_3MF_H

#include <string>

namespace E3D
{
    class Import3MF;
}

class E3D::Import3MF
{
public:
    Import3MF( const std::wstring& );
    ~Import3MF() = default;

private:
    Import3MF( const Import3MF& ) = delete;
    Import3MF& operator=( const Import3MF& ) = delete;

    bool readData( const std::wstring& ) const;
};

#endif //IMPORT_3MF_H
