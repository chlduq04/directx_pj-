#include "Ball.h"

Ball::Ball(){
	
}
Ball::Ball(D3DXVECTOR3 setPosition,D3DXVECTOR3 setVelocity,D3DXVECTOR3 setGoal, LPDIRECT3DDEVICE9 device){
	nLevel = 1;
	nMaxLevel = CHARACTER_MAX_LEVEL;
	bAlive = true;

	nLife = START_LIFE;
	nMaxLife = START_LIFE;

	nDef = 20;
	nMaxDef = 20;

	nMana = START_MANA;
	nMaxMana = START_MANA;

	nWeight = START_WEIGHT;
	nMaxWeight = START_WEIGHT;

	vPosition = setPosition;
	vVelocity = setVelocity;
	vGoal = setGoal;
	bGround = false;
	g_pChaModel = new Xfile();
	g_pDevice = device;
}
Ball::~Ball(){
	delete g_pChaModel;
}
void Ball::SetLife(int argu){
	nLife += argu;
	if(nLife+argu>nMaxLife)
		nLife= nMaxLife;
	if(nLife+argu<0){
		nLife= 0;
		bAlive = false;
	}
}
void Ball::SetMana(int argu){
	nMana += argu;
	if(nMana+argu>nMaxMana)
		nMana = nMaxMana;
	if(nMana+argu<0)
		nMana = 0;
}

bool Ball::SpendMana(int argu){
	if(nMana+argu<0){
		return false;
	}
	else{
		nMana += argu;
		return true;
	}
	return false;
}

void Ball::UpLevel(){
	if(nLevel>nMaxLevel){
		nLevel= nMaxLevel;
	}else{
		nLevel++;
	}

	nMaxLife = nLevel*100;
	nMaxMana = nMaxLife*50;
	nMaxWeight = nLevel*10;
	nLife = nMaxLife;
	nMana = nMaxMana;
	nWeight = nMaxWeight;
}

void Ball::DownLevel(){
	if(nLevel<=0){
		nLevel= 0;
	}else{
		nLevel--;
	}

	nMaxLife = nLevel*100;
	nMaxMana = nMaxLife*50;
	nMaxWeight = nLevel*10;
	nMaxDef = nLevel*20;

	nLife = nMaxLife;
	nMana = nMaxMana;
	nWeight = nMaxWeight;
}


void Ball::SetDefence(int argu){
	nDef += argu;
	if(nDef+argu > nMaxDef)
		nDef = nMaxDef;
	if(nDef+argu < 0)
		nLife -= nDef + argu;
}

HRESULT Ball::SetXfile(){
	if(FAILED(g_pChaModel->InitballMesh(g_pDevice,"FireBase.tga","Flame.tga","FireBall.fx","FireBall.x")))
		return E_FAIL;
	return S_OK;
}
