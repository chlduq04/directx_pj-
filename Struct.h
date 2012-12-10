#ifndef _STRUCT_H_
#define _STRUCT_H_

struct MYVERTEX
{
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
	float px, py, pz;
	float tu, tv;

};

#endif
