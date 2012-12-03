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
#include "Moving.h"
#include "Items.h"
#include "ItemsList.h"
#include "Ui.h"
#include "Struct.h"
#include "CModel.h"
#include "Macros.h"
#include "DirectInput.h"
#include "Monster.h"
#include "Monai.h"

HWND					g_hwnd = NULL;

ZCamera*				g_pCamera = NULL;
DWORD					g_cxHeight = 0;
DWORD					g_czHeight = 0;
DWORD					g_dwMouseX = 0;
DWORD					g_dwMouseY = 0;
//-----------------------------------------------------------------------------
// Drow Animation
//-----------------------------------------------------------------------------
CModel*					g_pModel		 = NULL; // A model object to work with
DirectInput*			g_pDI			 = NULL; // DirectInput instance
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
LPDIRECT3DTEXTURE9		speed_bar[10] = { NULL, NULL, NULL };// 빌보드로 사용할 텍스처
D3DXMATRIX				matBillboard;
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
D3DXVECTOR4             gLightColor(1.0f, 1.0f, 1.0f, 1.0f);//빛의 색
D3DXVECTOR3				zero(0.0f,0.0f,0.0f);

Ball*					myCharacter;

Moving*					mMoving;

D3DXMATRIXA16			myWorld;
D3DXMATRIXA16			myScale;
D3DXMATRIXA16			myTrans;
D3DXMATRIXA16			myRotate;
D3DXVECTOR3				mEye;

D3DXVECTOR4 Pos( START_POSITIONX, START_POSITIONY, START_POSITIONZ, 1.0f );
D3DXVECTOR4 Vel( START_VELOCITYX, START_VELOCITYY, START_VELOCITYZ, 0.0f );
D3DXVECTOR4 MonPos( START_MON_POSITIONX, START_MON_POSITIONY, START_MON_POSITIONZ, 1.0f );
D3DXVECTOR4 MonVel( START_VELOCITYX, START_VELOCITYY, START_VELOCITYZ, 0.0f );

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
// Monster
//-----------------------------------------------------------------------------
Monster* first_mon;
Monai* m_Ai;
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
inline void ProcessInputs( void )
{
	POINT	pt;
	GetCursorPos( &pt );
	int dx = pt.x - g_dwMouseX;	// 마우스의 변화값
	int dy = pt.y - g_dwMouseY;	// 마우스의 변화값

	Mouse_X += -dx*0.001;
	Mouse_Y += dy*0.05;


	if(cameraCase == 1){
	if( GetAsyncKeyState( 'W' )||GetAsyncKeyState( 'w' ) ) g_pCamera->MoveLocalZ( 0.5f );	// 카메라 전진!
	if( GetAsyncKeyState( 'S' )||GetAsyncKeyState( 's' ) ) g_pCamera->MoveLocalZ( -0.5f );	// 카메라 후진!
	if( GetAsyncKeyState( 'A' )||GetAsyncKeyState( 'a' ) ) g_pCamera->MoveLocalX( -0.5f );	// 카메라 후진!
	if( GetAsyncKeyState( 'D' )||GetAsyncKeyState( 'd' ) ) g_pCamera->MoveLocalX( 0.5f );	// 카메라 후진!
	if( GetAsyncKeyState( VK_ESCAPE ) ) PostMessage( g_hwnd, WM_DESTROY, 0, 0L );
	//if( GetAsyncKeyState( VK_LBUTTON ) ) g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	//if( GetAsyncKeyState( VK_RBUTTON ) ) g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	}
	else if(cameraCase == 2){
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

	if(speed_bar){
		for(int i=0;i<10;i++){
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
inline VOID setItemList(){
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

inline VOID itemListDraw(){
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

inline VOID DrawUi(){
	m_Ui->setUI(g_pd3dDevice);
	int velocity = abs((int)D3DXVec3Length(&myCharacter->getVelocity()));
	if(velocity>50){
		velocity = 50;
	}
	switch(velocity){
		case 50 : case 49 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[1],&matBillboard,-10.5f,120.0f,0.0f,vtx);
		case 48 : case 47 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[1],&matBillboard,-10.5f,115.0f,0.0f,vtx);
		case 46 : case 45 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[1],&matBillboard,-10.5f,110.0f,0.0f,vtx);
		case 44 : case 43 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[1],&matBillboard,-10.5f,105.0f,0.0f,vtx);
		case 42 : case 41 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[2],&matBillboard,-10.5f,100.0f,0.0f,vtx);
		case 40 : case 39 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[2],&matBillboard,-10.5f,95.0f,0.0f,vtx);
		case 38 : case 37 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[2],&matBillboard,-10.5f,90.0f,0.0f,vtx);
		case 36 : case 35 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[2],&matBillboard,-10.5f,85.0f,0.0f,vtx);
		case 34 : case 33 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[2],&matBillboard,-10.5f,80.0f,0.0f,vtx);
		case 32 : case 31 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[2],&matBillboard,-10.5f,75.0f,0.0f,vtx);
		case 30 : case 29 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[2],&matBillboard,-10.5f,70.0f,0.0f,vtx);
		case 28 : case 27 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[2],&matBillboard,-10.5f,65.0f,0.0f,vtx);
		case 26 : case 25 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,60.0f,0.0f,vtx);
		case 24 : case 23 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,55.0f,0.0f,vtx);
		case 22 : case 21 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,50.0f,0.0f,vtx);
		case 20 : case 19 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,45.0f,0.0f,vtx);
		case 18 : case 17 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,40.0f,0.0f,vtx);
		case 16 : case 15 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,35.0f,0.0f,vtx);
		case 14 : case 13 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,30.0f,0.0f,vtx);
		case 12 : case 11 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,25.0f,0.0f,vtx);
		case 10 : case 9 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,20.0f,0.0f,vtx);
		case 8 : case 7 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,15.0f,0.0f,vtx);
		case 6 : case 5 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,10.0f,0.0f,vtx);
		case 4 : case 3 : m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,5.0f,0.0f,vtx);
		case 2 : case 1: m_Ui->drawBillboard(g_pd3dDevice,speed_bar[0],&matBillboard,-10.5f,0.0f,0.0f,vtx);
		break;
	}
	m_Ui->drawBillboard(g_pd3dDevice,speed_bar[6],&matBillboard,-WINDOW_WIDTH+WINDOW_WIDTH/5,0,0,mapVtx);
	
	for(int i=0;i<myCharacter->hisLife()/10;i++){
		m_Ui->drawBillboard(g_pd3dDevice,speed_bar[3],&matBillboard,-WINDOW_WIDTH+WINDOW_WIDTH/20,12.0f*i,0.0f,hpVtx);
	}
	for(int i=0;i<myCharacter->hisMana()/10;i++){
		m_Ui->drawBillboard(g_pd3dDevice,speed_bar[4],&matBillboard,-WINDOW_WIDTH+WINDOW_WIDTH/20*2,12.0f*i,0.0f,hpVtx);
	}
	for(int i=0;i<myCharacter->hisDef()/10;i++){
		m_Ui->drawBillboard(g_pd3dDevice,speed_bar[5],&matBillboard,-WINDOW_WIDTH+WINDOW_WIDTH/20*3,12.0f*i,0.0f,hpVtx);
	}


}

