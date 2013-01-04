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
#include <crtdbg.h>	
#include <process.h>
//-----------------------------------------------------------------------------
// Header Files
//-----------------------------------------------------------------------------
#include "ZCamera.h"
#include "Variable.h"
#include "Settings.h"
#include "Xfile.h"
#include "Ball.h"
#include "Moving.h"
#include "SettingUI.h"
#include "Struct.h"
#include "Monster.h"
#include "Monai.h"
#include "CheckAI.h"
#include "SettingItems.h"
#include "SettingMonster.h"
#include "Skybox.h"
//-----------------------------------------------------------------------------
// Memory Check
//-----------------------------------------------------------------------------
#ifdef _DEBUG       
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#endif
//-----------------------------------------------------------------------------
// System Setting
//-----------------------------------------------------------------------------
HWND					g_hwnd = NULL;
DWORD					g_cxHeight = 0;	
DWORD					g_czHeight = 0;
DWORD					g_dwMouseX = 0;
DWORD					g_dwMouseY = 0;
//-----------------------------------------------------------------------------
// Camera Setting
//-----------------------------------------------------------------------------
ZCamera*				g_pCamera = NULL;
//-----------------------------------------------------------------------------
// Items Setting
//-----------------------------------------------------------------------------
SettingItems*			g_pSetItems;
//-----------------------------------------------------------------------------
// UI Setting
//-----------------------------------------------------------------------------
SettingUI*				g_pSetUi;
//-----------------------------------------------------------------------------
// Camera Setting
//-----------------------------------------------------------------------------
D3DXMATRIXA16			g_matAni;
INT						g_nCameraCase = 2;
FLOAT					g_fMouseX;
FLOAT					g_fMouseY;
//-----------------------------------------------------------------------------
// Character Matrix
//-----------------------------------------------------------------------------
D3DXMATRIX				g_matView;
D3DXMATRIX				g_matWorld;
D3DXMATRIX				g_matBoxWorld;

D3DXVECTOR4             g_v4LightColor(1.0f, 1.0f, 1.0f, 1.0f);//빛의 색
D3DXVECTOR3				g_v3Zero(0.0f,0.0f,0.0f); 
Ball*					g_pMyCharacter;
Moving*					g_pMoving;

D3DXMATRIXA16			g_matMyWorld;
D3DXMATRIXA16			g_matMyScale;
D3DXMATRIXA16			g_matMyTrans;
D3DXMATRIXA16			g_matMyRotate;
D3DXVECTOR3				g_v3EyePosition;
//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9				g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9		g_pd3dDevice = NULL; // Our rendering device
LPD3DXMESH				g_pMesh = NULL; // Our mesh object in sysmem
D3DMATERIAL9*			g_pMeshMaterials = NULL; // Materials for our mesh
LPDIRECT3DTEXTURE9*		g_pMeshTextures = NULL; // Textures for our mesh
DWORD					g_dwNumMaterials = 0L;   // Number of mesh materials
FLOAT					GSPEED = GAMESPEED;
D3DXMATRIX				g_matSetWorld;
D3DXMATRIX				g_matSetTrans;
D3DXMATRIX				g_matSetScale;
D3DXMATRIXA16			matWorld;
D3DXMATRIXA16			matView;
D3DXMATRIXA16			matProj;
//-----------------------------------------------------------------------------
// Map Draw
//-----------------------------------------------------------------------------
Xfile*					g_pMapBox;
CSkyBox*				g_pSkyBox;
//-----------------------------------------------------------------------------
// Monster Loading
//-----------------------------------------------------------------------------
SettingMonster*			g_pSetMonster = NULL;
//-----------------------------------------------------------------------------
// InitD3D
//-----------------------------------------------------------------------------
inline HRESULT InitD3D( HWND hWnd )
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
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// Create the D3DDevice
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,FALSE );
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,   D3DBLEND_SRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,  D3DBLEND_INVSRCALPHA );

	return S_OK;
}
//-----------------------------------------------------------------------------
// 각 행렬 제어, 카메라 세팅
//-----------------------------------------------------------------------------
inline VOID SetupCamera()
{
	/// 월드 행렬 설정
	D3DXMatrixIdentity( &matWorld );
	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	/// 뷰 행렬을 설정
	D3DXVECTOR3 vEyePt( 0.0f, 10.0f, 0.0f );
	D3DXVECTOR3 vLookatPt( 10.0f, 0.0f, 10.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
	/// 프로젝션 행렬 설정
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 1000.0f );
	g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	/// 카메라 초기화
	g_pCamera->SetView( &vEyePt, &vLookatPt, &vUpVec );
}

/**-----------------------------------------------------------------------------
* 마우스 처리
*------------------------------------------------------------------------------
*/
inline VOID InitGeometry()
{
	SetupCamera();
	POINT	pt;
	GetCursorPos( &pt );
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;
}

