#include "SettingItems.h"
SettingItems::SettingItems(FLOAT time, LPDIRECT3DDEVICE9 device){
	g_fStartTime = time;
	g_nItemSerialNum = 0;
	g_pItemList = new ItemsList();
	g_pHpItems = new Xfile();
	g_pMpItems = new Xfile();
	g_pDefItems = new Xfile();
	g_pDevice = device;
}
SettingItems::~SettingItems(){
	delete g_pItemList;
	delete g_pHpItems;
	delete g_pMpItems;
	delete g_pDefItems;
	g_pDevice = NULL;
}
HRESULT SettingItems::SetXfile(){
	if(FAILED(g_pHpItems->InitballMesh(g_pDevice,"FireBase.tga","CoinDOT3.tga","HP.fx","HP.x")))
		return E_FAIL;
	if(FAILED(g_pMpItems->InitballMesh(g_pDevice,"CoinDOT3.tga","CoinDOT3.tga","MP.fx","MP.x")))
		return E_FAIL;
	if(FAILED(g_pDefItems->InitballMesh(g_pDevice,"coin.dds","CoinDOT3.tga","DEF.fx","DEF.x")))
		return E_FAIL;
	return S_OK;
}
VOID SettingItems::SetViewMatrix(D3DXMATRIX view){
	g_pHpItems->SetView(view);
	g_pMpItems->SetView(view);
	g_pDefItems->SetView(view);
};
VOID SettingItems::SetProjectionMatrix(D3DXMATRIX proj,D3DXVECTOR4 light){
	g_pHpItems->SetViewprojtexture(proj,light);
	g_pMpItems->SetViewprojtexture(proj,light);
	g_pDefItems->SetViewprojtexture(proj,light);
};