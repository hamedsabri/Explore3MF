#include "gtest/gtest.h"

#include "Common/Mesh/NMR_Mesh.h"
#include "Common/Math/NMR_Vector.h"
#include "Common/NMR_Exception.h"
#include "Common/Mesh/NMR_MeshBuilder.h"

namespace NMR
{
	void createDummyQuad(CMesh * pMesh)
	{
		ASSERT_NE(pMesh, nullptr);

		NVEC3 vPoint1 = fnVEC3_make(0.0f, 0.0f, 10.0f);
		NVEC3 vPoint2 = fnVEC3_make(10.0f, 0.0f, 10.0f);
		NVEC3 vPoint3 = fnVEC3_make(0.0f, 10.0f, 10.0f);
		NVEC3 vPoint4 = fnVEC3_make(10.0f, 10.0f, 20.0f);

		CMeshBuilder MeshBuilder;
		MeshBuilder.addFace(vPoint1, vPoint2, vPoint3);
		MeshBuilder.addFace(vPoint3, vPoint4, vPoint1);
		MeshBuilder.addToMesh(pMesh, false);

		MESHNODE * node1 = pMesh->getNode(0);
		MESHNODE * node2 = pMesh->getNode(1);
		MESHNODE * node3 = pMesh->getNode(2);
		MESHNODE * node4 = pMesh->getNode(3);

		ASSERT_TRUE(node1->m_index == 0);
		ASSERT_TRUE(node2->m_index == 1);
		ASSERT_TRUE(node3->m_index == 2);
		ASSERT_TRUE(node4->m_index == 3);

		MESHFACE * face1 = pMesh->getFace(0);
		MESHFACE * face2 = pMesh->getFace(1);
		ASSERT_TRUE(face1->m_index == 0);
		ASSERT_TRUE(face2->m_index == 1);
		ASSERT_TRUE(pMesh->getNodeCount() == 4);
		ASSERT_TRUE(pMesh->getFaceCount() == 2);
	}


	TEST(Mesh, AddFace)
	{
		CMesh mesh1;
		createDummyQuad(&mesh1);
	}


	TEST(Mesh, MergeMesh)
	{
		CMesh mesh1, mesh2, mesh3;
		createDummyQuad(&mesh1);

		// Merge a Mesh
		mesh2.mergeMesh(&mesh1);

		// Check Mesh Topology
		ASSERT_TRUE(mesh2.getNodeCount() == 4);
		ASSERT_TRUE(mesh2.getFaceCount() == 2);

		MESHNODE * node1 = mesh2.getNode(0);
		MESHNODE * node2 = mesh2.getNode(1);
		MESHNODE * node3 = mesh2.getNode(2);
		MESHNODE * node4 = mesh2.getNode(3);

		// Check Mesh Node Positions
		ASSERT_TRUE(node1->m_index == 0);
		ASSERT_TRUE(node2->m_index == 1);
		ASSERT_TRUE(node3->m_index == 2);
		ASSERT_TRUE(node4->m_index == 3);
		ASSERT_EQ(node1->m_position.m_values.x, 0.0f);
		ASSERT_EQ(node1->m_position.m_values.y, 0.0f);
		ASSERT_EQ(node1->m_position.m_values.z, 10.0f);
		ASSERT_EQ(node2->m_position.m_values.x, 10.0f);
		ASSERT_EQ(node2->m_position.m_values.y, 0.0f);
		ASSERT_EQ(node2->m_position.m_values.z, 10.0f);
		ASSERT_EQ(node3->m_position.m_values.x, 0.0f);
		ASSERT_EQ(node3->m_position.m_values.y, 10.0f);
		ASSERT_EQ(node3->m_position.m_values.z, 10.0f);
		ASSERT_EQ(node4->m_position.m_values.x, 10.0f);
		ASSERT_EQ(node4->m_position.m_values.y, 10.0f);
		ASSERT_EQ(node4->m_position.m_values.z, 20.0f);

		// Check Node Indices
		MESHFACE * face1 = mesh2.getFace(0);
		MESHFACE * face2 = mesh2.getFace(1);
		ASSERT_TRUE(face1->m_index == 0);
		ASSERT_TRUE(face2->m_index == 1);
		ASSERT_TRUE(face1->m_nodeindices[0] == 0);
		ASSERT_TRUE(face1->m_nodeindices[1] == 1);
		ASSERT_TRUE(face1->m_nodeindices[2] == 2);
		ASSERT_TRUE(face2->m_nodeindices[0] == 2);
		ASSERT_TRUE(face2->m_nodeindices[1] == 3);
		ASSERT_TRUE(face2->m_nodeindices[2] == 0);

		// Check Invalid Parameter Call
		try
		{
			mesh3.mergeMesh(NULL);
			ASSERT_TRUE(false);
		}
		catch (CNMRException e)
		{
			ASSERT_TRUE(e.getErrorCode() == NMR_ERROR_INVALIDPARAM);
		}


	}

