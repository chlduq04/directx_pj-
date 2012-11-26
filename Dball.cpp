#include <Windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
//-----------------------------------------------------------------------------
// Header Files
//-----------------------------------------------------------------------------
#include "ZCamera.h"
#include "Variable.h"
#include "Settings.h"
#include "Xfile.h"
#include "Ball.h"
#include "Monster.h"
#include "Moving.h"
#include "Items.h"
#include "ItemsList.h"
#include "Ui.h"
//-----------------------------------------------------------------------------
// Drow Billboard
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9		speed_bar[3] = { NULL, NULL, NULL };// ������� ����� �ؽ�ó
D3DXMATRIXA16			matBillboard;
//-----------------------------------------------------------------------------
// Items Setting
//-----------------------------------------------------------------------------
float					m_fStartTime; 

ItemsList*				itemList;		
Items*					item1;
Items*					item2;
Ui*						m_Ui;
D3DXMATRIXA16			iWorld;
static int				itemSerialNum = 0;
//-----------------------------------------------------------------------------
// Camera Setting
//-----------------------------------------------------------------------------
D3DXMATRIXA16			g_matAni;
int						cameraCase = 1;
float					Mouse_X;
float					Mouse_Y;
//-----------------------------------------------------------------------------
// Character Matrix
//-----------------------------------------------------------------------------
D3DXMATRIX				mView;
D3DXMATRIXA16			mWorld;
D3DXMATRIXA16			mBox;
D3DXVECTOR4             gLightColor(1.0f, 1.0f, 1.0f, 1.0f);//���� ��
D3DXVECTOR3				zero(0.0f,0.0f,0.0f);

Ball*					myCharacter;
Monster*				mMonster1;

Moving*					mMoving;

D3DXMATRIXA16			myWorld;
D3DXMATRIXA16			myScale;
D3DXMATRIXA16			myTrans;
D3DXMATRIXA16			myRotate;
D3DXVECTOR3				mEye;

D3DXVECTOR4 Pos( START_POSITIONX, START_POSITIONY, START_POSITIONZ, 1.0f );
D3DXVECTOR4 Vel( START_VELOCITYX, START_VELOCITYY, START_VELOCITYZ, 0.0f );

//-----------------------------------------------------------------------------
// World Matrix
//-----------------------------------------------------------------------------
D3DXMATRIXA16			matWorld;
D3DXMATRIXA16			matView;
D3DXMATRIXA16			matProj;
//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9				g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9		g_pd3dDevice = NULL; // Our rendering device
LPD3DXMESH				g_pMesh = NULL; // Our mesh object in sysmem
D3DMATERIAL9*			g_pMeshMaterials = NULL; // Materials for our mesh
LPDIRECT3DTEXTURE9*		g_pMeshTextures = NULL; // Textures for our mesh
DWORD					g_dwNumMaterials = 0L;   // Number of mesh materials

//-----------------------------------------------------------------------------
// Xfile Draw
//-----------------------------------------------------------------------------
Xfile* drawXfile;
Xfile* mapBox;
//-----------------------------------------------------------------------------
// InitD3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
	// Create the D3D object.
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	return S_OK;
}


HRESULT initCharacter(){
	if(FAILED(drawXfile->InitballMesh(g_pd3dDevice,"FireBase.tga","Flame.tga","FireBall.fx","FireBall.x"))){
		return E_FAIL;
	}
	if(FAILED(mapBox->InitballMesh(g_pd3dDevice,"FieldstoneNoisy.tga","FieldstoneBumpDOT3.tga","Monster.fx","Monster.x"))){
		return E_FAIL;
	}
	return S_OK;
}
//-----------------------------------------------------------------------------
// �� ��� ����, ī�޶� ����
//-----------------------------------------------------------------------------

VOID SetupCamera()
{
	/// ���� ��� ����
	D3DXMatrixIdentity( &matWorld );
	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	/// �� ����� ����
	D3DXVECTOR3 vEyePt( 0.0f, 10.0f, 0.0f );
	D3DXVECTOR3 vLookatPt( 10.0f, 0.0f, 10.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
	/// �������� ��� ����
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 1000.0f );
	g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	/// ī�޶� �ʱ�ȭ
	g_pCamera->SetView( &vEyePt, &vLookatPt, &vUpVec );
}

/**-----------------------------------------------------------------------------
* ���콺 ó��
*------------------------------------------------------------------------------
*/
VOID InitGeometry()
{
	SetupCamera();
	POINT	pt;
	GetCursorPos( &pt );
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;
}

