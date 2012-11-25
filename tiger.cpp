#include "tiger.h"

Tiger::Tiger(D3DXMATRIX position){
	vPosition = position;
}
D3DXMATRIX Tiger::hisPosition(){
	return vPosition;
}
