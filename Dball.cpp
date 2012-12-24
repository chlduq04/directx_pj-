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
#include "Items.h"
#include "ItemsList.h"
#include "Ui.h"
#include "Struct.h"
#include "CModel.h"
#include "Macros.h"
#include "Monster.h"
#include "Monai.h"
#include "Missile.h"
#include "Wall.h"
#include "CheckAI.h"
//-----------------------------------------------------------------------------
// Memory Check
//-----------------------------------------------------------------------------
#ifdef _DEBUG       
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#endif
//-----------------------------------------------------------------------------
// Drow Billboard
//-----------------------------------------------------------------------------
MYVERTEX vtx[4] = {
	{WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/120, 0, 0, 1},
	{WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2, 0, 0, 0 },
	{WINDOW_WIDTH/2, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/120, 0, 1, 1},
	{WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, 0, 1, 0}
};
MYVERTEX hpVtx[4] = {
	{WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/50, 0, 0, 1},
	{WINDOW_WIDTH/2-WINDOW_WIDTH/20, -WINDOW_HEIGHT/2, 0, 0, 0 },
	{WINDOW_WIDTH/2, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/50, 0, 1, 1},
	{WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, 0, 1, 0}
};
MYVERTEX mapVtx[4] = {
	{WINDOW_WIDTH/2-WINDOW_WIDTH/5, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/5, 0, 0, 1},
	{WINDOW_WIDTH/2-WINDOW_WIDTH/5, -WINDOW_HEIGHT/2, 0, 0, 0 },
	{WINDOW_WIDTH/2, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/5, 0, 1, 1},
	{WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, 0, 1, 0}
};
MYVERTEX monHp[4] = {
	{WINDOW_WIDTH/2-WINDOW_WIDTH/5, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/5, 0, 0, 1},
	{WINDOW_WIDTH/2-WINDOW_WIDTH/5, -WINDOW_HEIGHT/2, 0, 0, 0 },
	{WINDOW_WIDTH/2, -WINDOW_HEIGHT/2+WINDOW_HEIGHT/5, 0, 1, 1},
	{WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, 0, 1, 0}
};
LPDIRECT3DTEXTURE9		g_pSpeedBar[10] = { NULL, NULL, NULL };// 빌보드로 사용할 텍스처
D3DXMATRIX				matBillboard;

//-----------------------------------------------------------------------------
// System Setting
//-----------------------------------------------------------------------------
HWND					g_hwnd = NULL;
DWORD					g_cxHeight = 0;	
DWORD					g_czHeight = 0;
DWORD					g_dwMouseX = 0;
DWORD					g_dwMouseY = 0;
DWORD					VERTEX_FVF = ( D3DFVF_XYZ | D3DFVF_DIFFUSE );
//-----------------------------------------------------------------------------
// Camera Setting
//-----------------------------------------------------------------------------
ZCamera*				g_pCamera = NULL;
//-----------------------------------------------------------------------------
// Model Loading
//-----------------------------------------------------------------------------
CModel*					g_pModel = NULL; // A model object to work with
//-----------------------------------------------------------------------------
// Draw Wall
//-----------------------------------------------------------------------------
Wall*					g_pWall = NULL;
BOOL					g_bWall = FALSE;
//-----------------------------------------------------------------------------
// Items Setting
//-----------------------------------------------------------------------------
FLOAT					g_fStartTime; 
ItemsList*				g_pItemList;		
Ui*						g_pUi;
D3DXMATRIXA16			g_matIteg_matWorld;
static INT				g_nItemSerialNum = 0;
//-----------------------------------------------------------------------------
// Camera Setting
//-----------------------------------------------------------------------------
D3DXMATRIXA16			g_matAni;
INT						g_nCameraCase = 1;
FLOAT					g_fMouseX;
FLOAT					g_fMouseY;
//-----------------------------------------------------------------------------
// Character Matrix
//-----------------------------------------------------------------------------
D3DXMATRIX				g_matView;
D3DXMATRIXA16			g_matWorld;
D3DXMATRIXA16			g_matBoxWorld;
D3DXMATRIXA16			g_matMisWorld;

