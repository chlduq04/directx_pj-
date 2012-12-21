#ifndef _UI_H_
#define _UI_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Struct.h"
#include "Settings.h"
class Ui{
private:
	LPDIRECT3DDEVICE9 d3dDevice;
	float win_width;
	float win_height;
public:
	Ui(LPDIRECT3DDEVICE9 device);
	VOID setUI();
	VOID setCenUI();
	VOID drawBillboard(LPDIRECT3DTEXTURE9 texture,D3DXMATRIX* matworld,float tranx, float trany, float tranz, MYVERTEX* vtx);
	HRESULT initBillboard(const char* image_name,LPDIRECT3DTEXTURE9* texture);
};
#endif