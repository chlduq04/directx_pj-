#ifndef _SETTINGUI_H_
#define _SETTINGUI_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Ui.h"
#include "Struct.h"
#include "Settings.h"
class SettingUI{
private:
	INT	SetLaser;
	INT SetDamage;
	BOOL NowLaser;
	MYVERTEX vtx[4];
	MYVERTEX Cha[4];
	MYVERTEX Mon[4];
	MYVERTEX Laser[4];
	LPDIRECT3DTEXTURE9		g_pImage[7];// 빌보드로 사용할 텍스처
	D3DXMATRIX				matBillBoard;
	Ui* g_pUI;
public:
	SettingUI(LPDIRECT3DDEVICE9 dev);
	~SettingUI();
	VOID DrawUI(int velocity,float life,float mana,float def,float monlife);
	inline BOOL GetLaserUI(){return NowLaser;};
	inline VOID SetLaserUI(){NowLaser = true;};
	inline VOID SettingVtx(MYVERTEX* vt,int setpx,int setpy,int setpz,int settu,int settv){
		vt->px = setpx; vt->py = setpy; vt->pz = setpz; vt->tu = settu; vt->tv = settv;
	}
	VOID DamageUI();
};
#endif