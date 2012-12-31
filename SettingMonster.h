#ifndef _SETTINGMONSTER_H_
#define _SETTINGMONSTER_H_
#include <d3dx9.h>
#include <d3d9.h>
#include "Ball.h"
#include "Monster.h"
#include "CModel.h"
#include "CheckAI.h"
#include "Missile.h"
#include "Xfile.h"
#include "Wall.h"
#include "Moving.h"
#include "Monai.h"
class SettingMonster{
private:
	BOOL				g_bWall;
	FLOAT				g_m_fStartTime;
	FLOAT				fCrashTime;
	BOOL				bCrash;
	D3DXMATRIX			g_matSetScale;
	D3DXMATRIX			g_matSetTrans;
	D3DXMATRIX			g_matSetWorld;

	Monai*				g_pMonAi;
	Moving*				g_pMove;
	Monster*			g_pMonster;
	Ball*				g_pCha;
	Xfile*				g_pMissileModel;
	Xfile*				g_pWallModel;
	Checkai*			g_pCheck;
	CModel*				g_pMonModel;
	LPDIRECT3DDEVICE9	g_pDevice;
	Missile*			g_pMissile[MISSILE_COUNT];
	Wall*				g_pWall;
public:
	SettingMonster(LPDIRECT3DDEVICE9 device,Ball* cha, Moving* move, FLOAT time);
	~SettingMonster();
	HRESULT	SetXfile();
	VOID Draw();
	VOID DrawWall();
	inline CModel*		GetModel(){return g_pMonModel;};
	inline Checkai*		GetCheckai(){return g_pCheck;};
	inline Missile**	GetMissile(){return g_pMissile;};
	inline Monster*		GetMonster(){return g_pMonster;};
	inline Wall*		GetWall(){return g_pWall;};
	VOID CrashMissile();
	VOID SetViewMatrix(D3DXMATRIX view);
	VOID SetProjectionMatrix(D3DXMATRIX proj,D3DXVECTOR4 light);
	inline VOID GetPositionMon(FLOAT time){g_pMonAi->GetPositionMon(time);};
	inline D3DXMATRIX DrawPosition(D3DXVECTOR3 scale,/**/D3DXVECTOR3 trans)
	{
		D3DXMatrixIdentity(&g_matSetWorld);
		D3DXMatrixScaling(&g_matSetScale,scale.x,scale.y,scale.z);
		D3DXMatrixTranslation(&g_matSetTrans,trans.x,trans.y,trans.z);
		return g_matSetWorld * g_matSetScale * g_matSetTrans;
	};
	VOID CrashMon(FLOAT time);
	inline VOID MonsterPosition(FLOAT speed){
		if(	!g_pMonster->IsbGround()){
			g_pMonster->SetPosition(g_pMonster->GetPosition()+g_pMonster->GetVelocity()*speed);
			if(g_pMonster->GetVelocity().y>0)
				g_pMonster->SetVelocityY(g_pMonster->GetVelocity().y-(GRAVITY+REVERSE_GRAVITY)*BALLSPEED*speed);
			else
				g_pMonster->SetVelocityY(g_pMonster->GetVelocity().y-(GRAVITY*BALLSPEED*speed/10));

			if( g_pMonster->GetPosition().y < -GROUND + ( MON_SIZE* 0.5f ) )
			{
				g_pMonster->SetPositionY(-GROUND + ( MON_SIZE * 0.5f ));
				g_pMonster->SetVelocityY(-g_pMonster->GetVelocity().y* ( 1 - ABSORBANCE )*speed);
			}
		}
		if(g_pMonster->GetPosition().x>MAXBOUNDX){
			g_pMonster->SetPositionX(MAXBOUNDX);
		}
		if(g_pMonster->GetPosition().x<MINBOUNDX){
			g_pMonster->SetPositionX(MINBOUNDX);
		}
		if(g_pMonster->GetPosition().z>MAXBOUNDZ){
			g_pMonster->SetPositionZ(MAXBOUNDZ);
		}
		if(g_pMonster->GetPosition().z<MINBOUNDZ){
			g_pMonster->SetPositionZ(MINBOUNDZ);
		}
		if(g_pMonster->GetPosition().y>MAXBOUNDY){
			g_pMonster->SetPositionY(MAXBOUNDY);
		}
		if(g_pMonster->GetPosition().y<MINBOUNDY){
			g_pMonster->SetPositionY(MINBOUNDY);
		}
	};
};
#endif