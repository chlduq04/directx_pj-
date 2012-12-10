#ifndef _STRUCT_H_
#define _STRUCT_H_

struct MYVERTEX
{
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
	float px, py, pz;
	float tu, tv;

};

struct MonMissile
{
	D3DXVECTOR3 vPosition; //위치
	D3DXVECTOR3 vVelocity; //방향벡터
	D3DXVECTOR3 vGoal;
	int demage;
};

#endif