D3DXVECTOR4             g_v4LightColor(1.0f, 1.0f, 1.0f, 1.0f);//빛의 색
D3DXVECTOR3				g_v3Zero(0.0f,0.0f,0.0f); 
Ball*					g_pMyCharacter;
Moving*					g_pMoving;

D3DXMATRIXA16			g_matMyWorld;
D3DXMATRIXA16			g_matMyScale;
D3DXMATRIXA16			g_matMyTrans;
D3DXMATRIXA16			g_matMyRotate;
D3DXMATRIXA16			g_matMyRotateX;
D3DXMATRIXA16			g_matMyRotateY;
D3DXMATRIXA16			g_matMyRotateZ;
D3DXVECTOR3				g_v3EyePosition;
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
// Laser variables
//-----------------------------------------------------------------------------
D3DXVECTOR3				ret1;
D3DXVECTOR3				ret2;
FLOAT					GSPEED = GAMESPEED;
BOOL					bWireFrame = true;
D3DXVECTOR3				curve[4];
//D3DXVECTOR3				beforeMonPos;
D3DXVECTOR3				beforeMypos;
D3DXVECTOR3				laserSpeed;
BOOL					SetBefore = FALSE;
FLOAT					Settime;
//-----------------------------------------------------------------------------
// Xfile Draw
//-----------------------------------------------------------------------------
Xfile* g_pDrawXfile;
Xfile* g_pMapBox;
Xfile* g_pMonDetail[ACTION_PATTERN_COUNT+1];
//-----------------------------------------------------------------------------
// Monster
//-----------------------------------------------------------------------------
Monster* g_pMon;
Monai* g_pMai;
Missile* g_pMissile[10];
//-----------------------------------------------------------------------------
// Monster
//-----------------------------------------------------------------------------
Checkai* g_pResult;
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
*------------------------------------------------------------------------------
*/
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

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
inline VOID Cleanup()
{
	if( g_pMeshMaterials != NULL )
		delete[] g_pMeshMaterials;

	if(g_pSpeedBar){
		for(INT i=0;i<10;i++){
			if(g_pSpeedBar[i]){
				g_pSpeedBar[i]->Release(); 
				g_pSpeedBar[i] = NULL;
				delete g_pSpeedBar[i];
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
inline VOID Setg_pItemList(FLOAT time){
	if( time-g_fStartTime >=  1.0f){
		if((rand()%10==5)&&(g_pItemList->GetCount()<10)){
			D3DXVECTOR3 iPosition(rand()%100,rand()%100,rand()%100);
			g_pItemList->SetNode(new Items(rand()%3,1,iPosition,g_nItemSerialNum++,time));
		}
		g_fStartTime = time; 
	}
}

inline VOID g_pItemListDraw(FLOAT time){
	Items* nowNode = g_pItemList->GetStart()->GetNext();
	if(nowNode!=g_pItemList->GetEnd()){
		while(nowNode->GetNext()!=g_pItemList->GetEnd()){
			if(time-(nowNode->GetTime())>20){
				Items* deleteNode = nowNode;
				nowNode=nowNode->GetNext();
				g_pItemList->DelNode(deleteNode);
			}else{
				D3DXMatrixIdentity(&g_matIteg_matWorld);
				D3DXMatrixScaling(&g_matMyScale,0.1f,0.1f,0.1f);
				D3DXMatrixRotationY(&g_matMyRotate, time);
				D3DXMatrixTranslation(&g_matMyTrans,nowNode->GetPosition().x,nowNode->GetPosition().y,nowNode->GetPosition().z);
				g_matIteg_matWorld *= g_matMyScale;
				g_matIteg_matWorld *= g_matMyRotate;
				g_matIteg_matWorld *= g_matMyTrans;
				g_pMapBox->DrawMyballShader(g_matIteg_matWorld);
				nowNode=nowNode->GetNext();
			}
		}
	}
}

inline VOID DrawUi(){
	g_pUi->SetUI();

	INT velocity = abs((INT)D3DXVec3Length(&g_pMyCharacter->GetVelocity()));
	if(velocity>50){
		velocity = 50;
	}
	switch(velocity){
	case 50 : case 49 : g_pUi->DrawBillboard(g_pSpeedBar[1],&matBillboard,-10.5f,120.0f,0.0f,vtx);
	case 48 : case 47 : g_pUi->DrawBillboard(g_pSpeedBar[1],&matBillboard,-10.5f,115.0f,0.0f,vtx);
	case 46 : case 45 : g_pUi->DrawBillboard(g_pSpeedBar[1],&matBillboard,-10.5f,110.0f,0.0f,vtx);
	case 44 : case 43 : g_pUi->DrawBillboard(g_pSpeedBar[1],&matBillboard,-10.5f,105.0f,0.0f,vtx);
	case 42 : case 41 : g_pUi->DrawBillboard(g_pSpeedBar[2],&matBillboard,-10.5f,100.0f,0.0f,vtx);
	case 40 : case 39 : g_pUi->DrawBillboard(g_pSpeedBar[2],&matBillboard,-10.5f,95.0f,0.0f,vtx);
	case 38 : case 37 : g_pUi->DrawBillboard(g_pSpeedBar[2],&matBillboard,-10.5f,90.0f,0.0f,vtx);
	case 36 : case 35 : g_pUi->DrawBillboard(g_pSpeedBar[2],&matBillboard,-10.5f,85.0f,0.0f,vtx);
	case 34 : case 33 : g_pUi->DrawBillboard(g_pSpeedBar[2],&matBillboard,-10.5f,80.0f,0.0f,vtx);
	case 32 : case 31 : g_pUi->DrawBillboard(g_pSpeedBar[2],&matBillboard,-10.5f,75.0f,0.0f,vtx);
	case 30 : case 29 : g_pUi->DrawBillboard(g_pSpeedBar[2],&matBillboard,-10.5f,70.0f,0.0f,vtx);
	case 28 : case 27 : g_pUi->DrawBillboard(g_pSpeedBar[2],&matBillboard,-10.5f,65.0f,0.0f,vtx);
	case 26 : case 25 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,60.0f,0.0f,vtx);
	case 24 : case 23 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,55.0f,0.0f,vtx);
	case 22 : case 21 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,50.0f,0.0f,vtx);
	case 20 : case 19 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,45.0f,0.0f,vtx);
	case 18 : case 17 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,40.0f,0.0f,vtx);
	case 16 : case 15 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,35.0f,0.0f,vtx);
	case 14 : case 13 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,30.0f,0.0f,vtx);
	case 12 : case 11 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,25.0f,0.0f,vtx);
	case 10 : case 9 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,20.0f,0.0f,vtx);
	case 8 : case 7 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,15.0f,0.0f,vtx);
	case 6 : case 5 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,10.0f,0.0f,vtx);
	case 4 : case 3 : g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,5.0f,0.0f,vtx);
	case 2 : case 1: g_pUi->DrawBillboard(g_pSpeedBar[0],&matBillboard,-10.5f,0.0f,0.0f,vtx);
		break;
	}