/**-----------------------------------------------------------------------------
* �Է� ó��
*------------------------------------------------------------------------------
*/
void ProcessInputs( void )
{
	POINT	pt;
	GetCursorPos( &pt );
	int dx = pt.x - g_dwMouseX;	// ���콺�� ��ȭ��
	int dy = pt.y - g_dwMouseY;	// ���콺�� ��ȭ��

	Mouse_X += -dx*0.001;
	Mouse_Y += dy*0.05;


	if(cameraCase == 1){
	if( GetAsyncKeyState( 'W' )||GetAsyncKeyState( 'w' ) ) g_pCamera->MoveLocalZ( 0.5f );	// ī�޶� ����!
	if( GetAsyncKeyState( 'S' )||GetAsyncKeyState( 's' ) ) g_pCamera->MoveLocalZ( -0.5f );	// ī�޶� ����!
	if( GetAsyncKeyState( 'A' )||GetAsyncKeyState( 'a' ) ) g_pCamera->MoveLocalX( -0.5f );	// ī�޶� ����!
	if( GetAsyncKeyState( 'D' )||GetAsyncKeyState( 'd' ) ) g_pCamera->MoveLocalX( 0.5f );	// ī�޶� ����!
	if( GetAsyncKeyState( VK_ESCAPE ) ) PostMessage( g_hwnd, WM_DESTROY, 0, 0L );
	//if( GetAsyncKeyState( VK_LBUTTON ) ) g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	//if( GetAsyncKeyState( VK_RBUTTON ) ) g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	}
	else if(cameraCase == 2){
		g_pCamera->RotateLocalX( dy * MOUSE_SENSITIVE );	// ���콺�� Y�� ȸ������ 3D world��  X�� ȸ����
		g_pCamera->RotateLocalY( dx * MOUSE_SENSITIVE );	// ���콺�� X�� ȸ������ 3D world��  Y�� ȸ����
		D3DXMATRIXA16*	pmatView = g_pCamera->GetViewMatrix();		// ī�޶� ����� ��´�.
		g_pd3dDevice->SetTransform( D3DTS_VIEW, pmatView );			// ī�޶� ��� ����
	}

	// ���콺�� �������� �߾����� �ʱ�ȭ
	 SetCursor( NULL );	// ���콺�� ��Ÿ���� �ʰ� �ʴ�.
	RECT	rc;
	GetClientRect( g_hwnd, &rc );
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen( g_hwnd, &pt );
	SetCursorPos( pt.x, pt.y );
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;


}
VOID SetupLight()
{
	D3DMATERIAL9 mtrl;
	ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	g_pd3dDevice->SetMaterial( &mtrl );

	/// ���� ����
	D3DXVECTOR3 vecDir;									/// ���⼺ ����(directional light)�� ���� ���� ����
	D3DLIGHT9 light;									/// ���� ����ü
	ZeroMemory( &light, sizeof(D3DLIGHT9) );			/// ����ü�� 0���� �����.

	light.Type       = D3DLIGHT_POINT;			/// ������ ����(�� ����,���⼺ ����,����Ʈ����Ʈ)
	light.Diffuse.r  = 1.0f;							/// ������ ����� ���
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 0.2f;
	light.Position.x = 30.0f;
	light.Position.y = 30.0f;
	light.Position.z = 30.0f;

	vecDir = D3DXVECTOR3( 1, 1, 1 );					/// ���� ����

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );	/// ������ ������ �������ͷ� �����.
	light.Range       = 1000.0f;									/// ������ �ٴٸ��� �ִ� �ִ�Ÿ�

	g_pd3dDevice->SetLight( 0, &light );							/// ����̽��� 0�� ���� ��ġ
	g_pd3dDevice->LightEnable( 0, TRUE );							/// 0�� ������ �Ҵ�
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );			/// ���������� �Ҵ�
	g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00404040 );		/// ȯ�汤��(ambient light)�� �� ����
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if( g_pMeshMaterials != NULL )
		delete[] g_pMeshMaterials;

	if(speed_bar){
		for(int i=0;i<3;i++){
			if(speed_bar[i]){
				speed_bar[i]->Release(); 
				speed_bar[i] = NULL;
				delete speed_bar[i];
			}
		}
	}

	if( g_pMeshTextures )
	{
		for( DWORD i = 0; i < g_dwNumMaterials; i++ )
		{
			if( g_pMeshTextures[i] )
				g_pMeshTextures[i]->Release();
		}
		delete[] g_pMeshTextures;
	}
	if( g_pMesh != NULL )
		g_pMesh->Release();

	if( g_pd3dDevice != NULL )
		g_pd3dDevice->Release();

	if( g_pD3D != NULL )
		g_pD3D->Release();
}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID setItemList(){
	float NowTime = (float)timeGetTime() * 0.001f;
	if( NowTime-m_fStartTime >=  1.0f){
		if((rand()%10==5)&&(itemList->getCount()<10)){
			D3DXVECTOR3 iPosition(rand()%100,rand()%100,rand()%100);
			char* item;
			switch(rand()%4){
			case 0:
				item = "hp";
				break;
			case 1:
				item = "mp";
				break;
			case 2:
				item = "def";
				break;
			case 3:
				item = "hp";
				break;
			}
			itemList->setNode(new Items(item,1,iPosition,itemSerialNum++,NowTime));
		}
		m_fStartTime = NowTime; 
	}
}

