#ifndef _UI_H_
#define _UI_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Struct.h"

class Ui{
private:
	float win_width;
	float win_height;
public:
	Ui(float width,float height);
	VOID setUI(LPDIRECT3DDEVICE9 device);
	VOID setCenUI(LPDIRECT3DDEVICE9 device);
	VOID drawBillboard(LPDIRECT3DDEVICE9 device,LPDIRECT3DTEXTURE9 texture,D3DXMATRIX* matworld,float tranx, float trany, float tranz, MYVERTEX* vtx);
	HRESULT initBillboard(LPDIRECT3DDEVICE9 device, const char* image_name,LPDIRECT3DTEXTURE9* texture);
};
#endif