//	g_pUi->DrawBillboard(g_pSpeedBar[6],&matBillboard,-WINDOW_WIDTH+WINDOW_WIDTH/5,0,0,mapVtx);

	for(INT i=0;i<g_pMyCharacter->HisLife()/10;i++){
		g_pUi->DrawBillboard(g_pSpeedBar[3],&matBillboard,-WINDOW_WIDTH+WINDOW_WIDTH/20,12.0f*i,0.0f,hpVtx);
	}
	for(INT i=0;i<g_pMyCharacter->HisMana()/10;i++){
		g_pUi->DrawBillboard(g_pSpeedBar[4],&matBillboard,-WINDOW_WIDTH+WINDOW_WIDTH/20*2,12.0f*i,0.0f,hpVtx);
	}
	for(INT i=0;i<g_pMyCharacter->HisDef()/10;i++){
		g_pUi->DrawBillboard(g_pSpeedBar[5],&matBillboard,-WINDOW_WIDTH+WINDOW_WIDTH/20*3,12.0f*i,0.0f,hpVtx);
	}

	INT m = g_pMon->HisLife()/50;
	for(INT i=0;i<m;i++){
		g_pUi->DrawBillboard(g_pSpeedBar[3],&matBillboard,-WINDOW_WIDTH+WINDOW_WIDTH/20*i,WINDOW_HEIGHT-m,0.0f,hpVtx);
	}

	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);// return to origin prog=
}


