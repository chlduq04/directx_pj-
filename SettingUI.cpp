#include "SettingUI.h"
SettingUI::SettingUI(LPDIRECT3DDEVICE9 dev){
	g_pUI = new Ui(dev);
	g_pUI->InitBillboard("normal_speed.png",&g_pImage[0]);
	g_pUI->InitBillboard("red_speed.png",&g_pImage[1]);
	g_pUI->InitBillboard("yellow_speed.png",&g_pImage[2]);
	g_pUI->InitBillboard("hp.png",&g_pImage[3]);
	g_pUI->InitBillboard("mp.png",&g_pImage[4]);
	g_pUI->InitBillboard("def.png",&g_pImage[5]);
	g_pUI->InitBillboard("black_rec.png",&g_pImage[6]);

	SettingVtx(&vtx[0],WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/120, 0, 0, 1);
	SettingVtx(&vtx[1],WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2, 0, 0, 0);
	SettingVtx(&vtx[2],WINDOW_WIDTH/2, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/120, 0, 1, 1);
	SettingVtx(&vtx[3],WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, 0, 1, 0);

	SettingVtx(&Cha[0],WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/50, 0, 0, 1);
	SettingVtx(&Cha[1],WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2, 0, 0, 0);
	SettingVtx(&Cha[2],WINDOW_WIDTH/2, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/50, 0, 1, 1);
	SettingVtx(&Cha[3],WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, 0, 1, 0);

	SettingVtx(&Mon[0],WINDOW_WIDTH/2-WINDOW_WIDTH/5, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/5, 0, 0, 1);
	SettingVtx(&Mon[1],WINDOW_WIDTH/2-WINDOW_WIDTH/5, -WINDOW_HEIGHT/2, 0, 0, 0);
	SettingVtx(&Mon[2],WINDOW_WIDTH/2, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/5, 0, 1, 1);
	SettingVtx(&Mon[3],WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, 0, 1, 0);

}
SettingUI::~SettingUI(){
	if(g_pImage){
		for(INT i=0;i<7;i++){
			if(g_pImage[i]){
				g_pImage[i]->Release(); 
				g_pImage[i]=NULL;
				delete g_pImage[i];
			}
		}
	}
	delete g_pUI;
}
VOID SettingUI::DrawUI(int velocity,float life,float mana,float def,float monlife){
	g_pUI->SetUI();
	switch(velocity){
	default:
	case 50 : case 49 : g_pUI->DrawBillboard(g_pImage[1],&matBillBoard,-10.5f,120.0f,0.0f,vtx);
	case 48 : case 47 : g_pUI->DrawBillboard(g_pImage[1],&matBillBoard,-10.5f,115.0f,0.0f,vtx);
	case 46 : case 45 : g_pUI->DrawBillboard(g_pImage[1],&matBillBoard,-10.5f,110.0f,0.0f,vtx);
	case 44 : case 43 : g_pUI->DrawBillboard(g_pImage[1],&matBillBoard,-10.5f,105.0f,0.0f,vtx);
	case 42 : case 41 : g_pUI->DrawBillboard(g_pImage[2],&matBillBoard,-10.5f,100.0f,0.0f,vtx);
	case 40 : case 39 : g_pUI->DrawBillboard(g_pImage[2],&matBillBoard,-10.5f,95.0f,0.0f,vtx);
	case 38 : case 37 : g_pUI->DrawBillboard(g_pImage[2],&matBillBoard,-10.5f,90.0f,0.0f,vtx);
	case 36 : case 35 : g_pUI->DrawBillboard(g_pImage[2],&matBillBoard,-10.5f,85.0f,0.0f,vtx);
	case 34 : case 33 : g_pUI->DrawBillboard(g_pImage[2],&matBillBoard,-10.5f,80.0f,0.0f,vtx);
	case 32 : case 31 : g_pUI->DrawBillboard(g_pImage[2],&matBillBoard,-10.5f,75.0f,0.0f,vtx);
	case 30 : case 29 : g_pUI->DrawBillboard(g_pImage[2],&matBillBoard,-10.5f,70.0f,0.0f,vtx);
	case 28 : case 27 : g_pUI->DrawBillboard(g_pImage[2],&matBillBoard,-10.5f,65.0f,0.0f,vtx);
	case 26 : case 25 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,60.0f,0.0f,vtx);
	case 24 : case 23 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,55.0f,0.0f,vtx);
	case 22 : case 21 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,50.0f,0.0f,vtx);
	case 20 : case 19 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,45.0f,0.0f,vtx);
	case 18 : case 17 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,40.0f,0.0f,vtx);
	case 16 : case 15 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,35.0f,0.0f,vtx);
	case 14 : case 13 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,30.0f,0.0f,vtx);
	case 12 : case 11 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,25.0f,0.0f,vtx);
	case 10 : case 9 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,20.0f,0.0f,vtx);
	case 8 : case 7 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,15.0f,0.0f,vtx);
	case 6 : case 5 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,10.0f,0.0f,vtx);
	case 4 : case 3 : g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,5.0f,0.0f,vtx);
	case 2 : case 1: case 0: g_pUI->DrawBillboard(g_pImage[0],&matBillBoard,-10.5f,0.0f,0.0f,vtx);
		break;
	}
	for(INT i=0;i<life/10;i++){
		g_pUI->DrawBillboard(g_pImage[3],&matBillBoard,-WINDOW_WIDTH+WINDOW_WIDTH/20,12.0f*i,0.0f,Cha);
	}
	for(INT i=0;i<mana/10;i++){
		g_pUI->DrawBillboard(g_pImage[4],&matBillBoard,-WINDOW_WIDTH+WINDOW_WIDTH/20*2,12.0f*i,0.0f,Cha);
	}
	for(INT i=0;i<def/10;i++){
		g_pUI->DrawBillboard(g_pImage[5],&matBillBoard,-WINDOW_WIDTH+WINDOW_WIDTH/20*3,12.0f*i,0.0f,Cha);
	}
	for(INT i=0;i<monlife/50;i++){
		g_pUI->DrawBillboard(g_pImage[3],&matBillBoard,-WINDOW_WIDTH+WINDOW_WIDTH/20*i,WINDOW_HEIGHT-monlife/50,0.0f,Mon);
	}
}
