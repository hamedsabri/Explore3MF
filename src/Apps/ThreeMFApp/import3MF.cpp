#include <import3MF.h>

#include <assert.h>

#include <iostream>
#include <vector>

using namespace E3D;
using namespace NMR;

Import3MF::Import3MF(const std::string& fileName)
{
    readData(fileName);
}

HRESULT
Import3MF::readData(const std::string& fileName) const
{
    HRESULT hResult;

    PLib3MFModel * pModel;
    PLib3MFModelReader * p3MFReader;
    PLib3MFModelResourceIterator * pResourceIterator;
    BOOL pbHasNext;
    BOOL bIsMeshObject;

    lib3mf_createmodel(&pModel);

    // read in model from 3MF file
    lib3mf_model_queryreader(pModel, "3mf", &p3MFReader);
    hResult = lib3mf_reader_readfromfileutf8(p3MFReader, fileName.c_str());

    if (hResult != LIB3MF_OK) 
    {
        lib3mf_release(pModel);
        return hResult;
    }

    // iterate through all the resources
    hResult = lib3mf_model_getresources(pModel, &pResourceIterator);
    if (hResult != LIB3MF_OK) 
    {
        lib3mf_release(pModel);
        return hResult;
    }

    // iterates to the next resource in the list.
    hResult = lib3mf_resourceiterator_movenext( pResourceIterator, &pbHasNext );
    if (hResult != LIB3MF_OK)
    {
        lib3mf_release(pResourceIterator);
        lib3mf_release(pModel);
        return hResult;
    }

    while (pbHasNext)
    {
        PLib3MFModelResource * pResource;
        PLib3MFModelMeshObject * pMeshObject;
        ModelResourceID ResourceID;

        // get current resource
        hResult = lib3mf_resourceiterator_getcurrent(pResourceIterator, &pResource);
        if (hResult != LIB3MF_OK) 
        {
            lib3mf_release(pResourceIterator);
            lib3mf_release(pModel);
            return hResult;
        }

        // get resource ID
        hResult = lib3mf_resource_getresourceid(pResource, &ResourceID);
        if (hResult != LIB3MF_OK) 
        {
            lib3mf_release(pResource);
            lib3mf_release(pResourceIterator);
            lib3mf_release(pModel);
            return hResult;
        }

        std::cout << "ResourceID: " << ResourceID << '\n';

        // query mesh interface
        hResult = lib3mf_object_ismeshobject(pResource, &bIsMeshObject);
        if ((hResult == LIB3MF_OK) && bIsMeshObject ) 
        {
            if (bIsMeshObject)
            {
                 pMeshObject = pResource;

                 // parse mesh object information
                 hResult = parseMeshObject(pMeshObject);
                 if (hResult != LIB3MF_OK) 
                 {
                     lib3mf_release(pMeshObject);
                     lib3mf_release(pResourceIterator);
                     lib3mf_release(pModel);
                     return false;
                 }
            }
        }

        // iterates to the next resource in the list.
        hResult = lib3mf_resourceiterator_movenext(pResourceIterator, &pbHasNext);
        if (hResult != LIB3MF_OK) 
        {
            return hResult;
        }
    }

    // release
    lib3mf_release(pModel);
    lib3mf_release(p3MFReader);
    lib3mf_release(pResourceIterator);

    return LIB3MF_OK;
}

HRESULT
Import3MF::parseMeshObject(PLib3MFModelMeshObject * pMeshObject) const
{
    std::cout << "======= Parsing Mesh Object Begin =======" << '\n';

    HRESULT hResult;

    DWORD vertCount = 0;
    DWORD triCount = 0;

    // retrieve mesh vertex count
    hResult = lib3mf_meshobject_getvertexcount(pMeshObject, &vertCount);
    if (hResult != LIB3MF_OK)
        return hResult;

    // retrieve mesh triangle count
    hResult = lib3mf_meshobject_gettrianglecount(pMeshObject, &triCount);
    if (hResult != LIB3MF_OK)
        return hResult;

    std::cout << "Vertex count:" << vertCount << '\n';
    std::cout << "Triangle count:" << triCount << '\n';

    assert(vertCount > 3);
    assert(triCount > 1);

    DWORD pnVertexCount = 0;
    DWORD pnTriangleCount = 0;

    // vertex positions ( x, y, z )
    std::vector<MODELMESHVERTEX> pVertices(vertCount);

    MODELMESHVERTEX * pVtx = &pVertices[0];

    hResult = lib3mf_meshobject_getvertices(pMeshObject, pVtx, vertCount, &pnVertexCount);

    if (hResult != LIB3MF_OK)
        return hResult;

    assert(pnVertexCount == vertCount);

    for (uint32_t nIndex = 0; nIndex < vertCount; ++nIndex)
    {
        std::cout << "Vertex[" << nIndex << "]" << ": " << pVtx->m_fPosition[0]
                                                << ", " << pVtx->m_fPosition[1]
                                                << ", " << pVtx->m_fPosition[2] << '\n';
        ++pVtx;
    }

    // triangle indices
    std::vector<MODELMESHTRIANGLE> pTriangles(triCount);

    MODELMESHTRIANGLE *pTri = &pTriangles[0];

    hResult = lib3mf_meshobject_gettriangleindices(pMeshObject, pTri, triCount, &pnTriangleCount);

    if (hResult != LIB3MF_OK)
        return hResult;

    assert(pnTriangleCount == triCount);

    for (uint32_t nIndex = 0; nIndex < triCount; ++nIndex)
    {
        std::cout << "Triangle[" << nIndex << "]" << ": "
                                 << pTri->m_nIndices[0] << ", "
                                 << pTri->m_nIndices[1] << ", "
                                 << pTri->m_nIndices[2] << '\n';
        ++pTri;
    }

    std::cout << "======= Parsing Mesh Object End =======" << '\n';

    return LIB3MF_OK;
}
