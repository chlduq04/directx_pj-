#ifndef _UI_H_
#define _UI_H_

#include <d3d9.h>
#include <d3dx9.h>

class Ui{
private:
public:
	HRESULT initBillboard(LPDIRECT3DDEVICE9 device, const char* image_name,LPDIRECT3DTEXTURE9* texture);
};
#endif