VOID itemListDraw(){
	float NowTime = (float)timeGetTime() * 0.001f;
	Items* nowNode = itemList->getStart(); 
	while(nowNode->getNext()!=itemList->getEnd()){
		nowNode=nowNode->getNext();
		if(NowTime-(nowNode->getTime())>20){
			itemList->delNode(nowNode->getNumber());
		}else{
			D3DXMatrixIdentity(&iWorld);
			D3DXMatrixScaling(&myScale,0.1f,0.1f,0.1f);
			D3DXMatrixRotationY(&myRotate, timeGetTime() / 1000.0f );
			D3DXMatrixTranslation(&myTrans,nowNode->getPosition().x,nowNode->getPosition().y,nowNode->getPosition().z);
			iWorld *= myScale;
			iWorld *= myRotate;
			iWorld *= myTrans;
			mapBox->DrawMyballShader(iWorld);
		}
	}
}

VOID DrawBillboard()
{
		g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
		g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
		g_pd3dDevice->SetRenderState( D3DRS_ALPHAREF,        0x08 );
		g_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );

		struct MYVERTEX
		{
			enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
			float px, py, pz;
			float tu, tv;
		};

		// ������ ����
		MYVERTEX vtx[4] = 
		{ 
			{ WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/60, 0, 0, 1 },
			{ WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2, 0, 0, 0 },
			{ WINDOW_WIDTH/2, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/60, 0, 1, 1 },
			{ WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, 0, 1, 0 }
		};


		D3DXMatrixIdentity( &matBillboard );
		D3DXMATRIXA16	matbill_tran;
		// 0�� �ؽ�ó�� ������ �ؽ�ó�� �ø���
		g_pd3dDevice->SetTexture( 1, NULL );
		g_pd3dDevice->SetFVF( MYVERTEX::FVF );

		g_pd3dDevice->SetTexture( 0, speed_bar[0] );
		D3DXMatrixTranslation(&matbill_tran,-10.5f,0.5f,0.0f);
		matBillboard *= matbill_tran;
		g_pd3dDevice->SetTransform( D3DTS_WORLD, &matBillboard );
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(MYVERTEX) );
//		g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
}

VOID UI()
{
	D3DXMATRIX mat_Ortho;
	D3DXMatrixIdentity(&mat_Ortho);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &mat_Ortho);	
	D3DXMatrixOrthoLH (&mat_Ortho,WINDOW_WIDTH,WINDOW_HEIGHT,0,1);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &mat_Ortho);
	DrawBillboard();
	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
}

VOID Render()
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
	SetupLight();
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
		if(cameraCase == 1){
			D3DXVECTOR3 vLookatPt(myWorld._41,myWorld._42, myWorld._43);
			D3DXMatrixLookAtLH(&mView,g_pCamera->GetEye(),&vLookatPt,g_pCamera->GetUp());
		}
		else if(cameraCase == 2){			
			if(Mouse_Y<-20)
				Mouse_Y = -20;
			if(Mouse_Y>20)
				Mouse_Y = 20;

			D3DXVECTOR3 vEyePt(myWorld._41+10*cos(Mouse_X),myWorld._42+Mouse_Y,myWorld._43+10*sin(Mouse_X));
			D3DXVECTOR3 vLookatPt(myWorld._41,myWorld._42, myWorld._43);						
			D3DXVECTOR3 vUpVec(0.0f,1.0f,0.0f);						
			D3DXMatrixLookAtLH( &mView, &vEyePt, &vLookatPt, &vUpVec );
			mEye = vLookatPt - vEyePt;
		}

		drawXfile->set_view(mView);
		mapBox->set_view(mView);

		mMoving->getPosition(myCharacter,GSpeed);	
		D3DXMatrixIdentity(&myWorld);
		D3DXMatrixScaling(&myScale,BALL_SIZE,BALL_SIZE,BALL_SIZE);
		D3DXMatrixTranslation(&myTrans,myCharacter->getPosition().x,myCharacter->getPosition().y,myCharacter->getPosition().z);
	//	D3DXMatrixRotationAxis(&myRotate,myCharacter->hisptVelocity(),timeGetTime() / 1000.0f);
		myWorld *= myScale;
	//	myWorld *= myRotate;
		myWorld *= myTrans;
		drawXfile->DrawMyballShader(myWorld);	

		D3DXMatrixIdentity(&mBox);
		D3DXMatrixScaling(&myScale,3.2f,0.15f,3.2f);
		D3DXMatrixTranslation(&myTrans,80.0f,-5.2f,80.0f);
		mBox *= myScale;
		mBox *= myTrans;
		mapBox->DrawMyballShader(mBox);
		
		setItemList();
		itemListDraw();
		mMoving->getItem(myCharacter,itemList,BALL_REAL_SIZE,ITEM_REAL_SIZE);

		UI();
		g_pd3dDevice->EndScene();
	}
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

