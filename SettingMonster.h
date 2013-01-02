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
#include "ZCamera.h"
class SettingMonster{
private:
	D3DXMATRIX			g_matRotation;
	D3DXVECTOR3			g_matInit;
	D3DXVECTOR3			g_matAngle;
	BOOL				g_bWall;
	FLOAT				g_m_fStartTime;
	FLOAT				fCrashTime;
	BOOL				bCrash;
	D3DXMATRIX			g_matSetScale;
	D3DXMATRIX			g_matSetTrans;
	D3DXMATRIX			g_matSetWorld;
	D3DXMATRIX			g_matSetRotate;

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
	VOID Draw(LPD3DXMATRIX monworld,LPD3DXMATRIX originview,ZCamera* camera,FLOAT time,FLOAT speed,INT cameracase);
	inline CModel*		GetModel(){return g_pMonModel;};
	inline Checkai*		GetCheckai(){return g_pCheck;};
	inline Missile**	GetMissile(){return g_pMissile;};
	inline Monster*		GetMonster(){return g_pMonster;};
	inline Wall*		GetWall(){return g_pWall;};
	VOID SetViewMatrix(D3DXMATRIX view);
	VOID SetProjectionMatrix(D3DXMATRIX proj,D3DXVECTOR4 light);
	inline VOID GetPositionMon(FLOAT time){g_pMonAi->GetPositionMon(time);};
	inline D3DXMATRIX DrawPosition(D3DXMATRIX* world,/**/D3DXVECTOR3 scale,/**/D3DXVECTOR3 trans)
	{
		D3DXMatrixIdentity(world);
		D3DXMatrixScaling(&g_matSetScale,scale.x,scale.y,scale.z);
		D3DXMatrixTranslation(&g_matSetTrans,trans.x,trans.y,trans.z);
		*world = *world * g_matSetScale * g_matSetTrans;
		return *world;
	}
	inline D3DXMATRIX DrawPosition(D3DXVECTOR3 scale,/**/D3DXVECTOR3 trans)
	{
		D3DXMatrixIdentity(&g_matSetWorld);
		D3DXMatrixScaling(&g_matSetScale,scale.x,scale.y,scale.z);
		D3DXMatrixTranslation(&g_matSetTrans,trans.x,trans.y,trans.z);
		return g_matSetWorld * g_matSetScale * g_matSetTrans;
	};
	inline D3DXMATRIX DrawPosition(D3DXMATRIX* world,/**/D3DXVECTOR3 scale,FLOAT rotate,/**/D3DXVECTOR3 trans){
		D3DXMatrixIdentity(world);
		D3DXMatrixScaling(&g_matSetScale,scale.x,scale.y,scale.z);
		D3DXMatrixRotationY(&g_matSetRotate,rotate);
		D3DXMatrixTranslation(&g_matSetTrans,trans.x,trans.y,trans.z);
		*world = *world * g_matSetScale * g_matSetRotate * g_matSetTrans;
		return *world;
	};
	inline VOID MonsterPosition(FLOAT speed){
		if(	!g_pMonster->IsbGround()){
			g_pMonster->SetPosition(g_pMonster->GetPosition()+g_pMonster->GetVelocity()*speed);
				//D3DXVECTOR3 matInit(0.0f,0.0f,1.0f);
				//D3DXVECTOR3 matAngle;
				//float m = D3DXVec3Dot(&matInit,&vVelocity);
				//D3DXVec3Cross(&matAngle,&matInit,&vVelocity);
				//D3DXMatrixRotationAxis(&matWorld,&matAngle,m);

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

	inline VOID DrawWall(){
		if(g_pMonAi->OnWall() != 0)
		{
			if( !g_pWall->IsGround() )
			{
				g_pWall->SetPosition(g_pWall->GetPosition()+g_pWall->GetVelocity()*BALLSPEED);
				if(g_pWall->GetVelocity().y>0){
					g_pWall->SetVelocityY(g_pWall->GetVelocity().y-(GRAVITY+REVERSE_GRAVITY)*BALLSPEED*15.0f);
				}else{
					g_pWall->SetVelocityY(g_pWall->GetVelocity().y-(GRAVITY*BALLSPEED)*5.0f);
					switch(g_pMonAi->OnWallPosition()){
					case 1:
					case 2:
						if(abs(g_pMonAi->OnWall() - g_pCha->GetPosition().x)<BALL_SIZE+3.0f && abs(g_pWall->GetPositionY() - g_pCha->GetPosition().y)<BALL_SIZE+5.0f){
							g_pCha->SetLife(-g_pWall->GetVelocityY());
						}
						break;
					case 3:
					case 4:
						if(abs(g_pMonAi->OnWall() - g_pCha->GetPosition().z)<BALL_SIZE+3.0f && abs(g_pWall->GetPositionY() - g_pCha->GetPosition().y)<BALL_SIZE+5.0f){
							g_pCha->SetLife(-g_pWall->GetVelocityY());
						}
						break;
					}
				}

				if( g_pWall->GetPosition().y < -GROUND)
				{
					if(g_pWall->GetBcount()>7){
						g_pWall->IsGround(true);
					}else{
						g_pWall->SetPositionY(-GROUND );
						g_pWall->SetVelocityY(-g_pWall->GetVelocity().y* ( 1 - ABSORBANCE*20 ));
						g_pWall->SetBcount();
					}

				}
			}
			INT l_nWall = g_pMonAi->OnWall();
			if(!g_bWall){
				switch(g_pMonAi->OnWallPosition()){
				case 1:
					if( g_pCha->GetPosition().x < l_nWall + ( MYSIZE * 0.5f ) )
					{
						g_pCha->SetPositionX(l_nWall + ( MYSIZE * 0.5f ));
						g_pCha->SetVelocityX(-(g_pCha->GetVelocity().x) * ( 1 - ABSORBANCE ));
					}
					g_pWallModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(0.001f,3.2f,3.2f),D3DXVECTOR3(g_pMonAi->OnWall(),g_pWall->GetPositionY()+MAXBOUNDY/2,MAXBOUNDZ/2)));			
					break;
				case 2:
					if( g_pCha->GetPosition().x > l_nWall - ( MYSIZE * 0.5f ) )
					{
						g_pCha->SetPositionX(l_nWall - ( MYSIZE * 0.5f ));
						g_pCha->SetVelocityX(-(g_pCha->GetVelocity().x) * ( 1 - ABSORBANCE ));
					}
					g_pWallModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(0.001f,3.2f,3.2f),D3DXVECTOR3(g_pMonAi->OnWall(),g_pWall->GetPositionY()+MAXBOUNDY/2,MAXBOUNDZ/2)));
					break;
				case 3:
					if( g_pCha->GetPosition().z < l_nWall + ( MYSIZE * 0.5f ) )
					{
						g_pCha->SetPositionZ(l_nWall + ( MYSIZE * 0.5f ));
						g_pCha->SetVelocityZ(-(g_pCha->GetVelocity().z) * ( 1 - ABSORBANCE ));
					}
					g_pWallModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(3.2f,3.2f,0.001f),D3DXVECTOR3(MAXBOUNDX/2,g_pWall->GetPositionY()+MAXBOUNDY/2,g_pMonAi->OnWall())));
					break;
				case 4:
					if( g_pCha->GetPosition().z > l_nWall - ( MYSIZE * 0.5f ) )
					{
						g_pCha->SetPositionZ(l_nWall - ( MYSIZE * 0.5f ));
						g_pCha->SetVelocityZ(-(g_pCha->GetVelocity().z) * ( 1 - ABSORBANCE ));
					}
					g_pWallModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(3.2f,3.2f,0.001f),D3DXVECTOR3(MAXBOUNDX/2,g_pWall->GetPositionY()+MAXBOUNDY/2,g_pMonAi->OnWall())));
					break;
				default:
					break;
				}
				g_bWall = TRUE;
			}else{
				g_bWall = FALSE;
			}
		}
	};
	inline VOID CrashMissile(){
		if(g_pMonAi->GetMsionall()){
			for(INT i=0;i<MISSILE_COUNT;i++){
				g_pMissileModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(MISSILE_SIZE,MISSILE_SIZE,MISSILE_SIZE),g_pMissile[i]->GetPosition()));
				if(g_pMissile[i]->GetType()!= 4){
					D3DXVECTOR3 vOneToTwo = g_pCha->GetPosition() - g_pMissile[i]->GetPosition();
					float DistSq = D3DXVec3LengthSq( &vOneToTwo );
					if( DistSq < (MON_REAL_SIZE+MYSIZE) * (MON_REAL_SIZE+MYSIZE) ){
						g_pCha->SetLife(g_pMissile[i]->GetDemage());
					}
				}
			}
		}	
	};

	inline VOID CrashMon(FLOAT time){
		if((time - fCrashTime > 2.0f)&&(bCrash == true)){
			g_pMonster->SetisGoal(false);
			g_pMonster->SetOriginType(0);
			bCrash = false;
		}
		if(g_pMonster->IsAlive()==true)//is alive?
		{
			D3DXVECTOR3 pMonRealPosition = g_pMonster->GetPosition();
			pMonRealPosition.y += MON_REAL_SIZE/2;
			D3DXVECTOR3 vOneToTwo = g_pCha->GetPosition() - pMonRealPosition;
			float DistSq = D3DXVec3LengthSq( &vOneToTwo );

			if( DistSq < (MON_REAL_SIZE+MYSIZE) * (MON_REAL_SIZE+MYSIZE) )
			{
				D3DXVec3Normalize( &vOneToTwo, &vOneToTwo );
				float fImpact = D3DXVec3Dot( &vOneToTwo, &g_pMonster->GetVelocity() ) - D3DXVec3Dot( &vOneToTwo, &g_pCha->GetVelocity());	

				if( fImpact > 0.0f )
				{
					bCrash = true;

					fCrashTime = time;

					D3DXVECTOR3 vVelocityOneN = ( 1 - BOUNCE_LOST ) * D3DXVec3Dot( &vOneToTwo, &g_pMonster->GetVelocity() ) * vOneToTwo;
					D3DXVECTOR3 vVelocityOneT = ( 1 - BOUNCE_LOST ) * g_pMonster->GetVelocity() - vVelocityOneN;

					D3DXVECTOR3 vVelocityTwoN = ( 1 - BOUNCE_LOST ) * D3DXVec3Dot( &vOneToTwo, &g_pCha->GetVelocity()) * vOneToTwo;
					D3DXVECTOR3 vVelocityTwoT = ( 1 - BOUNCE_LOST ) * g_pCha->GetVelocity() - vVelocityTwoN;

					g_pMonster->SetVelocity(vVelocityOneT - vVelocityOneN * ( 1 - BOUNCE_TRANSFER ) + vVelocityTwoN * BOUNCE_TRANSFER);
					g_pCha->SetVelocity(vVelocityTwoT - vVelocityTwoN * ( 1 - BOUNCE_TRANSFER ) + vVelocityOneN * BOUNCE_TRANSFER);

					float fDistanceToMove = ( MON_REAL_SIZE - sqrtf( DistSq ) ) * 0.5f;
					g_pMonster->SetPosition(g_pMonster->GetPosition()-vOneToTwo * fDistanceToMove);
					g_pCha->SetPosition(g_pCha->GetPosition()+vOneToTwo * fDistanceToMove);	

					g_pMonster->SetLife(-abs((int)D3DXVec3Length(&g_pCha->GetVelocity())));
				}
			}
		}
	}

};
#endif