/**-----------------------------------------------------------------------------
* 입력 처리
*------------------------------------------------------------------------------*/
inline VOID ProcessInputs( VOID )
{
	POINT	pt;
	GetCursorPos( &pt );
	INT dx = pt.x - g_dwMouseX;	// 마우스의 변화값
	INT dy = pt.y - g_dwMouseY;	// 마우스의 변화값

	g_fMouseX += -dx*0.001;
	g_fMouseY += dy*0.05;


	if(g_nCameraCase == 1){
		if( GetAsyncKeyState( 'W' )||GetAsyncKeyState( 'w' ) ) g_pCamera->MoveLocalZ( 0.5f );	// 카메라 전진!
		if( GetAsyncKeyState( 'S' )||GetAsyncKeyState( 's' ) ) g_pCamera->MoveLocalZ( -0.5f );	// 카메라 후진!
		if( GetAsyncKeyState( 'A' )||GetAsyncKeyState( 'a' ) ) g_pCamera->MoveLocalX( -0.5f );	// 카메라 후진!
		if( GetAsyncKeyState( 'D' )||GetAsyncKeyState( 'd' ) ) g_pCamera->MoveLocalX( 0.5f );	// 카메라 후진!
		if( GetAsyncKeyState( VK_ESCAPE ) ) PostMessage( g_hwnd, WM_DESTROY, 0, 0L );
		//if( GetAsyncKeyState( VK_LBUTTON ) ) g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
		//if( GetAsyncKeyState( VK_RBUTTON ) ) g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	}
	else if(g_nCameraCase == 2){
		g_pCamera->RotateLocalX( dy * MOUSE_SENSITIVE );	// 마우스의 Y축 회전값은 3D world의  X축 회전값
		g_pCamera->RotateLocalY( dx * MOUSE_SENSITIVE );	// 마우스의 X축 회전값은 3D world의  Y축 회전값
		D3DXMATRIXA16*	pmatView = g_pCamera->GetViewMatrix();		// 카메라 행렬을 얻는다.
		g_pd3dDevice->SetTransform( D3DTS_VIEW, pmatView );			// 카메라 행렬 셋팅
	}

	// 마우스를 윈도우의 중앙으로 초기화
	SetCursor( NULL );	// 마우스를 나타나지 않게 않다.
	RECT	rc;
	GetClientRect( g_hwnd, &rc );
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen( g_hwnd, &pt );
	SetCursorPos( pt.x, pt.y );
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;


}
/**-----------------------------------------------------------------------------
* 빛 처리
*------------------------------------------------------------------------------*/
inline VOID SetupLight()
{
	D3DMATERIAL9 mtrl;
	ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	g_pd3dDevice->SetMaterial( &mtrl );

	/// 광원 설정
	D3DXVECTOR3 vecDir;									/// 방향성 광원(directional light)이 향할 빛의 방향
	D3DLIGHT9 light;									/// 광원 구조체
	ZeroMemory( &light, sizeof(D3DLIGHT9) );			/// 구조체를 0으로 지운다.

	light.Type       = D3DLIGHT_POINT;			/// 광원의 종류(점 광원,방향성 광원,스포트라이트)
	light.Diffuse.r  = 1.0f;							/// 광원의 색깔과 밝기
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 0.2f;
	light.Position.x = 30.0f;
	light.Position.y = 30.0f;
	light.Position.z = 30.0f;

	vecDir = D3DXVECTOR3( 1, 1, 1 );					/// 광원 고정

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );	/// 광원의 방향을 단위벡터로 만든다.
	light.Range       = 1000.0f;									/// 광원이 다다를수 있는 최대거리

	g_pd3dDevice->SetLight( 0, &light );							/// 디바이스에 0번 광원 설치
	g_pd3dDevice->LightEnable( 0, TRUE );							/// 0번 광원을 켠다
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );			/// 광원설정을 켠다
	g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00404040 );		/// 환경광원(ambient light)의 값 설정
}

