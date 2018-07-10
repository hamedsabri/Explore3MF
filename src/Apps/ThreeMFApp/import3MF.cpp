#include <import3MF.h>

#include <Common/Platform/NMR_ImportStream_GCC_Native.h>
#include <Model/Reader/NMR_ModelReader_3MF_Native.h>
#include <Model/Classes/NMR_ModelBuildItem.h>

#include <assert.h>
#include <iostream>

using namespace E3D;
using namespace NMR;

Import3MF::Import3MF(const std::wstring& fileName)
{
    readData(fileName);
}

bool
Import3MF::readData(const std::wstring& fileName) const
{
    PModel model = std::make_shared<CModel>();
    PImportStream modelStream = std::make_shared<CImportStream_GCC_Native>(fileName.c_str());
    PModelReader modelReader = std::make_shared<CModelReader_3MF_Native>(model);

    try
    {
        modelReader->readStream(modelStream);
    }
    catch (CNMRException ex)
    {
        std::cout << "NMR Exception: " << ex.what() << '\n';
        throw ex;
    }

    std::cout << "Model ObjectCount: " << model->getObjectCount() << '\n';
    std::cout << "Model BuildItemCount: " << model->getBuildItemCount() << '\n';

    const uint32_t buildItemCount = model->getBuildItemCount();
    for (uint32_t i = 0; i < buildItemCount; ++i )
    {
        PModelBuildItem item = model->getBuildItem(i);

        std::cout << "Item Transformation: " << item->getTransformString() << '\n';
        std::cout << "Item ObjectID:" << item->getObjectID() << '\n';

        CModelObject * object = item->getObject();

        // all component is merged inot one mesh.
        PMesh mesh = std::make_shared<CMesh>();
        object->mergeToMesh(mesh.get());

        const uint32_t vertsCount = mesh->getNodeCount();
        const uint32_t faceCount = mesh->getFaceCount();
        assert( faceCount > 0 );
        assert( vertsCount > 0 );

        std::cout << "VertsCount:" << vertsCount << '\n';
        std::cout << "FaceCount:" << faceCount << '\n';

        for( uint32_t index = 0; index < vertsCount; ++index )
        {
            MESHNODE * node = mesh->getNode( index );

            std::cout << "Vertex [" <<  index << "]" 
                      << ":" 
                      << node->m_position.m_fields[0] << ", "
                      << node->m_position.m_fields[1] << ", "
                      << node->m_position.m_fields[2] << '\n';
        }

        for( uint32_t index = 0; index < faceCount; ++index )
        {
            MESHFACE * triFace = mesh->getFace(index);

            std::cout << "Triangle [" <<  index << "]" 
                      << ":" 
                      << triFace->m_nodeindices[0] << ", "
                      << triFace->m_nodeindices[1] << ", "
                      << triFace->m_nodeindices[2] << '\n';
        }

    }

    return true;
}
