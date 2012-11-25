#ifndef _XFILE_H_
#define _XFILE_H_

#include <d3d9.h>
#include <d3dx9.h>
class Xfile
{
private:
	LPD3DXEFFECT            gpTextureMappingShader;
	LPDIRECT3DTEXTURE9		texDM;	
	LPDIRECT3DTEXTURE9		texSM;
	LPD3DXMESH				gpSphere;
public:
	~Xfile();
	VOID SetMatrix(LPD3DXEFFECT xfile,D3DXHANDLE parameter,D3DXMATRIX *matrix);
	VOID SetTexture(LPD3DXEFFECT xfile, D3DXHANDLE parameter,LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DTEXTURE9 LoadTexture(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename);
	LPD3DXEFFECT LoadShader(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename );
	LPD3DXMESH LoadModel(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * filename);
	HRESULT InitballMesh(LPDIRECT3DDEVICE9 g_pd3dDevice,const char * texDM,const char * texSM,const char * shader,const char * model);
	VOID DrawMyballShader(D3DXMATRIX world);
	VOID set_viewprojtexture(D3DXMATRIX projection,D3DXVECTOR4 light);
	VOID set_view(D3DXMATRIX view);
};
#endif