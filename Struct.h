#ifndef _STRUCT_H_
#define _STRUCT_H_

struct VERTEX 
{ 
    float x, y, z; 
    float tu, tv; 
	float tu1, tv1; 
}; 
struct MYVERTEX
{
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
	float px, py, pz;
	float tu, tv;

};
struct RASERVERTEX
{
	D3DXVECTOR3 pos;
	DWORD diffuse;
};
#endif
