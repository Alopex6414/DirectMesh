/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectMesh.cpp
* @brief	This File is DirectX Library Common Header.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-06-25	v1.00a	alopex	Create This File.
*/
#include "DirectCommon.h"
#include "DirectMesh.h"
#include "DirectThreadSafe.h"

//------------------------------------------------------------------
// @Function:	 DirectMesh()
// @Purpose: DirectMesh构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectMesh::DirectMesh()
{
	m_bThreadSafe = true;									//线程安全
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//初始化临界区

	m_pD3D9Device = NULL;
	m_pD3DXMeshCube = NULL;
	m_pD3DXMeshSphere = NULL;
	m_pD3DXMeshCylinder = NULL;
	m_pD3DXMeshTorus = NULL;
	m_pD3DXMeshPolygon = NULL;
	m_pD3DXMeshTeapot = NULL;
}

//------------------------------------------------------------------
// @Function:	 ~DirectMesh()
// @Purpose: DirectMesh析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectMesh::~DirectMesh()
{
	SAFE_RELEASE(m_pD3DXMeshCube);
	SAFE_RELEASE(m_pD3DXMeshSphere);
	SAFE_RELEASE(m_pD3DXMeshCylinder);
	SAFE_RELEASE(m_pD3DXMeshTorus);
	SAFE_RELEASE(m_pD3DXMeshPolygon);
	SAFE_RELEASE(m_pD3DXMeshTeapot);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//删除临界区
}

//------------------------------------------------------------------
// @Function:	 DirectMesh()
// @Purpose: DirectMesh构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectMesh::DirectMesh(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_bThreadSafe = true;									//线程安全
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//初始化临界区

	m_pD3D9Device = pD3D9Device;
	m_pD3DXMeshCube = NULL;
	m_pD3DXMeshSphere = NULL;
	m_pD3DXMeshCylinder = NULL;
	m_pD3DXMeshTorus = NULL;
	m_pD3DXMeshPolygon = NULL;
	m_pD3DXMeshTeapot = NULL;
}

//------------------------------------------------------------------
// @Function:	 DirectMeshInitCube()
// @Purpose: DirectMesh初始化立方体
// @Since: v1.00a
// @Para: FLOAT fWidth(Cube立方体X轴向宽度)
// @Para: FLOAT fHeight(Cube立方体Y轴向高度)
// @Para: FLOAT fDepth(Cube立方体Z轴向深度)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshInitCube(FLOAT fWidth, FLOAT fHeight, FLOAT fDepth)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateBox(m_pD3D9Device, fWidth, fHeight, fDepth, &m_pD3DXMeshCube, NULL);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshInitCylinder()
// @Purpose: DirectMesh初始化柱体
// @Since: v1.00a
// @Para: FLOAT fRadius1(Cylinder柱体沿Z轴负方向的半径大小)
// @Para: FLOAT fRadius2(Cylinder柱体沿Z正方向的半径大小)
// @Para: FLOAT fLength(Cylinder柱体沿Z轴的长度)
// @Para: UINT nSlices(Cylinder柱体的外围有几个面)
// @Para: UINT nStacks(Cylinder柱体的两端间共有几段)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshInitCylinder(FLOAT fRadius1, FLOAT fRadius2, FLOAT fLength, UINT nSlices, UINT nStacks)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateCylinder(m_pD3D9Device, fRadius1, fRadius2, fLength, nSlices, nStacks, &m_pD3DXMeshCylinder, NULL);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshInitSphere()
// @Purpose: DirectMesh初始化球面体
// @Since: v1.00a
// @Para: FLOAT fRadius(Sphere球面体沿Z轴直径大小)
// @Para: UINT nSlices(Sphere球面体绕主轴线切片数)
// @Para: UINT nStacks(Sphere球面体绕主轴线的纬线数)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshInitSphere(FLOAT fRadius, UINT nSlices, UINT nStacks)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateSphere(m_pD3D9Device, fRadius, nSlices, nStacks, &m_pD3DXMeshSphere, NULL);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshInitTorus()
// @Purpose: DirectMesh初始化圆环体
// @Since: v1.00a
// @Para: FLOAT fInnerRadius(Torus圆环体内直径)
// @Para: FLOAT fOuterRadius(Torus圆环体外直径)
// @Para: UINT nSides(Torus圆环的外圈有几个面)
// @Para: UINT nRings(Torus圆环的内圈有几个面)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshInitTorus(FLOAT fInnerRadius, FLOAT fOuterRadius, UINT nSides, UINT nRings)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateTorus(m_pD3D9Device, fInnerRadius, fOuterRadius, nSides, nRings, &m_pD3DXMeshTorus, NULL);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshInitPolygon()
// @Purpose: DirectMesh初始化多面体
// @Since: v1.00a
// @Para: FLOAT fLength(多面体边长)
// @Para: UINT nSides(多面体边数)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshInitPolygon(FLOAT fLength, UINT nSides)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreatePolygon(m_pD3D9Device, fLength, nSides, &m_pD3DXMeshPolygon, NULL);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshInitTeaport()
// @Purpose: DirectMesh初始化茶壶
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshInitTeapot()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateTeapot(m_pD3D9Device, &m_pD3DXMeshTeapot, NULL);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetCube()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshDrawSubsetCube()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshCube->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetCylinder()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshDrawSubsetCylinder()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshCylinder->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetSphere()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshDrawSubsetSphere()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshSphere->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetTorus()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshDrawSubsetTorus()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshTorus->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetPolygon()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshDrawSubsetPolygon()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshPolygon->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetTeaport()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMODE DirectMesh::DirectMeshDrawSubsetTeapot()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshTeapot->DrawSubset(0);
}