/**-----------------------------------------------------------------------------
* Clean
*------------------------------------------------------------------------------*/
inline VOID Cleanup()
{
	if( g_pMeshMaterials != NULL )
		delete[] g_pMeshMaterials;

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
/**-----------------------------------------------------------------------------
* Draw Position
*------------------------------------------------------------------------------*/
inline D3DXMATRIX DrawPosition(/**/D3DXVECTOR3 scale,/**/D3DXVECTOR3 trans)
{
	D3DXMatrixIdentity(&g_matSetWorld);
	D3DXMatrixScaling(&g_matSetScale,scale.x,scale.y,scale.z);
	D3DXMatrixTranslation(&g_matSetTrans,trans.x,trans.y,trans.z);
	return g_matSetWorld * g_matSetScale * g_matSetTrans;
}
inline D3DXMATRIX DrawPosition(D3DXMATRIX* world,/**/D3DXVECTOR3 scale,/**/D3DXVECTOR3 trans)
{
	D3DXMatrixIdentity(world);
	D3DXMatrixScaling(&g_matSetScale,scale.x,scale.y,scale.z);
	D3DXMatrixTranslation(&g_matSetTrans,trans.x,trans.y,trans.z);
	*world = *world * g_matSetScale * g_matSetTrans;
	return *world;
}

inline VOID CameraCase(){
	if(g_nCameraCase == 1){
		D3DXVECTOR3 vLookatPt(g_matMyWorld._41,g_matMyWorld._42, g_matMyWorld._43);
		D3DXMatrixLookAtLH(&g_matView,g_pCamera->GetEye(),g_pCamera->GetLookat(),g_pCamera->GetUp());
	}
	else if(g_nCameraCase == 2){			
		if(g_fMouseY<-25)
			g_fMouseY = -25;
		if(g_fMouseY>25)
			g_fMouseY = 25;

		D3DXVECTOR3 vEyePt(g_matMyWorld._41+10*cos(g_fMouseX),g_matMyWorld._42+g_fMouseY,g_matMyWorld._43+10*sin(g_fMouseX));
		D3DXVECTOR3 vLookatPt(g_matMyWorld._41,g_matMyWorld._42, g_matMyWorld._43);						
		D3DXVECTOR3 vUpVec(0.0f,1.0f,0.0f);						
		D3DXMatrixLookAtLH( &g_matView, &vEyePt, &vLookatPt, &vUpVec );
		g_v3EyePosition = vLookatPt - vEyePt;
	}
}
/**-----------------------------------------------------------------------------
* Render
*------------------------------------------------------------------------------*/
inline VOID Render(FLOAT time)
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
//	SetupLight();
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
		//-----------------------------------------------------------------------------
		// Camera Setting
		//-----------------------------------------------------------------------------
		CameraCase();	
		//-----------------------------------------------------------------------------
		// View Setting
		//-----------------------------------------------------------------------------
		g_pMyCharacter->SetViewMatrix(g_matView);
		g_pSetMonster->SetViewMatrix(g_matView);
		g_pMapBox->SetView(g_matView);
		g_pSetItems->SetViewMatrix(g_matView);
		//-----------------------------------------------------------------------------
		// Move Setting
		//-----------------------------------------------------------------------------
		g_pMoving->GetPosition(GSPEED);			
		//-----------------------------------------------------------------------------
		// Character Setting
		//-----------------------------------------------------------------------------
		g_pMyCharacter->Draw(&g_matMyWorld);
		//-----------------------------------------------------------------------------
		// Monster Setting
		//-----------------------------------------------------------------------------
		g_pSetMonster->Draw(&g_matBoxWorld,&g_matView,g_pCamera,time,GSPEED,g_nCameraCase);
		//-----------------------------------------------------------------------------
		// Room Setting
		//-----------------------------------------------------------------------------
		g_pMapBox->DrawMyballShader(DrawPosition(D3DXVECTOR3(3.2f,0.15f,3.2f),D3DXVECTOR3(MAXBOUNDX/2,-5.2f,MAXBOUNDZ/2)));
		//-----------------------------------------------------------------------------
		// Items Setting
		//-----------------------------------------------------------------------------
		g_pSetItems->Draw(time, g_pMyCharacter);		
		//-----------------------------------------------------------------------------
		// Sky box Setting
		//-----------------------------------------------------------------------------
		g_pSkyBox->Render();   
		//-----------------------------------------------------------------------------
		// UI Setting
		//-----------------------------------------------------------------------------
		g_pSetUi->DrawUI(abs((INT)D3DXVec3Length(&g_pMyCharacter->GetVelocity())),g_pMyCharacter->HisLife(),g_pMyCharacter->HisMana(),g_pMyCharacter->HisDef(),g_pSetMonster->GetMonster()->GetLife()/*g_pMon->HisLife()*/);
		g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

		g_pd3dDevice->EndScene();

	}
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}


inline VOID AfterInitD3D(){
	float m_fStartTime = (FLOAT)timeGetTime() * 0.001f;
	srand((unsigned)GetTickCount());
	D3DXVECTOR4 m_v4Pos( START_POSITIONX, START_POSITIONY, START_POSITIONZ, 1.0f );
	D3DXVECTOR4 m_v4Vel( START_VELOCITYX, START_VELOCITYY, START_VELOCITYZ, 0.0f );

	g_pCamera = new ZCamera;
	g_pMapBox = new Xfile();
	g_pSetItems = new SettingItems(m_fStartTime,g_pd3dDevice);
	g_pMyCharacter = new Ball(( D3DXVECTOR3 )m_v4Pos,( D3DXVECTOR3 )m_v4Vel,( D3DXVECTOR3 )m_v4Vel, g_pd3dDevice);	
	g_pMoving = new Moving(g_pMyCharacter);
	
	g_pSetMonster = new SettingMonster(g_pd3dDevice,g_pMyCharacter,g_pMoving,m_fStartTime);
	g_pSkyBox = new CSkyBox(g_pd3dDevice);
	g_pSetUi = new SettingUI(g_pd3dDevice);
}

