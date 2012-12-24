#ifndef _XFILE_H_
#define _XFILE_H_

#include <d3d9.h>
#include <d3dx9.h>
class Xfile
{
private:
	LPD3DXEFFECT            pTextureMappingShader;
	LPDIRECT3DTEXTURE9		pTexDM;	
	LPDIRECT3DTEXTURE9		pTexSM;
	LPD3DXMESH				pSphere;
public:
	~Xfile();
	VOID SetMatrix(LPD3DXEFFECT xfile,D3DXHANDLE parameter,D3DXMATRIX *matrix);
	VOID SetTexture(LPD3DXEFFECT xfile, D3DXHANDLE parameter,LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DTEXTURE9 LoadTexture(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename);
	LPD3DXEFFECT LoadShader(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename );
	LPD3DXMESH LoadModel(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename);
	HRESULT InitballMesh(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * texDM,const char * texSM,const char * shader,const char * model);
	VOID DrawMyballShader(D3DXMATRIX world);
	VOID SetViewprojtexture(D3DXMATRIX projection,D3DXVECTOR4 light);
	VOID SetView(D3DXMATRIX view);
};
#endif