inline VOID Render()
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
	SetupLight();
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{

		//-----------------------------------------------------------------------------
		// Camera Setting
		//-----------------------------------------------------------------------------

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

		//-----------------------------------------------------------------------------
		// View Setting
		//-----------------------------------------------------------------------------
		drawXfile->set_view(mView);
		mapBox->set_view(mView);

		//-----------------------------------------------------------------------------
		// Character Setting
		//-----------------------------------------------------------------------------
		mMoving->getPosition(myCharacter,GSpeed);	
		D3DXMatrixIdentity(&myWorld);
		D3DXMatrixScaling(&myScale,BALL_SIZE,BALL_SIZE,BALL_SIZE);
		D3DXMatrixTranslation(&myTrans,myCharacter->getPosition().x,myCharacter->getPosition().y,myCharacter->getPosition().z);
	//	D3DXMatrixRotationAxis(&myRotate,myCharacter->hisptVelocity(),timeGetTime() / 1000.0f);
		myWorld *= myScale;
	//	myWorld *= myRotate;
		myWorld *= myTrans;
		drawXfile->DrawMyballShader(myWorld);	

		//-----------------------------------------------------------------------------
		// Monster Setting
		//-----------------------------------------------------------------------------
		
		m_Ai->getPositionMon();
		D3DXMatrixIdentity(&mBox);
		D3DXMatrixScaling(&myScale,MON_SIZE,MON_SIZE,MON_SIZE);
		D3DXMatrixTranslation(&myTrans,first_mon->getPosition().x,first_mon->getPosition().y,first_mon->getPosition().z);
		mBox *= myScale;
		mBox *= myTrans;
		mapBox->DrawMyballShader(mBox);	

		//-----------------------------------------------------------------------------
		// Room Setting
		//-----------------------------------------------------------------------------
		D3DXMatrixIdentity(&mBox);
		D3DXMatrixScaling(&myScale,3.2f,0.15f,3.2f);
		D3DXMatrixTranslation(&myTrans,80.0f,-5.2f,80.0f);
		mBox *= myScale;
		mBox *= myTrans;
		mapBox->DrawMyballShader(mBox);
		
		setItemList();
		itemListDraw();
		mMoving->getItem(myCharacter,itemList,BALL_REAL_SIZE,ITEM_REAL_SIZE);

		DrawUi();
		g_pd3dDevice->EndScene();
	}
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