inline VOID modelLeader(FLOAT time){
	if(g_pModel){
		g_pModel->Update(time);
		g_pModel->Draw();
	}
}
//inline VOID RenderPolyLine( LPDIRECT3DDEVICE9 device, UINT count = 100 )
//{
//	if(!SetBefore){
//		beforeMypos = g_pMyCharacter->GetPosition();
//		SetBefore = true;
//	}
//	laserSpeed = g_pMyCharacter->GetPosition() - beforeMypos;
//	D3DXVec3Normalize(&laserSpeed,&laserSpeed);
//	beforeMypos += laserSpeed * 0.5f;
//
//	curve[0] = g_pMon->GetPosition();
//	curve[1] = g_pMon->GetPosition();
//	curve[2] = beforeMypos;
//	curve[3] = beforeMypos;
//	D3DXVec3CatmullRom( &ret1, &curve[ 0 ], &curve[ 1 ], &curve[ 2 ], &curve[ 3 ], (FLOAT)0 / count );
//	D3DXMatrixScaling(&g_matMyScale,BALL_SIZE,BALL_SIZE,BALL_SIZE);
//
//	for( INT i = 0; i < count + 1; i++ )
//	{
//		D3DXMatrixIdentity(&matWorld);
//		D3DXVec3CatmullRom( &ret2, &curve[ 0 ], &curve[ 1 ], &curve[ 2 ], &curve[ 3 ], (FLOAT)(i + 1) / count );
//		D3DXMatrixTranslation(&g_matMyTrans,ret1.x,ret1.y,ret1.z);
//		matWorld *= g_matMyScale;
//		matWorld *= g_matMyTrans;
//		g_pDrawXfile->DrawMyballShader(matWorld);
//		ret1 = ret2;
//	}
//}

