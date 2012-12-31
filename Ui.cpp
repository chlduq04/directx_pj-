#include "Ui.h"

Ui::Ui(LPDIRECT3DDEVICE9 device){
	d3dDevice = device;
	fWinWidth = WINDOW_WIDTH;
	fWinHeight = WINDOW_HEIGHT;
}
Ui::~Ui(){
	d3dDevice = NULL;
}
HRESULT Ui::InitBillboard(const char* image_name,LPDIRECT3DTEXTURE9* texture){
	D3DXCreateTextureFromFile( d3dDevice, image_name, texture );
	return S_OK;
}
VOID Ui::SetUI()
{
	D3DXMATRIX mat_Ortho;
	D3DXMatrixIdentity(&mat_Ortho);
	d3dDevice->SetTransform(D3DTS_VIEW, &mat_Ortho);	
	D3DXMatrixOrthoLH (&mat_Ortho,fWinWidth,fWinHeight,0,10);
	d3dDevice->SetTransform(D3DTS_PROJECTION, &mat_Ortho);

	d3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
	d3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	d3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	d3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
	d3dDevice->SetRenderState( D3DRS_ALPHAREF,        0x08 );
	d3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
	d3dDevice->SetTexture( 1, NULL );
	d3dDevice->SetFVF( MYVERTEX::FVF );
}
VOID Ui::SetCenUI()
{
	D3DXMATRIX mat_Ortho;
	D3DXMatrixIdentity(&mat_Ortho);
	d3dDevice->SetTransform(D3DTS_VIEW, &mat_Ortho);	
	D3DXMatrixOrthoOffCenterLH(&mat_Ortho,-1,1,1,-1,0,1);
	d3dDevice->SetTransform(D3DTS_PROJECTION, &mat_Ortho);

	d3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
	d3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	d3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	d3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
	d3dDevice->SetRenderState( D3DRS_ALPHAREF,        0x08 );
	d3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
	d3dDevice->SetTexture( 1, NULL );
	d3dDevice->SetFVF( MYVERTEX::FVF );
}
VOID Ui::DrawBillboard(LPDIRECT3DTEXTURE9 texture,D3DXMATRIX* matworld,float tranx, float trany, float tranz, MYVERTEX* vtx){
	
	D3DXMatrixIdentity( matworld );
	D3DXMATRIXA16	matbill_tran;
	// 0번 텍스처에 빌보드 텍스처를 올린다

	d3dDevice->SetTexture( 0, texture );
	D3DXMatrixTranslation(&matbill_tran,tranx,trany,tranz);
	//D3DXMatrixTranslation(&matbill_tran,-10.5f,0.5f,0.0f);
	*matworld *= matbill_tran;
	d3dDevice->SetTransform( D3DTS_WORLD, matworld );
	d3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(MYVERTEX) );
	//		g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
}