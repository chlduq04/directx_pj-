#ifndef _TIGER_H_
#define _TIGER_H_

#include <d3d9.h>
#include <d3dx9.h>

class Tiger{
private:
	D3DXMATRIXA16 vPosition; 
public:
	Tiger(D3DXMATRIX position);
	D3DXMATRIX hisPosition();
};
#endif 