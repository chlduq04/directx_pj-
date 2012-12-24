#ifndef _UI_H_
#define _UI_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Struct.h"
#include "Settings.h"
class Ui{
private:
	LPDIRECT3DDEVICE9 d3dDevice;
	float fWinWidth;
	float fWinHeight;
public:
	Ui(LPDIRECT3DDEVICE9 device);
	VOID SetUI();
	VOID SetCenUI();
	VOID DrawBillboard(LPDIRECT3DTEXTURE9 texture,D3DXMATRIX* matworld,float tranx, float trany, float tranz, MYVERTEX* vtx);
	HRESULT InitBillboard(const char* image_name,LPDIRECT3DTEXTURE9* texture);
};
#endif