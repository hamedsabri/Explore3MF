#include <import3MF.h>

#include <Common/Platform/NMR_ImportStream_GCC_Native.h>
#include <Model/Reader/NMR_ModelReader_3MF_Native.h>
#include <Model/Classes/NMR_ModelBuildItem.h>

#include <meshModel.h>

#include <assert.h>
#include <iostream>

using namespace E3D;
using namespace NMR;

namespace
{
    double
    getUnitScale(PModel model)
    {
        double scale = 1.0;

        switch (model->getUnit())
        {
        case MODELUNIT_FOOT:
            scale = 30.48;
            break;

        case MODELUNIT_METER:
            scale = 1e+2;
            break;

        case MODELUNIT_CENTIMETER:
            scale = 1.0;
            break;

        case MODELUNIT_INCH:
            scale = 2.54;
            break;

        case MODELUNIT_MILLIMETER:
            scale = 1e-1;
            break;

        case MODELUNIT_MICROMETER:
            scale = 1e-4;
            break;
        }

        return scale;
    }

    void
    saveMeshDataPerItem(PModel model, PMesh mesh, std::vector<PMeshModel>& meshModels)
    {
        MeshData meshData;

        const uint32_t vertsCount = mesh->getNodeCount();
        const uint32_t faceCount = mesh->getFaceCount();
        assert( faceCount > 0 );
        assert( vertsCount > 0 );

        for( uint32_t index = 0; index < vertsCount; ++index )
        {
            Vertex vertex;

            auto node = mesh->getNode( index );

            // position
            vertex.position = glm::vec3( node->m_position.m_fields[0],
                                         node->m_position.m_fields[1], 
                                         node->m_position.m_fields[2]) * static_cast<float>(getUnitScale(model));   

            meshData.vertices.push_back(vertex);
        }

        CMeshInformationHandler * pMeshInformationHandler = mesh->getMeshInformationHandler();
        CMeshInformation * pInformation = nullptr;

        for( uint32_t index = 0; index < faceCount; ++index )
        {
            pInformation = pMeshInformationHandler->getInformationByType(0, emiBaseMaterials);

            if (pInformation->faceHasData(index))
            {
                // indices
                auto triFace = mesh->getFace(index);

                meshData.indices.push_back(triFace->m_nodeindices[0]);
                meshData.indices.push_back(triFace->m_nodeindices[1]);
                meshData.indices.push_back(triFace->m_nodeindices[2]);
            }
        }

        PMeshModel meshModel = std::make_shared<MeshModel>(meshData);
        meshModels.push_back(meshModel);
    }
}

Import3MF::Import3MF(const std::wstring& fileName)
{
    readData(fileName);
}

MeshModels
Import3MF::meshModels() const
{ 
    return m_meshModels; 
}

bool
Import3MF::readData(const std::wstring& fileName)
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

    const uint32_t buildItemCount = model->getBuildItemCount();
    for (uint32_t i = 0; i < buildItemCount; ++i )
    {
        PModelBuildItem item = model->getBuildItem(i);

        CModelObject * object = item->getObject();

        // all component(s) is merged inot one mesh.
        PMesh mesh = std::make_shared<CMesh>();
        object->mergeToMesh(mesh.get());

        saveMeshDataPerItem(model, mesh, m_meshModels);
    }

    return true;
}