inline VOID Render(FLOAT time)
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
//	SetupLight();
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{

		//-----------------------------------------------------------------------------
		// Camera Setting
		//-----------------------------------------------------------------------------
		
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
		

		//-----------------------------------------------------------------------------
		// View Setting
		//-----------------------------------------------------------------------------
		g_pDrawXfile->SetView(g_matView);
		g_pMapBox->SetView(g_matView);
//		BlackBox->SetView(g_matView);
		for(INT i=0;i<ACTION_PATTERN_COUNT+1;i++){
			g_pMonDetail[i]->SetView(g_matView);
		}
		//-----------------------------------------------------------------------------
		// Character Setting
		//-----------------------------------------------------------------------------
		g_pMoving->GetPosition(GSPEED);	
		
		D3DXMatrixIdentity(&g_matMyWorld);
		D3DXMatrixScaling(&g_matMyScale,BALL_SIZE,BALL_SIZE,BALL_SIZE);
		D3DXMatrixTranslation(&g_matMyTrans,g_pMyCharacter->GetPosition().x,g_pMyCharacter->GetPosition().y,g_pMyCharacter->GetPosition().z);
		g_matMyWorld *= g_matMyScale;
		g_matMyWorld *= g_matMyTrans;
		g_pDrawXfile->DrawMyballShader(g_matMyWorld);	


//		RenderPolyLine(g_pd3dDevice);

		//-----------------------------------------------------------------------------
		// Monster Setting
		//-----------------------------------------------------------------------------
		g_pMai->GetPositionMon(time);
		D3DXMatrixIdentity(&g_matBoxWorld);
//		D3DXMatrixTranslation(&g_matMyTrans,100.0f,0,0);
		D3DXMatrixScaling(&g_matMyScale,MON_SIZE,MON_SIZE,MON_SIZE);
		D3DXMatrixTranslation(&g_matMyTrans,g_pMon->GetPosition().x,g_pMon->GetPosition().y,g_pMon->GetPosition().z);
		g_matBoxWorld *= g_matMyScale;
		if(g_pMai->GetActionNum()==4){
			D3DXMatrixRotationY(&g_matMyRotate,time*GAMESPEED*10);
			g_matBoxWorld *= g_matMyRotate;
		}else{
			D3DXVECTOR3 monRotationX = D3DXVECTOR3(1,0,1);
			D3DXVECTOR3	monRotationZ = D3DXVECTOR3(g_pMon->GetVelocity().x,0,g_pMon->GetVelocity().z);
			D3DXVec3Normalize(&monRotationX,&monRotationX);
			D3DXVec3Normalize(&monRotationZ,&monRotationZ);
			FLOAT angle=acos(D3DXVec3Dot(&monRotationX,&monRotationZ))*180/D3DX_PI;
			D3DXMatrixRotationY(&g_matMyRotate,angle);
			g_matBoxWorld *= g_matMyRotate;
		}
		g_matBoxWorld *= g_matMyTrans;
//		g_pMonDetail[g_pMai->GetActionNum()]->DrawMyballShader(g_matBoxWorld);	
		if(g_nCameraCase == 1){
			g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_matBoxWorld );
			D3DXMATRIXA16*	pmatView = g_pCamera->GetViewMatrix();		// 카메라 행렬을 얻는다.
			g_pd3dDevice->SetTransform( D3DTS_VIEW, pmatView );			// 카메라 행렬 셋팅
		}
		else if(g_nCameraCase == 2){
			g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_matBoxWorld );
			D3DXMATRIXA16*	pmatView = g_pCamera->GetViewMatrix();		// 카메라 행렬을 얻는다.
			g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_matView);			// 카메라 행렬 셋팅
		}
		modelLeader(g_pMai->GetMotionTime());

		//-----------------------------------------------------------------------------
		// Missile Setting
		//-----------------------------------------------------------------------------
		if(g_pMai->GetMsionall()){
			for(INT i=0;i<10;i++){
				D3DXMatrixIdentity(&g_matMisWorld);
				D3DXMatrixScaling(&g_matMyScale,MISSILE_SIZE,MISSILE_SIZE,MISSILE_SIZE);
				D3DXMatrixTranslation(&g_matMyTrans,g_pMissile[i]->GetPosition().x,g_pMissile[i]->GetPosition().y,g_pMissile[i]->GetPosition().z);
				g_matMisWorld *= g_matMyScale;
				g_matMisWorld *= g_matMyTrans;
				g_pDrawXfile->DrawMyballShader(g_matMisWorld);
				g_pMoving->CrashMissile(g_pMissile[i]);
			}
		}
		//-----------------------------------------------------------------------------
		// Room Setting
		//-----------------------------------------------------------------------------
		D3DXMatrixIdentity(&g_matBoxWorld);
		D3DXMatrixScaling(&g_matMyScale,3.2f,0.15f,3.2f);
		D3DXMatrixTranslation(&g_matMyTrans,MAXBOUNDX/2,-5.2f,MAXBOUNDZ/2);
		g_matBoxWorld *= g_matMyScale;
		g_matBoxWorld *= g_matMyTrans;
		g_pMapBox->DrawMyballShader(g_matBoxWorld);

