#ifndef _SKYBOX_H_
#define _SKYBOX_H_
#include <d3dx9.h>
#include <d3d9.h>
#include "Settings.h"
struct VERTEX 
{ 
    float x, y, z; 
    float tu, tv; 
	float tu1, tv1; 
}; 
const DWORD  VERTEXFVF = D3DFVF_XYZ | D3DFVF_TEX2; 
 
class CSkyBox 
{ 
private: 
	LPDIRECT3DDEVICE9           m_pd3dDevice     ; 
    LPDIRECT3DVERTEXBUFFER9     m_pVB            ; 
    LPDIRECT3DTEXTURE9          m_pTexture[7]    ; 
public: 
	CSkyBox(LPDIRECT3DDEVICE9  pD3DDevice); 
	~CSkyBox(void); 
	HRESULT  InitVB(); 
	HRESULT  InitTexture();
	void     Render(); 
	HRESULT     SetTexture(const char * TextureFile, int ps); 
}; 
#endif