inline VOID AfterRender(){
	delete g_pCamera;
	delete g_pMapBox;
	delete g_pMyCharacter;
	delete g_pMoving;
	delete g_pSetItems;
	delete g_pSetMonster;
//	delete g_pMai;
	delete g_pSkyBox;
	delete g_pSetUi;
}

inline VOID BeforeRender(){
	InitGeometry();
	g_pMyCharacter->SetProjectionMatrix(matProj,g_v4LightColor);
	g_pSetMonster->SetProjectionMatrix(matProj,g_v4LightColor);
	g_pMapBox->SetViewprojtexture(matProj,g_v4LightColor);
	g_pSetItems->SetProjectionMatrix(matProj,g_v4LightColor);
}
inline HRESULT initLoad(){
	if(FAILED(g_pMapBox->InitballMesh(g_pd3dDevice,"FieldstoneNoisy.tga","FieldstoneBumpDOT3.tga","Monster.fx","Monster.x"))){
		return E_FAIL;
	}
	g_pSkyBox->InitVB(); 
	g_pSkyBox->InitTexture();
	g_pMyCharacter->SetXfile();
	g_pSetItems->SetXfile();
	g_pSetMonster->SetXfile();
	return S_OK;
}
//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
inline LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_SPACE:
			if(g_pMyCharacter->SpendMana(-10)){
				g_pMyCharacter->SetGround(FALSE);
				g_pMyCharacter->SetVelocity(g_v3Zero);
				g_pMyCharacter->SetVelocity(g_pMyCharacter->GetVelocity()+ g_v3EyePosition*2.5f*GAMESPEED);
			}
			break;
		case 'E':
			break;
		case 'Q':
			if(g_nCameraCase == 2){
				g_pMyCharacter->SetGround(FALSE);
				g_pMyCharacter->SetVelocityY(g_pMyCharacter->GetVelocity().y+0.005f);
				g_pMyCharacter->SetPosition(g_pMyCharacter->GetPosition()+g_pMyCharacter->GetVelocity());
			}
			break;
		case 'W':
			if(g_nCameraCase == 2){
				g_pMyCharacter->SetGround(FALSE);
				g_pMyCharacter->SetVelocity(g_pMyCharacter->GetVelocity()+g_v3EyePosition*0.05f*GSPEED);
			}
			break;
		case 'D':
			break;
		case 'A':
			break;
		case 'S':
			if(g_nCameraCase == 2){
				g_pMyCharacter->SetVelocity(g_pMyCharacter->GetVelocity()*0.9f);
			}
			break;
		case 'N':
			if(g_nCameraCase == 1)
				g_nCameraCase = 2;
			else if(g_nCameraCase == 2)
				g_nCameraCase =1;
			break;
		}
		break;
	case WM_RBUTTONDOWN :
		GSPEED = 0.5f;
		break;
	case WM_RBUTTONUP:
		GSPEED = 1.0f;
		break;
	case WM_LBUTTONDOWN:
		g_pMyCharacter->SetGround(FALSE);
		g_pMyCharacter->SetVelocity(g_v3Zero);
		g_pMyCharacter->SetVelocity(g_pMyCharacter->GetVelocity()+ g_v3EyePosition*1.5f*GAMESPEED);
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
// Desc: The application's entry poINT
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );//memory leak check

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
	HWND hWnd = CreateWindow( "D3D Tutorial", "GongGong",
		WS_OVERLAPPEDWINDOW, 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL, NULL, wc.hInstance, NULL );

	g_hwnd = hWnd;

	// Initialize Direct3D
	if( SUCCEEDED( InitD3D( hWnd ) ) )
	{

		AfterInitD3D();

		// Create the scene geometry
		if(SUCCEEDED( initLoad()))
		{
			// Show the window
			ShowWindow( hWnd, SW_SHOWDEFAULT );
			UpdateWindow( hWnd );

			// Enter the message loop
			MSG msg;
			ZeroMemory( &msg, sizeof( msg ) );

			BeforeRender();

			while( msg.message != WM_QUIT )
			{
				if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
				else{
					Render((FLOAT)timeGetTime() * 0.001f);

					ProcessInputs();

				}
			}
		}
	}
	AfterRender();
	UnregisterClass( "D3D Tutorial", wc.hInstance );
	return 0;
}