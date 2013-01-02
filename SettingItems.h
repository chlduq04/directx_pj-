#ifndef _SETTINGITEMS_H_
#define _SETTINGITEMS_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "Items.h"
#include "ItemsList.h"
#include "Xfile.h"
#include "Ball.h"
class SettingItems{
private:
	float g_fStartTime;
	ItemsList* g_pItemList;
	INT g_nItemSerialNum;

	Xfile* g_pHpItems;
	Xfile* g_pMpItems;
	Xfile* g_pDefItems;
	D3DXMATRIX g_matSetWorld;
	D3DXMATRIX g_matSetScale;
	D3DXMATRIX g_matSetRotate;
	D3DXMATRIX g_matSetTrans;

	LPDIRECT3DDEVICE9 g_pDevice;
public:
	SettingItems(FLOAT time, LPDIRECT3DDEVICE9 device);
	~SettingItems();
	inline D3DXMATRIX DrawPosition(/**/D3DXVECTOR3 scale,/**/D3DXVECTOR3 trans,float rotate){
		D3DXMatrixIdentity(&g_matSetWorld);
		D3DXMatrixScaling(&g_matSetScale,scale.x,scale.y,scale.z);
		D3DXMatrixRotationX(&g_matSetRotate,rotate);
		D3DXMatrixTranslation(&g_matSetTrans,trans.x,trans.y,trans.z);
		return g_matSetWorld * g_matSetScale * g_matSetRotate * g_matSetTrans;
	};
	inline VOID NewItems(FLOAT time){
		if( time-g_fStartTime >=  1.0f){
			if((rand()%10==5)&&(g_pItemList->GetCount()<10)){
				g_pItemList->SetNode(new Items(rand()%3,1,D3DXVECTOR3(rand()%100,rand()%100,rand()%100),g_nItemSerialNum++,time));
			}
			g_fStartTime = time; 
		}
	};
	inline VOID GetItem(Ball* character){
		Items* nowNode = g_pItemList->GetStart()->GetNext(); 
		if(nowNode!=g_pItemList->GetEnd()){
			while(nowNode->GetNext()!=g_pItemList->GetEnd()){
				D3DXVECTOR3 vOneToTwo = character->GetPosition() - nowNode->GetPosition();
				float DistSq = D3DXVec3LengthSq( &vOneToTwo );
				if( DistSq < (MYSIZE+ITEM_REAL_SIZE) * (MYSIZE+ITEM_REAL_SIZE) )
				{
					Items* deleteNode = nowNode;
					character->SetLife(nowNode->GetHp());
					character->SetMana(nowNode->GetMp());
					character->SetDefence(nowNode->GetDef());
					nowNode = nowNode->GetNext();
					g_pItemList->DelNode(deleteNode);
				}else{
					nowNode = nowNode->GetNext();
				}
			}
		}
	};
	inline VOID DrawItem(FLOAT time){
		Items* nowNode = g_pItemList->GetStart()->GetNext();
		if(nowNode!=g_pItemList->GetEnd()){
			while(nowNode->GetNext()!=g_pItemList->GetEnd()){
				if(time-(nowNode->GetTime())>20){
					Items* deleteNode = nowNode;
					nowNode=nowNode->GetNext();
					g_pItemList->DelNode(deleteNode);
				}else{
					switch(nowNode->GetType()){
					default:
					case 0:
						g_pHpItems->DrawMyballShader(DrawPosition(D3DXVECTOR3(0.1f,0.1f,0.1f),nowNode->GetPosition(),nowNode->GetTime()+time));
						break;
					case 1:
						g_pMpItems->DrawMyballShader(DrawPosition(D3DXVECTOR3(0.1f,0.1f,0.1f),nowNode->GetPosition(),nowNode->GetTime()+time));
						break;
					case 2:
						g_pDefItems->DrawMyballShader(DrawPosition(D3DXVECTOR3(0.1f,0.1f,0.1f),nowNode->GetPosition(),nowNode->GetTime()+time));
						break;
					}
					nowNode=nowNode->GetNext();
				}
			}
		}
	};

	inline VOID Draw(FLOAT time , Ball* character){
		NewItems(time);
		DrawItem(time);
		GetItem(character);
	}
	inline ItemsList* getItemsList(){return g_pItemList;};

	VOID SetViewMatrix(D3DXMATRIX view);
	VOID SetProjectionMatrix(D3DXMATRIX proj,D3DXVECTOR4 light);
	HRESULT SetXfile();
};
#endif