	TEST(Mesh, AddToMesh)
	{
		CMesh mesh1, mesh2;
		createDummyQuad(&mesh1);

		// Merge a Mesh
		mesh1.addToMesh(&mesh2);

		// Check Mesh Topology
		ASSERT_TRUE(mesh2.getNodeCount() == 4);
		ASSERT_TRUE(mesh2.getFaceCount() == 2);

		MESHNODE * node1 = mesh2.getNode(0);
		MESHNODE * node2 = mesh2.getNode(1);
		MESHNODE * node3 = mesh2.getNode(2);
		MESHNODE * node4 = mesh2.getNode(3);

		// Check Mesh Node Positions
		ASSERT_TRUE(node1->m_index == 0);
		ASSERT_TRUE(node2->m_index == 1);
		ASSERT_TRUE(node3->m_index == 2);
		ASSERT_TRUE(node4->m_index == 3);
		ASSERT_EQ(node1->m_position.m_values.x, 0.0f);
		ASSERT_EQ(node1->m_position.m_values.y, 0.0f);
		ASSERT_EQ(node1->m_position.m_values.z, 10.0f);
		ASSERT_EQ(node2->m_position.m_values.x, 10.0f);
		ASSERT_EQ(node2->m_position.m_values.y, 0.0f);
		ASSERT_EQ(node2->m_position.m_values.z, 10.0f);
		ASSERT_EQ(node3->m_position.m_values.x, 0.0f);
		ASSERT_EQ(node3->m_position.m_values.y, 10.0f);
		ASSERT_EQ(node3->m_position.m_values.z, 10.0f);
		ASSERT_EQ(node4->m_position.m_values.x, 10.0f);
		ASSERT_EQ(node4->m_position.m_values.y, 10.0f);
		ASSERT_EQ(node4->m_position.m_values.z, 20.0f);

		// Check Node Indices
		MESHFACE * face1 = mesh2.getFace(0);
		MESHFACE * face2 = mesh2.getFace(1);
		ASSERT_TRUE(face1->m_index == 0);
		ASSERT_TRUE(face2->m_index == 1);
		ASSERT_TRUE(face1->m_nodeindices[0] == 0);
		ASSERT_TRUE(face1->m_nodeindices[1] == 1);
		ASSERT_TRUE(face1->m_nodeindices[2] == 2);
		ASSERT_TRUE(face2->m_nodeindices[0] == 2);
		ASSERT_TRUE(face2->m_nodeindices[1] == 3);
		ASSERT_TRUE(face2->m_nodeindices[2] == 0);

		// Check Invalid Parameter Call
		try
		{
			mesh1.addToMesh(NULL);
			ASSERT_TRUE(false);
		}
		catch (CNMRException e)
		{
			ASSERT_TRUE(e.getErrorCode() == NMR_ERROR_INVALIDPARAM);
		}


	}

	TEST(Mesh, CreateFrom)
	{
		CMesh mesh1;
		createDummyQuad(&mesh1);

		// Test CreateFrom Constructor
		PMesh mesh2 (new CMesh (&mesh1));

		// Check Mesh Topology
		ASSERT_TRUE(mesh2->getNodeCount() == 4);
		ASSERT_TRUE(mesh2->getFaceCount() == 2);

		MESHNODE * node1 = mesh2->getNode(0);
		MESHNODE * node2 = mesh2->getNode(1);
		MESHNODE * node3 = mesh2->getNode(2);
		MESHNODE * node4 = mesh2->getNode(3);

		// Check Mesh Node Positions
		ASSERT_TRUE(node1->m_index == 0);
		ASSERT_TRUE(node2->m_index == 1);
		ASSERT_TRUE(node3->m_index == 2);
		ASSERT_TRUE(node4->m_index == 3);
		ASSERT_EQ(node1->m_position.m_values.x, 0.0f);
		ASSERT_EQ(node1->m_position.m_values.y, 0.0f);
		ASSERT_EQ(node1->m_position.m_values.z, 10.0f);
		ASSERT_EQ(node2->m_position.m_values.x, 10.0f);
		ASSERT_EQ(node2->m_position.m_values.y, 0.0f);
		ASSERT_EQ(node2->m_position.m_values.z, 10.0f);
		ASSERT_EQ(node3->m_position.m_values.x, 0.0f);
		ASSERT_EQ(node3->m_position.m_values.y, 10.0f);
		ASSERT_EQ(node3->m_position.m_values.z, 10.0f);
		ASSERT_EQ(node4->m_position.m_values.x, 10.0f);
		ASSERT_EQ(node4->m_position.m_values.y, 10.0f);
		ASSERT_EQ(node4->m_position.m_values.z, 20.0f);

		// Check Node Indices
		MESHFACE * face1 = mesh2->getFace(0);
		MESHFACE * face2 = mesh2->getFace(1);
		ASSERT_TRUE(face1->m_index == 0);
		ASSERT_TRUE(face2->m_index == 1);
		ASSERT_TRUE(face1->m_nodeindices[0] == 0);
		ASSERT_TRUE(face1->m_nodeindices[1] == 1);
		ASSERT_TRUE(face1->m_nodeindices[2] == 2);
		ASSERT_TRUE(face2->m_nodeindices[0] == 2);
		ASSERT_TRUE(face2->m_nodeindices[1] == 3);
		ASSERT_TRUE(face2->m_nodeindices[2] == 0);

		// Check Invalid Parameter Call
		try
		{
			PMesh mesh3(new CMesh(NULL));
			ASSERT_TRUE(false);
		}
		catch (CNMRException e)
		{
			ASSERT_TRUE(e.getErrorCode() == NMR_ERROR_INVALIDPARAM);
		}

	}

}