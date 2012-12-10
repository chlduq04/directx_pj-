/////////////////////////////////////////////////
//
// File: "CModel.h"
//
// Author: Jason Jurecka
//
// Creation Date: June 5, 2003
//
// Purpose: This is a wrapper for the DirectX functions
//	that work with models. This class when completed
//	will allow for loading, drawing, texturing, and
//	model animation.
//
// Note: This was written for DirectX version 9
//	Each instance of this class = one model
//
//		In the future could add functionality to 
//		load files in other formats for DirectX
//		and if I feel up too it OpenGL
/////////////////////////////////////////////////

#ifndef _MODEL_H_
#define _MODEL_H_

#include <d3dx9.h>
#include <d3dx9anim.h>
#include "CAllocateHierarchy.h"
#include "DerivedStructs.h"
#include "Macros.h"

#define SHADOWFVF D3DFVF_XYZRHW | D3DFVF_DIFFUSE //The FVF for the shadow vertex

class CModel  
{
private:
	
	LPDIRECT3DDEVICE9	m_pd3dDevice;			//The d3d device to use
	//Model
	LPMESHCONTAINER		m_pFirstMesh;			// The first mesh in the hierarchy
	LPD3DXFRAME			m_pFrameRoot;			// Frame hierarchy of the model
	LPD3DXMATRIX		m_pBoneMatrices;		// Used when calculating the bone position
	D3DXVECTOR3			m_vecCenter;			// Center of bounding sphere of object
    float               m_fRadius;				// Radius of bounding sphere of object
	UINT				m_uMaxBones;			// The Max number of bones for the model
	//Animation
	DWORD				m_dwCurrentAnimation;	// The current animation
	DWORD				m_dwAnimationSetCount;	// Number of animation sets
	LPD3DXANIMATIONCONTROLLER   m_pAnimController;// Controller for the animations

	void DrawFrame(LPFRAME pFrame);
	void SetupBoneMatrices(LPFRAME pFrame, LPD3DXMATRIX pParentMatrix);
	void UpdateFrameMatrices(LPFRAME pFrame, LPD3DXMATRIX pParentMatrix);
public:
	CModel(LPDIRECT3DDEVICE9 pD3DDevice);
	virtual ~CModel();
	CModel &operator=(const CModel&){}
	CModel(const CModel&){}
	inline void setBoundingSphereCenter(D3DXVECTOR3 position)
	{ m_vecCenter = position; }
	inline LPD3DXVECTOR3 GetBoundingSphereCenter()
	{ return &m_vecCenter; }
	inline float GetBoundingSphereRadius()
	{ return m_fRadius; }
	inline DWORD GetCurrentAnimation()
	{ return m_dwCurrentAnimation; }
	void SetCurrentAnimation(DWORD dwAnimationFlag);
	void Draw();
	HRESULT LoadXFile(char* strFileName);
	void Update(double dElapsedTime);
};

#endif