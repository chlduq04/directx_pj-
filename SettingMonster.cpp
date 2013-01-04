#include "SettingMonster.h"
SettingMonster::SettingMonster(LPDIRECT3DDEVICE9 device,Ball* cha, Moving* move,FLOAT time){
	D3DXVECTOR4 m_v4MonPos( START_MON_POSITIONX, START_MON_POSITIONY, START_MON_POSITIONZ, 1.0f );
	D3DXVECTOR4 m_v4MonVel( START_VELOCITYX, START_VELOCITYY, START_VELOCITYZ, 0.0f );
	g_pDevice = device;
	g_pCha = cha;
	g_pMove = move;
	g_pWall = new Wall();
	g_pMissileModel = new Xfile();
	g_pWallModel = new Xfile();
	g_pMonster = new Monster((D3DXVECTOR3)m_v4MonPos,(D3DXVECTOR3)m_v4MonVel,(D3DXVECTOR3)m_v4MonVel);
	g_pMonModel = new CModel(g_pDevice);
	g_pCheck = new Checkai();
	for(INT i=0;i<MISSILE_COUNT;i++){
		g_pMissile[i] = new Missile();
	}

	g_pMonAi = new Monai(g_pMonster,g_pCha,g_pMissile,g_pMove,g_pWall,g_pCheck,g_pMonModel,time);
	fCrashTime = 0;
	bCrash = FALSE;
	g_bWall = FALSE;
	g_matInit = D3DXVECTOR3(0.0f,0.0f,0.0f);
	SetBefore = FALSE;
	bWireFrame = TRUE;
	LaserDamage = 0.2f;
}
SettingMonster::~SettingMonster(){
	delete g_pMonModel;
	delete g_pCheck;
	delete g_pMissileModel;
	delete g_pWallModel;
	delete g_pMonster;
	delete g_pWall;
	g_pDevice = NULL;
	g_pCha = NULL;
	g_pMove  = NULL;
	for(INT i=0;i<MISSILE_COUNT;i++){
		delete g_pMissile[i] ;
	}
	delete g_pMonAi;
}
HRESULT SettingMonster::SetXfile(){
	if(FAILED(g_pMissileModel->InitballMesh(g_pDevice,"FireBase.tga","Flame.tga","FireBall.fx","FireBall.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pWallModel->InitballMesh(g_pDevice,"FieldstoneNoisy.tga","FieldstoneBumpDOT3.tga","Monster.fx","Monster.x"))){
		return E_FAIL;
	}
	if(!SUCCEEDED(g_pMonModel->LoadXFile("box.x"))){
		return E_FAIL;
	}
	return S_OK;
}
VOID SettingMonster::Draw(LPD3DXMATRIX monworld,LPD3DXMATRIX originview,ZCamera* camera,FLOAT time,FLOAT speed,INT cameracase){
	MonsterPosition(speed);
	GetPositionMon(time);
	D3DXVec3Normalize(&g_matAngle,&D3DXVECTOR3( g_pMonster->GetVelocity().x,0,g_pMonster->GetVelocity().z));
	if(g_pMonster->GetVelocity().x>0){
		DrawPosition(monworld,D3DXVECTOR3(MON_SIZE,MON_SIZE,MON_SIZE), -acos(D3DXVec3Dot(&g_matAngle,&D3DXVECTOR3( 0,0,-1.0))) + 2*D3DX_PI,g_pMonster->GetPosition());
	}else{
		DrawPosition(monworld,D3DXVECTOR3(MON_SIZE,MON_SIZE,MON_SIZE), acos(D3DXVec3Dot(&g_matAngle,&D3DXVECTOR3( 0,0,-1.0))) ,g_pMonster->GetPosition());
	}

	if(cameracase == 1){
		g_pDevice->SetTransform( D3DTS_WORLD, monworld );
		g_pDevice->SetTransform( D3DTS_VIEW, camera->GetViewMatrix() );			// 카메라 행렬 셋팅
	}
	else if(cameracase == 2){
		g_pDevice->SetTransform( D3DTS_WORLD, monworld );
		g_pDevice->SetTransform( D3DTS_VIEW, originview);			// 카메라 행렬 셋팅
	}
	CrashMon(time);

	if(g_pMonModel){
		g_pMonModel->Update(g_pMonAi->GetMotionTime());
		g_pMonModel->Draw();
	}
	//RenderLine();
	//-----------------------------------------------------------------------------
	// Wall Setting
	//-----------------------------------------------------------------------------
	DrawWall();
	//-----------------------------------------------------------------------------
	// Missile Setting
	//-----------------------------------------------------------------------------
	CrashMissile();
	D3DXMatrixIdentity(monworld);
}


VOID SettingMonster::SetViewMatrix(D3DXMATRIX view){
	g_pMissileModel->SetView(view);
	g_pWallModel->SetView(view);
};
VOID SettingMonster::SetProjectionMatrix(D3DXMATRIX proj,D3DXVECTOR4 light){
	g_pMissileModel->SetViewprojtexture(proj,light);
	g_pWallModel->SetViewprojtexture(proj,light);
};