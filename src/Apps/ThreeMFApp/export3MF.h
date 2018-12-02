#ifndef EXPORT_3MF_H
#define EXPORT_3MF_H

#include <string>
#include <vector>
#include <memory>

namespace E3D
{
    class Export3MF;

    class MeshModel;
    using PMeshModel = std::shared_ptr<MeshModel>;

    using MeshModels = std::vector<PMeshModel>;
}

class E3D::Export3MF
{
public:
    Export3MF( const std::string&, const MeshModels& );
    ~Export3MF() = default;

private:
    Export3MF( const Export3MF& ) = delete;
    Export3MF& operator=( const Export3MF& ) = delete;

    bool saveData( const std::string&, const MeshModels& );
};

#endif //EXPORT_3MF_H