//		g_pMoving->GetPositionWall(g_pMyCharacter,g_pWall,D3DXVECTOR3(30,0,0),GSPEED);

		if(g_pMoving->GetMonWall())
		{
			if(!g_bWall){
			D3DXMatrixIdentity(&g_matBoxWorld);
			if(g_pMoving->GetMonMaxWallX()){
				D3DXMatrixScaling(&g_matMyScale,0.001f,3.2f,3.2f);
				D3DXMatrixTranslation(&g_matMyTrans,g_pMoving->GetMaxX(),g_pWall->GetPositionY()+MAXBOUNDY/2,MAXBOUNDZ/2);
			}
			else if(g_pMoving->GetMonMinWallX()){
				D3DXMatrixScaling(&g_matMyScale,0.001f,3.2f,3.2f);
				D3DXMatrixTranslation(&g_matMyTrans,g_pMoving->GetMinX(),g_pWall->GetPositionY()+MAXBOUNDY/2,MAXBOUNDZ/2);
			}
			else if(g_pMoving->GetMonMaxWallY()){
			}
			else if(g_pMoving->GetMonMinWallY()){
			}
			else if(g_pMoving->GetMonMaxWallZ()){
				D3DXMatrixScaling(&g_matMyScale,3.2f,3.2f,0.001f);
				D3DXMatrixTranslation(&g_matMyTrans,MAXBOUNDX/2,g_pWall->GetPositionY()+MAXBOUNDY/2,g_pMoving->GetMaxZ());
			}
			else if(g_pMoving->GetMonMinWallZ()){
				D3DXMatrixScaling(&g_matMyScale,3.2f,3.2f,0.001f);
				D3DXMatrixTranslation(&g_matMyTrans,MAXBOUNDX/2,g_pWall->GetPositionY()+MAXBOUNDY/2,g_pMoving->GetMinZ());
			}
			g_matBoxWorld *= g_matMyScale;
			g_matBoxWorld *= g_matMyTrans;
			g_pMapBox->DrawMyballShader(g_matBoxWorld);
			g_bWall = true;
			}else{
				g_bWall = FALSE;
			}
		}

		g_pMoving->GetItem(g_pItemList);		
		Setg_pItemList(time);
		g_pItemListDraw(time);

		g_pMoving->CrashMon(time);

		DrawUi();
		g_pd3dDevice->EndScene();

	}
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}


inline VOID AfterInitD3D(){
	float m_fStartTime = (FLOAT)timeGetTime() * 0.001f;
	srand((unsigned)GetTickCount());
	D3DXVECTOR4 m_v4Pos( START_POSITIONX, START_POSITIONY, START_POSITIONZ, 1.0f );
	D3DXVECTOR4 m_v4Vel( START_VELOCITYX, START_VELOCITYY, START_VELOCITYZ, 0.0f );
	D3DXVECTOR4 m_v4MonPos( START_MON_POSITIONX, START_MON_POSITIONY, START_MON_POSITIONZ, 1.0f );
	D3DXVECTOR4 m_v4MonVel( START_VELOCITYX, START_VELOCITYY, START_VELOCITYZ, 0.0f );

	g_pCamera = new ZCamera;
	g_pWall = new Wall();
	for(INT i=0;i<10;i++){g_pMissile[i]= new Missile();}
	g_pDrawXfile = new Xfile();
	g_pMapBox = new Xfile();
	for(INT i=0;i<ACTION_PATTERN_COUNT+1;i++){g_pMonDetail[i] = new Xfile();}
	g_pMyCharacter = new Ball(( D3DXVECTOR3 )m_v4Pos,( D3DXVECTOR3 )m_v4Vel,( D3DXVECTOR3 )m_v4Vel);	
	g_pItemList = new ItemsList();
	g_pModel = new CModel(g_pd3dDevice);
	g_pMon = new Monster((D3DXVECTOR3)m_v4MonPos,(D3DXVECTOR3)m_v4MonVel,(D3DXVECTOR3)m_v4MonVel);
	g_pMoving = new Moving(g_pMyCharacter,g_pMon,g_pWall);
	g_pResult = new Checkai();
	g_pMai = new Monai(g_pMon,g_pMyCharacter,g_pMissile,g_pMoving,g_pWall,g_pResult,g_pModel, m_fStartTime);
	g_pUi = new Ui(g_pd3dDevice);
}

