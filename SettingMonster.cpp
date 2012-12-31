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
}
HRESULT SettingMonster::SetXfile(){
	if(FAILED(g_pMissileModel->InitballMesh(g_pDevice,"FireBase.tga","Flame.tga","FireBall.fx","FireBall.x"))){
		return E_FAIL;
	}
	if(FAILED(g_pWallModel->InitballMesh(g_pDevice,"FieldstoneNoisy.tga","FieldstoneBumpDOT3.tga","Monster.fx","Monster.x"))){
		return E_FAIL;
	}
	if(!SUCCEEDED(g_pMonModel->LoadXFile("boxmodel.x"))){
		return E_FAIL;
	}
	return S_OK;
}
VOID SettingMonster::Draw(){
	if(g_pMonModel){
		g_pMonModel->Update(g_pMonAi->GetMotionTime());
		g_pMonModel->Draw();
	}
}
VOID SettingMonster::DrawWall(){
	if(g_pMove->GetMonWall())
	{
		if(!g_bWall){
			if(g_pMove->GetMonMaxWallX()){
				g_pWallModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(0.001f,3.2f,3.2f),D3DXVECTOR3(g_pMove->GetMaxX(),g_pWall->GetPositionY()+MAXBOUNDY/2,MAXBOUNDZ/2)));
			}
			else if(g_pMove->GetMonMinWallX()){
				g_pWallModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(0.001f,3.2f,3.2f),D3DXVECTOR3(g_pMove->GetMinX(),g_pWall->GetPositionY()+MAXBOUNDY/2,MAXBOUNDZ/2)));			
			}
			else if(g_pMove->GetMonMaxWallZ()){
				g_pWallModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(3.2f,3.2f,0.001f),D3DXVECTOR3(MAXBOUNDX/2,g_pWall->GetPositionY()+MAXBOUNDY/2,g_pMove->GetMaxZ())));
			}
			else if(g_pMove->GetMonMinWallZ()){
				g_pWallModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(3.2f,3.2f,0.001f),D3DXVECTOR3(MAXBOUNDX/2,g_pWall->GetPositionY()+MAXBOUNDY/2,g_pMove->GetMinZ())));
			}
			g_bWall = TRUE;
		}else{
			g_bWall = FALSE;
		}
	}
}
VOID SettingMonster::CrashMissile(){
	if(g_pMonAi->GetMsionall()){
		for(INT i=0;i<MISSILE_COUNT;i++){
			g_pMissileModel->DrawMyballShader(DrawPosition(D3DXVECTOR3(MISSILE_SIZE,MISSILE_SIZE,MISSILE_SIZE),g_pMissile[i]->GetPosition()));
			if(g_pMissile[i]->GetType()!= 4){
				D3DXVECTOR3 vOneToTwo = g_pCha->GetPosition() - g_pMissile[i]->GetPosition();
				float DistSq = D3DXVec3LengthSq( &vOneToTwo );
				if( DistSq < (MON_REAL_SIZE+MYSIZE) * (MON_REAL_SIZE+MYSIZE) ){
					g_pCha->SetLife(g_pMissile[i]->GetDemage());
				}
			}
		}
	}	
}
VOID SettingMonster::SetViewMatrix(D3DXMATRIX view){
	g_pMissileModel->SetView(view);
	g_pWallModel->SetView(view);
};
VOID SettingMonster::SetProjectionMatrix(D3DXMATRIX proj,D3DXVECTOR4 light){
	g_pMissileModel->SetViewprojtexture(proj,light);
	g_pWallModel->SetViewprojtexture(proj,light);
};
VOID SettingMonster::CrashMon(FLOAT time){
	if((time - fCrashTime > 2.0f)&&(bCrash == true)){
		g_pMonster->SetisGoal(false);
		g_pMonster->SetOriginType(0);
		bCrash = false;
	}
	if(g_pMonster->IsAlive()==true)//is alive?
	{
		D3DXVECTOR3 pMonRealPosition = g_pMonster->GetPosition();
		pMonRealPosition.y += MON_REAL_SIZE/2;
		D3DXVECTOR3 vOneToTwo = g_pCha->GetPosition() - pMonRealPosition;
		float DistSq = D3DXVec3LengthSq( &vOneToTwo );

		if( DistSq < (MON_REAL_SIZE+MYSIZE) * (MON_REAL_SIZE+MYSIZE) )
		{
			D3DXVec3Normalize( &vOneToTwo, &vOneToTwo );
			float fImpact = D3DXVec3Dot( &vOneToTwo, &g_pMonster->GetVelocity() ) - D3DXVec3Dot( &vOneToTwo, &g_pCha->GetVelocity());	

			if( fImpact > 0.0f )
			{
				bCrash = true;

				fCrashTime = time;

				D3DXVECTOR3 vVelocityOneN = ( 1 - BOUNCE_LOST ) * D3DXVec3Dot( &vOneToTwo, &g_pMonster->GetVelocity() ) * vOneToTwo;
				D3DXVECTOR3 vVelocityOneT = ( 1 - BOUNCE_LOST ) * g_pMonster->GetVelocity() - vVelocityOneN;

				D3DXVECTOR3 vVelocityTwoN = ( 1 - BOUNCE_LOST ) * D3DXVec3Dot( &vOneToTwo, &g_pCha->GetVelocity()) * vOneToTwo;
				D3DXVECTOR3 vVelocityTwoT = ( 1 - BOUNCE_LOST ) * g_pCha->GetVelocity() - vVelocityTwoN;

				g_pMonster->SetVelocity(vVelocityOneT - vVelocityOneN * ( 1 - BOUNCE_TRANSFER ) + vVelocityTwoN * BOUNCE_TRANSFER);
				g_pCha->SetVelocity(vVelocityTwoT - vVelocityTwoN * ( 1 - BOUNCE_TRANSFER ) + vVelocityOneN * BOUNCE_TRANSFER);

				float fDistanceToMove = ( MON_REAL_SIZE - sqrtf( DistSq ) ) * 0.5f;
				g_pMonster->SetPosition(g_pMonster->GetPosition()-vOneToTwo * fDistanceToMove);
				g_pCha->SetPosition(g_pCha->GetPosition()+vOneToTwo * fDistanceToMove);	
				
				g_pMonster->SetLife(-abs((int)D3DXVec3Length(&g_pCha->GetVelocity())));
			}
		}
	}
}
