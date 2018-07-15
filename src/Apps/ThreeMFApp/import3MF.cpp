#include <import3MF.h>

#include <Common/Platform/NMR_ImportStream_GCC_Native.h>
#include <Common/MeshInformation/NMR_MeshInformation_BaseMaterials.h>

#include <Model/Reader/NMR_ModelReader_3MF_Native.h>
#include <Model/Classes/NMR_ModelBuildItem.h>
#include <Model/Classes/NMR_ModelBaseMaterial.h>
#include <Model/Classes/NMR_ModelBaseMaterials.h>

#include <meshModel.h>

#include <assert.h>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace E3D;
using namespace NMR;

namespace
{
    using PIndexToColorValue = std::unordered_map<ModelResourceIndex, std::string>;
    using PIdToBasematerial = std::unordered_map<ModelResourceID, PIndexToColorValue>;

    glm::i16vec4
    hex2rgb(std::string& hex)
    {
        glm::i16vec4 color;

        // drop a hash if the value has one
        if (hex[0] == '#') {
            hex.erase(0,1);
        }

        std::istringstream(hex.substr(0, 2)) >> std::hex >> color.r;
        std::istringstream(hex.substr(2, 2)) >> std::hex >> color.g;
        std::istringstream(hex.substr(4, 2)) >> std::hex >> color.b;
        std::istringstream(hex.substr(6, 2)) >> std::hex >> color.a;

        return color;
    }

    PIdToBasematerial
    baseMaterialData(PModel model)
    {
        PIndexToColorValue indexToColorValue;
        PIdToBasematerial idToBasematerials;

        for (uint32_t i = 0; i < model->getBaseMaterialCount(); ++i)
        {
            for (uint32_t j = 0; j < model->getBaseMaterial(i)->getCount(); ++j)
            {
                auto pMaterial = model->getBaseMaterial(i)->getBaseMaterial(j);
                indexToColorValue.insert(std::make_pair(j, pMaterial->getDisplayColorString()));
            }

            idToBasematerials.insert(std::make_pair(model->getBaseMaterialResource(i)->getResourceID()->getUniqueID(), indexToColorValue));
        }

        return idToBasematerials;
    }

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

    glm::mat4
    getItemTransform(PModel model, PModelBuildItem item)
    {
        // row major order
        NMATRIX3 m = item->getTransform();

        // scale
        auto scale = static_cast<float>(getUnitScale(model));
        glm::mat4 M = glm::mat4(1.0f);
        M = glm::scale(M, glm::vec3(scale));

        // column major order ( affine transformation matrix )
        glm::mat4 T( m.m_fields[0][0], m.m_fields[1][0], m.m_fields[2][0], 0.0f,  
                     m.m_fields[0][1], m.m_fields[1][1], m.m_fields[2][1], 0.0f,  
                     m.m_fields[0][2], m.m_fields[1][2], m.m_fields[2][2], 0.0f, 
                     m.m_fields[0][3], m.m_fields[1][3], m.m_fields[2][3], 1.0f );

        // order matters
        T = M * T;

        return T;
    }

    void
    saveMeshDataPerItem( PModel model,
                         PMesh mesh,
                         std::vector<PMeshModel>& meshModels,
                         PIdToBasematerial& baseMaterialMap,
                         const glm::mat4& transform)
    {
        MeshData meshData;

        const uint32_t vertsCount = mesh->getNodeCount();
        const uint32_t faceCount = mesh->getFaceCount();
        assert( faceCount > 0 );
        assert( vertsCount > 0 );

        CMeshInformationHandler * pMeshInformationHandler = mesh->getMeshInformationHandler();
        CMeshInformation * pInformation = nullptr;
        glm::vec4 baseMaterialColor;

        for( uint32_t index = 0; index < faceCount; ++index )
        {
            pInformation = pMeshInformationHandler->getInformationByType(0, emiBaseMaterials);

            if (pInformation->faceHasData(index))
            {
                CMeshInformation_BaseMaterials * pBaseMaterials = static_cast<CMeshInformation_BaseMaterials*>(pInformation);

                MESHINFORMATION_BASEMATERIAL * pFaceData = reinterpret_cast<MESHINFORMATION_BASEMATERIAL*>(pBaseMaterials->getFaceData(index));

                ModelResourceID pid = pFaceData->m_nMaterialGroupID;
                ModelResourceIndex pindex = pFaceData->m_nMaterialIndex;

                //std::cout << "PId:" << pid << ", " << "PIndex:" << pindex << '\n';

                auto refIt = baseMaterialMap.find(pid);
                if (refIt != baseMaterialMap.end())
                {
                    auto indexToColorValue = refIt->second;
                    auto colorRefIt = indexToColorValue.find(pindex);
                    if (colorRefIt != indexToColorValue.end())
                    {
                        auto RGBAValues = hex2rgb(colorRefIt->second);

                        baseMaterialColor = glm::vec4( RGBAValues.r / 255.0f,
                                                       RGBAValues.g / 255.0f,
                                                       RGBAValues.b / 255.0f,
                                                       RGBAValues.a / 255.0f );
                    }
                }

                // indices
                auto triFace = mesh->getFace(index);

                meshData.indices.push_back(triFace->m_nodeindices[0]);
                meshData.indices.push_back(triFace->m_nodeindices[1]);
                meshData.indices.push_back(triFace->m_nodeindices[2]);
            }
        }

        for( uint32_t index = 0; index < vertsCount; ++index )
        {
            Vertex vertex;

            auto node = mesh->getNode( index );

            // position
            vertex.position = glm::vec3( node->m_position.m_fields[0],
                                         node->m_position.m_fields[1], 
                                         node->m_position.m_fields[2] );
            // color
            vertex.color = baseMaterialColor;

            meshData.vertices.push_back(vertex);
        }

        PMeshModel meshModel = std::make_shared<MeshModel>(meshData);
        meshModel->setAffineTransformMatrix(transform);

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

    PIdToBasematerial baseMaterialsMap = baseMaterialData(model);

    const uint32_t buildItemCount = model->getBuildItemCount();
    for (uint32_t i = 0; i < buildItemCount; ++i )
    {
        PModelBuildItem item = model->getBuildItem(i);

        CModelObject * object = item->getObject();

        // all component(s) is merged into one mesh.
        PMesh mesh = std::make_shared<CMesh>();
        object->mergeToMesh(mesh.get());

        // item transformation
        const glm::mat4& M = getItemTransform(model, item);

        saveMeshDataPerItem(model, mesh, m_meshModels, baseMaterialsMap, M);
    }

    return true;
}
