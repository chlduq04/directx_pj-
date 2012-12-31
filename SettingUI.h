#ifndef _SETTINGUI_H_
#define _SETTINGUI_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Ui.h"
#include "Struct.h"
#include "Settings.h"
class SettingUI{
private:
	MYVERTEX vtx[4];
	MYVERTEX Cha[4];
	MYVERTEX Mon[4];
	LPDIRECT3DTEXTURE9		g_pImage[7];// ������� ����� �ؽ�ó
	D3DXMATRIX				matBillBoard;
	Ui* g_pUI;
public:
	SettingUI(LPDIRECT3DDEVICE9 dev);
	~SettingUI();
	VOID DrawUI(int velocity,float life,float mana,float def,float monlife);
	inline VOID SettingVtx(MYVERTEX* vt,int setpx,int setpy,int setpz,int settu,int settv){
		vt->px = setpx; vt->py = setpy; vt->pz = setpz; vt->tu = settu; vt->tv = settv;
	}
};
#endif