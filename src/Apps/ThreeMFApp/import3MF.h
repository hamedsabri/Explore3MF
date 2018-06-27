#ifndef IMPORT_3MF_H
#define IMPORT_3MF_H

#include <Model/COM/NMR_DLLInterfaces.h>

#include <string>

namespace E3D
{
    class Import3MF;
}

class E3D::Import3MF
{
public:
    Import3MF( const std::string& );
    ~Import3MF() = default;

private:
    Import3MF( const Import3MF& ) = delete;
    Import3MF& operator=( const Import3MF& ) = delete;

    HRESULT readData( const std::string& ) const;
    HRESULT parseMeshObject( NMR::PLib3MFModelMeshObject* ) const;
};

#endif //IMPORT_3MF_H