inline VOID afterInitD3D(){
	m_fStartTime = (float)timeGetTime() * 0.001f;
	srand((unsigned)GetTickCount());
	g_pCamera = new ZCamera;
	drawXfile = new Xfile();
	mapBox = new Xfile();
	myCharacter = new Ball(START_LIFE,START_MANA,0,CHARACTER_MAX_LEVEL,( D3DXVECTOR3 )Pos,( D3DXVECTOR3 )Vel,( D3DXVECTOR3 )Vel);	
	mMoving = new Moving(GRAVITY,REVERSE_GRAVITY,GROUND,MYSIZE,CEILING,THRESHOLD,BALLSPEED,GAMESPEED,ABSORBANCE,MINBOUNDX,MINBOUNDY,MINBOUNDZ,MAXBOUNDX,MAXBOUNDY,MAXBOUNDZ);
	itemList = new ItemsList();
	g_pModel = new CModel(g_pd3dDevice);
	first_mon = new Monster(MON_HEALTH,10,(D3DXVECTOR3)MonPos,(D3DXVECTOR3)MonVel,(D3DXVECTOR3)MonVel);
	m_Ai = new Monai(first_mon,myCharacter,MAXBOUNDX,MAXBOUNDZ,MINBOUNDX,MINBOUNDZ,GAMESPEED,MON_REAL_SIZE);
	m_Ui = new Ui(WINDOW_WIDTH,WINDOW_HEIGHT);
}

inline VOID afterRender(){
	delete g_pCamera;
	delete drawXfile;
	delete mapBox;
	delete myCharacter;
	delete mMoving;
	delete itemList;
	delete g_pModel;
	delete first_mon;
	delete m_Ai;
	delete m_Ui;
}

inline VOID beforeRender(){
	InitGeometry();
	drawXfile->set_viewprojtexture(matProj,gLightColor);
	mapBox->set_viewprojtexture(matProj,gLightColor);
	
}
inline HRESULT initLoad(){
	/*---------init character---------*/
	if(FAILED(drawXfile->InitballMesh(g_pd3dDevice,"FireBase.tga","Flame.tga","FireBall.fx","FireBall.x"))){
		return E_FAIL;
	}
	if(FAILED(mapBox->InitballMesh(g_pd3dDevice,"FieldstoneNoisy.tga","FieldstoneBumpDOT3.tga","Monster.fx","Monster.x"))){
		return E_FAIL;
	}

	/*---------init billboard---------*/
	if(!SUCCEEDED(m_Ui->initBillboard(g_pd3dDevice,"normal_speed.png",&speed_bar[0]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(m_Ui->initBillboard(g_pd3dDevice,"red_speed.png",&speed_bar[1]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(m_Ui->initBillboard(g_pd3dDevice,"yellow_speed.png",&speed_bar[2]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(m_Ui->initBillboard(g_pd3dDevice,"hp.png",&speed_bar[3]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(m_Ui->initBillboard(g_pd3dDevice,"mp.png",&speed_bar[4]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(m_Ui->initBillboard(g_pd3dDevice,"def.png",&speed_bar[5]))){
		return E_FAIL;
	}
	if(!SUCCEEDED(m_Ui->initBillboard(g_pd3dDevice,"black_rec.png",&speed_bar[6]))){
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
			if(myCharacter->spendMana(-10)){
			myCharacter->setGround(false);
			myCharacter->setVelocity(zero);
			myCharacter->setVelocity(myCharacter->getVelocity()+ mEye*2.5f*GAMESPEED);
			}
			break;
		case 'E':
			break;
		case 'Q':
			if(cameraCase == 2){
			myCharacter->setGround(false);
			myCharacter->setVelocityY(myCharacter->getVelocity().y+0.005f);
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
		myCharacter->setVelocity(myCharacter->getVelocity()+ mEye*1.5f*GAMESPEED);
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

	// Initialize Direct3D
	if( SUCCEEDED( InitD3D( hWnd ) ) )
	{
	afterInitD3D();
	//  g_pDI = DirectInput::GetInstance();
	//	g_pDI->InitDirectInput(hInst,hWnd);
	//	g_pDI->CreateKeyboardDevice(DISCL_BACKGROUND|DISCL_NONEXCLUSIVE);

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