VOID beforeInitD3D(){
	m_fStartTime = (float)timeGetTime() * 0.001f;
	srand((unsigned)GetTickCount());
	g_pCamera = new ZCamera;
	drawXfile = new Xfile();
	mapBox = new Xfile();
	myCharacter = new Ball(START_LIFE,START_MANA,0,CHARACTER_MAX_LEVEL,( D3DXVECTOR3 )Pos,( D3DXVECTOR3 )Vel,( D3DXVECTOR3 )Vel);	
	mMoving = new Moving(GRAVITY,REVERSE_GRAVITY,GROUND,MYSIZE,CEILING,THRESHOLD,BALLSPEED,GAMESPEED,ABSORBANCE,MINBOUNDX,MINBOUNDY,MINBOUNDZ,MAXBOUNDX,MAXBOUNDX,MAXBOUNDX);
	itemList = new ItemsList();
	m_Ui = new Ui();
}

VOID afterRender(){
	delete g_pCamera;
	delete drawXfile;
	delete mapBox;
	delete myCharacter;
	delete mMoving;
	delete itemList;
	delete m_Ui;
}

VOID beforeRender(){
	InitGeometry();
	drawXfile->set_viewprojtexture(matProj,gLightColor);
	mapBox->set_viewprojtexture(matProj,gLightColor);
	
}
HRESULT initLoad(){
	if(!SUCCEEDED(initCharacter())){
		return E_FAIL;
	}
	if(!SUCCEEDED(m_Ui->initBillboard(g_pd3dDevice,"normal_speed.png",&speed_bar[0]))){
		return E_FAIL;
	}
	return S_OK;
}
//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_KEYDOWN:
		switch( wParam )
		{
		case 'E':
			break;
		case 'Q':
			if(cameraCase == 2){
			myCharacter->setGround(false);
			myCharacter->setVelocityY(myCharacter->getVelocity().y+0.3f);
			myCharacter->setPosition(myCharacter->getPosition()+myCharacter->getVelocity());
			}
			break;
		case 'W':
			if(cameraCase == 2){
				myCharacter->setGround(false);
				myCharacter->setVelocity(myCharacter->getVelocity()+mEye*0.05f*GSpeed);
				 }
			break;
		case 'D':
			break;
		case 'A':
			break;
		case 'S':
			if(cameraCase == 2){
				myCharacter->setVelocity(myCharacter->getVelocity()*0.9f);
			}
			break;
		case 'N':
			if(cameraCase == 1)
				cameraCase = 2;
			else if(cameraCase == 2)
				cameraCase =1;
			break;

		}
		break;
	case WM_RBUTTONDOWN :
		GSpeed = 0.5f;
		break;
	case WM_RBUTTONUP:
		GSpeed = 1.0f;
		break;
	case WM_LBUTTONDOWN:
		myCharacter->setGround(false);
		myCharacter->setVelocity(zero);
		myCharacter->setVelocity(myCharacter->getVelocity()+ mEye*1.0f*GAMESPEED);
		break;
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage( 0 );
		return 0;

	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	UNREFERENCED_PARAMETER( hInst );

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
		"D3D Tutorial", NULL
	};
	RegisterClassEx( &wc );

	// Create the application's window
	HWND hWnd = CreateWindow( "D3D Tutorial", "D3D Tutorial 06: Meshes",
		WS_OVERLAPPEDWINDOW, 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL, NULL, wc.hInstance, NULL );
	g_hwnd = hWnd;
	beforeInitD3D();
	// Initialize Direct3D
	if( SUCCEEDED( InitD3D( hWnd ) ) )
	{
		// Create the scene geometry
		if(SUCCEEDED( initLoad()))
		{
			// Show the window
			ShowWindow( hWnd, SW_SHOWDEFAULT );
			UpdateWindow( hWnd );

			// Enter the message loop
			MSG msg;
			ZeroMemory( &msg, sizeof( msg ) );
			beforeRender();
			while( msg.message != WM_QUIT )
			{
				if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
				else{
					Render();
					ProcessInputs();
				}
			}
		}
	}
	afterRender();
	UnregisterClass( "D3D Tutorial", wc.hInstance );
	return 0;
}