inline VOID AfterRender(){
	for(INT i=0;i<10;i++){delete g_pMissile[i];}
	delete g_pWall;
	delete g_pCamera;
	delete g_pDrawXfile;
	delete g_pMapBox;
	for(INT i=0;i<ACTION_PATTERN_COUNT+1;i++){delete g_pMonDetail[i];};
	delete g_pMyCharacter;
	delete g_pMoving;
	delete g_pItemList;
	delete g_pModel;
	delete g_pMon;
	delete g_pMai;
	delete g_pResult;
	delete g_pUi;
}

inline VOID BeforeRender(){
	InitGeometry();
	g_pDrawXfile->SetViewprojtexture(matProj,g_v4LightColor);
	g_pMapBox->SetViewprojtexture(matProj,g_v4LightColor);
	for(INT i=0;i<ACTION_PATTERN_COUNT+1;i++){
		g_pMonDetail[i]->SetViewprojtexture(matProj,g_v4LightColor);
	}

}
inline HRESULT initLoad(){
	/*---------init character---------*/
	if(FAILED(g_pDrawXfile->InitballMesh(g_pd3dDevice,"FireBase.tga","Flame.tga","FireBall.fx","FireBall.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pMapBox->InitballMesh(g_pd3dDevice,"FieldstoneNoisy.tga","FieldstoneBumpDOT3.tga","Monster.fx","Monster.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pMonDetail[0]->InitballMesh(g_pd3dDevice,"Spotlight.jpg","noise.tga","MsiBall.fx","Monster.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pMonDetail[1]->InitballMesh(g_pd3dDevice,"Corona.tga","Corona.tga","HealBall.fx","Monster.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pMonDetail[2]->InitballMesh(g_pd3dDevice,"Hex.dds","FireBase.tga","DefBall.fx","Monster.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pMonDetail[3]->InitballMesh(g_pd3dDevice,"quad2.tga","base.tga","AttBall.fx","Monster.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pMonDetail[4]->InitballMesh(g_pd3dDevice,"N2d_000.tga","base.tga","LaserBall.fx","Monster.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pMonDetail[5]->InitballMesh(g_pd3dDevice,"Cube4.png","Fur.tga","WallBall.fx","Monster.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pMonDetail[6]->InitballMesh(g_pd3dDevice,"nhk_16.tga","FireBase.tga","ChangeBall.fx","Monster.x"))){
		return E_FAIL;
	}
	/*---------init billboard---------*/
	if(!SUCCEEDED(g_pUi->InitBillboard("normal_speed.png",&g_pSpeedBar[0]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(g_pUi->InitBillboard("red_speed.png",&g_pSpeedBar[1]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(g_pUi->InitBillboard("yellow_speed.png",&g_pSpeedBar[2]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(g_pUi->InitBillboard("hp.png",&g_pSpeedBar[3]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(g_pUi->InitBillboard("mp.png",&g_pSpeedBar[4]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(g_pUi->InitBillboard("def.png",&g_pSpeedBar[5]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(g_pUi->InitBillboard("black_rec.png",&g_pSpeedBar[6]))){
		return E_FAIL;
	}
	/*---------init monster.x---------*/
	if(!SUCCEEDED(g_pModel->LoadXFile("boxmodel.x"))){
		return E_FAIL;
	}
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
		case 'K':
			g_pModel->SetCurrentAnimation(g_pModel->GetCurrentAnimation()+1);
			break;
		case 'L':
			g_pModel->SetCurrentAnimation(g_pModel->GetCurrentAnimation()-1);
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