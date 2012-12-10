#include "Ui.h"

Ui::Ui(float width,float height){
	win_width = width;
	win_height = height;
}


HRESULT Ui::initBillboard(LPDIRECT3DDEVICE9 device, const char* image_name,LPDIRECT3DTEXTURE9* texture){
	D3DXCreateTextureFromFile( device, image_name, texture );
	return S_OK;
}
VOID Ui::setUI(LPDIRECT3DDEVICE9 device)
{
	D3DXMATRIX mat_Ortho;
	D3DXMatrixIdentity(&mat_Ortho);
	device->SetTransform(D3DTS_VIEW, &mat_Ortho);	
	D3DXMatrixOrthoLH (&mat_Ortho,win_width,win_height,0,10);
	device->SetTransform(D3DTS_PROJECTION, &mat_Ortho);

	device->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	device->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
	device->SetRenderState( D3DRS_ALPHAREF,        0x08 );
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
	device->SetTexture( 1, NULL );
	device->SetFVF( MYVERTEX::FVF );
}
VOID Ui::setCenUI(LPDIRECT3DDEVICE9 device)
{
	D3DXMATRIX mat_Ortho;
	D3DXMatrixIdentity(&mat_Ortho);
	device->SetTransform(D3DTS_VIEW, &mat_Ortho);	
	D3DXMatrixOrthoOffCenterLH(&mat_Ortho,-1,1,1,-1,0,1);
	device->SetTransform(D3DTS_PROJECTION, &mat_Ortho);

	device->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	device->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	device->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
	device->SetRenderState( D3DRS_ALPHAREF,        0x08 );
	device->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
	device->SetTexture( 1, NULL );
	device->SetFVF( MYVERTEX::FVF );
}
VOID Ui::drawBillboard(LPDIRECT3DDEVICE9 device,LPDIRECT3DTEXTURE9 texture,D3DXMATRIX* matworld,float tranx, float trany, float tranz, MYVERTEX* vtx){
	
	D3DXMatrixIdentity( matworld );
	D3DXMATRIXA16	matbill_tran;
	// 0번 텍스처에 빌보드 텍스처를 올린다

	device->SetTexture( 0, texture );
	D3DXMatrixTranslation(&matbill_tran,tranx,trany,tranz);
	//D3DXMatrixTranslation(&matbill_tran,-10.5f,0.5f,0.0f);
	*matworld *= matbill_tran;
	device->SetTransform( D3DTS_WORLD, matworld );
	device->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(MYVERTEX) );
	//		g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
}