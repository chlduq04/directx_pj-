#include "Ui.h"

HRESULT Ui::initBillboard(LPDIRECT3DDEVICE9 device, const char* image_name,LPDIRECT3DTEXTURE9* texture){
	D3DXCreateTextureFromFile( device, image_name, texture );
	return S_OK;
}
