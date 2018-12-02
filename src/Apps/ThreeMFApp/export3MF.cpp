#include <export3MF.h>
#include <import3MF.h>

#include <Model/COM/NMR_DLLInterfaces.h>

#include <meshData.h>
#include <meshModel.h>

#include <glm/gtc/type_precision.hpp>
#include <iostream>
#include <memory>

using namespace E3D;
using namespace NMR;

namespace
{
    class CustomBase
    {
    public:
        CustomBase() : m_pLib3MFBase(nullptr) {}
        ~CustomBase()
        {
            if (m_pLib3MFBase)
            {
                lib3mf_release(m_pLib3MFBase);
                m_pLib3MFBase = nullptr;
            }
        }
        PLib3MFBase* & get() { return m_pLib3MFBase; }

    private:
        PLib3MFBase* m_pLib3MFBase;
    };
}

Export3MF::Export3MF(const std::string& fileName,  const MeshModels& meshModels)
{
    saveData(fileName, meshModels);
}

bool
Export3MF::saveData(const std::string& fileName, const MeshModels& meshModels)
{
    HRESULT hResult;

    // create model instance
    CustomBase model;
    hResult = lib3mf_createmodel( &model.get() );
        
    if (hResult != LIB3MF_OK)
    {
        std::cout << "create model failed!" << '\n';
        return false;
    }

    // write scene thumbnail

    // write mesh 
    for (auto const mesh : meshModels)
    {
        const int numVertices = mesh->getNumVertices();
        const int numTriangles = mesh->getNumTriangles();
        if (numVertices < 3 || numTriangles < 1)
        {
            return false;
        }

        // create mesh object
        CustomBase meshObject;
        hResult = lib3mf_model_addmeshobject(model.get(), &meshObject.get());
        if (hResult != LIB3MF_OK)
        {
            std::cout << "add mesh object to model failed!\n" << '\n';
            return false;
        }

        // set mesh name
        if (!mesh->getName().empty())
        {
            hResult = lib3mf_object_setnameutf8( meshObject.get(), mesh->getName().c_str());
            if (hResult != LIB3MF_OK)
            {
                std::cout << "set mesh name failed!" << '\n';
                return false;
            }
        }

        // mesh geometry
        auto vertices = mesh->getVertices();
        auto triangles = mesh->getTriangles();
        
        // vertices
        std::vector<MODELMESHVERTEX> Vertices;
        Vertices.resize(numVertices);
        for (auto i = 0; i < numVertices; ++i)
        {   
            // order matters glm::vec4 is represented as a column vector
            glm::vec4 pt = mesh->model * glm::vec4( vertices[i].position[0], 
                                                    vertices[i].position[1], 
                                                    vertices[i].position[2], 1.0f ) ;

            Vertices[i].m_fPosition[0] = pt[0];
            Vertices[i].m_fPosition[1] = pt[1];
            Vertices[i].m_fPosition[2] = pt[2];
        }

        // triangles
        std::vector<MODELMESHTRIANGLE> Triangles;
        Triangles.resize(numTriangles);

        for (auto i = 0; i < numTriangles; ++i)
        {
            for (size_t j = 0; j < 3; ++j)
            {
                Triangles[i].m_nIndices[j] = triangles[i][j];
            }
        }

        hResult = lib3mf_meshobject_setgeometry( meshObject.get(), 
                                                 &Vertices[0], 
                                                 numVertices, 
                                                 &Triangles[0], 
                                                 numTriangles );

        // set mesh thumbnail


        // add build item for Mesh
        CustomBase buildItem;
        hResult = lib3mf_model_addbuilditem( model.get(), meshObject.get(), nullptr, &buildItem.get() );
        if (hResult != LIB3MF_OK)
        {
            std::cout << "add build item failed!" << "\n";
            return false;
        }

        // create a model writer
        CustomBase writer;
        hResult = lib3mf_model_querywriter( model.get(), "3mf", &writer.get());
        if (hResult != LIB3MF_OK)
        {
            std::cout << "could not create 3MF model writer" << '\n' ;
            return false;
        }

        // write to file
        hResult = lib3mf_writer_writetofileutf8( writer.get(), fileName.c_str() );
        if (hResult != LIB3MF_OK)
        {
            std::cout << "write 3MF to file failed!" << '\n';
            return false;
        }
    }

    return true;
}
