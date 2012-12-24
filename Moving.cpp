#include "Moving.h"

Moving::Moving(Ball* myball,Monster* pMonster,Wall* pWallSet){
	pCha = myball;
	pMon = pMonster;
	pWall = pWallSet;

	nCount = 0;
	nWallCount = 0;
	bCrash = false;

	fMaxboundx = MAXBOUNDX;
	fMaxboundy = MAXBOUNDY;
	fMaxboundz = MAXBOUNDZ;
	fMinboundx = MINBOUNDX;
	fMinboundy = MINBOUNDY;
	fMinboundz = MINBOUNDZ;

	bMonWall = false;
	bMonMaxWallX = false;
	bMonMaxWallY = false;
	bMonMaxWallZ = false;
	bMonMinWallX = false;
	bMonMinWallY = false;
	bMonMinWallZ = false;
	fWallBounce = 0;
	fCrashTime = 0;
	fActionStart = -1.0f;
}

void Moving::GetItem(ItemsList* itList){
	Items* nowNode = itList->GetStart()->GetNext(); 
	if(nowNode!=itList->GetEnd()){
		while(nowNode->GetNext()!=itList->GetEnd()){
			D3DXVECTOR3 vOneToTwo = pCha->GetPosition() - nowNode->GetPosition();
			float DistSq = D3DXVec3LengthSq( &vOneToTwo );
			if( DistSq < (MYSIZE+ITEM_REAL_SIZE) * (MYSIZE+ITEM_REAL_SIZE) )
			{
				Items* deleteNode = nowNode;
				pCha->SetLife(nowNode->GetHp());
				pCha->SetMana(nowNode->GetMp());
				pCha->SetDefence(nowNode->GetDef());
				nowNode = nowNode->GetNext();
				itList->DelNode(deleteNode);
			}else{
				nowNode = nowNode->GetNext();
			}
		}
	}
}

void Moving::GetPosition(float speed){
	if( (GRAVITY+REVERSE_GRAVITY) * ( (pCha->GetPosition().y + GROUND - ( MYSIZE * 1.0f ) ) + 0.5f *
		pCha->GetVelocity().y * pCha->GetVelocity().y< THRESHOLD) && pCha->IsGround()== false)
	{
		nCount++;
	}

	if( (GRAVITY+REVERSE_GRAVITY) * ( (pCha->GetPosition().y + GROUND - ( MYSIZE * 1.0f ) ) + 0.5f *
		pCha->GetVelocity().y * pCha->GetVelocity().y
		< THRESHOLD) && nCount>5)
	{
		pCha->SetPositionY(-GROUND +  MYSIZE * 0.5f );
		pCha->SetVelocityY(0.0f);
		pCha->SetGround(true);
		nCount=0;
	}

	if(	!pMon->IsbGround()){
		pMon->SetPosition(pMon->GetPosition()+pMon->GetVelocity()*speed);
		if(pMon->GetVelocity().y>0)
			pMon->SetVelocityY(pMon->GetVelocity().y-(GRAVITY+REVERSE_GRAVITY)*BALLSPEED*speed);
		else
			pMon->SetVelocityY(pMon->GetVelocity().y-(GRAVITY*BALLSPEED*speed/10));

		if( pMon->GetPosition().y < -GROUND + ( MON_SIZE* 0.5f ) )
		{
			pMon->SetPositionY(-GROUND + ( MON_SIZE * 0.5f ));
			pMon->SetVelocityY(-pMon->GetVelocity().y* ( 1 - ABSORBANCE )*speed);
		}
	}
	if(pMon->GetPosition().x>MAXBOUNDX){
		pMon->SetPositionX(MAXBOUNDX);
	}
	if(pMon->GetPosition().x<MINBOUNDX){
		pMon->SetPositionX(MINBOUNDX);
	}
	if(pMon->GetPosition().z>MAXBOUNDZ){
		pMon->SetPositionZ(MAXBOUNDZ);
	}
	if(pMon->GetPosition().z<MINBOUNDZ){
		pMon->SetPositionZ(MINBOUNDZ);
	}
	if(pMon->GetPosition().y>MAXBOUNDY){
		pMon->SetPositionY(MAXBOUNDY);
	}
	if(pMon->GetPosition().y<MINBOUNDY){
		pMon->SetPositionY(MINBOUNDY);
	}
	


	if( !pCha->IsGround() )
	{
		pCha->SetPosition(pCha->GetPosition()+pCha->GetVelocity()*BALLSPEED*speed);
		if(pCha->GetVelocity().y>0)
			pCha->SetVelocityY(pCha->GetVelocity().y-(GRAVITY+REVERSE_GRAVITY)*BALLSPEED*speed);
		else
			pCha->SetVelocityY(pCha->GetVelocity().y-(GRAVITY*BALLSPEED*speed));

		if( pCha->GetPosition().y < -GROUND + ( MYSIZE * 0.5f ) )
		{
			pCha->SetPositionY(-GROUND + ( MYSIZE * 0.5f ));
			pCha->SetVelocityY(-pCha->GetVelocity().y* ( 1 - ABSORBANCE )*speed);
			pCha->SetVelocityX(pCha->GetVelocity().x*0.5f*speed);
			pCha->SetVelocityZ(pCha->GetVelocity().z*0.5f*speed);
		}
	}
	else
	{
		pCha->SetVelocityX(pCha->GetVelocity().x*0.5f*speed);
		pCha->SetVelocityZ(pCha->GetVelocity().z*0.5f*speed);
	}


	if( pCha->GetPosition().y > CEILING - ( MYSIZE * 0.5f ) )
	{
		pCha->SetPositionY(CEILING - ( MYSIZE * 0.5f ));
		pCha->SetVelocityY(-pCha->GetVelocity().y * ( 1 - ABSORBANCE )*speed);
		pCha->SetVelocityX(pCha->GetVelocity().x*0.5f*speed);
		pCha->SetVelocityZ(pCha->GetVelocity().z*0.5f*speed);
	}
	if( pCha->GetPosition().z < fMinboundz + ( MYSIZE * 0.5f ) )
	{
		pCha->SetPositionZ(fMinboundz + ( MYSIZE * 0.5f ));
		pCha->SetVelocityZ(-(pCha->GetVelocity().z) * ( 1 - ABSORBANCE )*speed);
	}
	if( pCha->GetPosition().x < fMinboundx + ( MYSIZE * 0.5f ) )
	{
		pCha->SetPositionX(fMinboundx + ( MYSIZE * 0.5f ));
		pCha->SetVelocityX(-(pCha->GetVelocity().x) * ( 1 - ABSORBANCE )*speed);
	}
	if( pCha->GetPosition().z > fMaxboundz - ( MYSIZE * 0.5f ) )
	{
		pCha->SetPositionZ(fMaxboundz - ( MYSIZE * 0.5f ));
		pCha->SetVelocityZ(-(pCha->GetVelocity().z) * ( 1 - ABSORBANCE )*speed);
	}
	if( pCha->GetPosition().x > fMaxboundx - ( MYSIZE * 0.5f ) )
	{
		pCha->SetPositionX(fMaxboundx - ( MYSIZE * 0.5f ));
		pCha->SetVelocityX(-(pCha->GetVelocity().x) * ( 1 - ABSORBANCE )*speed);
	}

}

void Moving::GetPositionWall(D3DXVECTOR3 pos,float speed){
	bMonWall = true;
	if(pos.x!=0){
		if(pCha->GetPosition().x>pos.x){
			bMonMinWallX = true;
			fMinboundx = pos.x;
		}
		else{
			bMonMaxWallX = true;
			fMaxboundx = pos.x;
		}
	}
	else if(pos.y!=0){
		if(pCha->GetPosition().y>pos.y){
			bMonMinWallY = true;
			fMinboundy = pos.y;
		}
		else{
			bMonMaxWallY = true;
			fMaxboundy = pos.y;
		}
	}
	else if(pos.z!=0){
		if(pCha->GetPosition().z>pos.z){
			bMonMinWallZ = true;
			fMinboundz = pos.z;
		}
		else{
			bMonMaxWallZ = true;
			fMaxboundz = pos.z;
		}
	}

	if( !pWall->IsGround() )
	{
		pWall->SetPosition(pWall->GetPosition()+pWall->GetVelocity()*BALLSPEED*speed);
		if(pWall->GetVelocity().y>0)
			pWall->SetVelocityY(pWall->GetVelocity().y-(GRAVITY+REVERSE_GRAVITY)*BALLSPEED*speed*15.0f);
		else
			pWall->SetVelocityY(pWall->GetVelocity().y-(GRAVITY*BALLSPEED*speed)*5.0f);

		if( pWall->GetPosition().y < -GROUND)
		{
			if(pWall->GetBcount()>7){
				pWall->IsGround(true);
			}else{
				pWall->SetPositionY(-GROUND );
				pWall->SetVelocityY(-pWall->GetVelocity().y* ( 1 - ABSORBANCE*20 )*speed);
				pWall->SetBcount();
			}

		}
	}
}
void Moving::ReturnWall(){
	bMonWall = false;
	if(bMonMaxWallX){
		bMonMaxWallX = false; 
		fMaxboundx = MAXBOUNDX;
	}else if(bMonMinWallX){
		bMonMinWallX = false; 
		fMinboundx = MINBOUNDX;
	}else if(bMonMaxWallY){
		bMonMaxWallY = false; 
		fMaxboundy = MAXBOUNDY;
	}else if(bMonMinWallY){
		bMonMinWallY = false; 
		fMinboundy = MINBOUNDY;
	}else if(bMonMaxWallZ){
		bMonMaxWallZ = false; 
		fMaxboundz = MAXBOUNDZ;
	}else if(bMonMinWallZ){
		bMonMinWallZ = false; 
		fMinboundz = MINBOUNDZ;
	}
	pWall->ResetPosVel();
}
void Moving::CrashMon(float time){
	if((time - fCrashTime > 2.0f)&&(bCrash == true)){
		pMon->SetisGoal(false);
		pMon->SetOriginType(0);
		bCrash = false;
	}
	if(pMon->IsAlive()==true)//is alive?
	{
		D3DXVECTOR3 pMonRealPosition = pMon->GetPosition();
		pMonRealPosition.y += MON_REAL_SIZE/2;
		D3DXVECTOR3 vOneToTwo = pCha->GetPosition() - pMonRealPosition;
		float DistSq = D3DXVec3LengthSq( &vOneToTwo );

		if( DistSq < (MON_REAL_SIZE+MYSIZE) * (MON_REAL_SIZE+MYSIZE) )
		{
			D3DXVec3Normalize( &vOneToTwo, &vOneToTwo );
			float fImpact = D3DXVec3Dot( &vOneToTwo, &pMon->GetVelocity() ) - D3DXVec3Dot( &vOneToTwo, &pCha->GetVelocity());	

			if( fImpact > 0.0f )
			{
				bCrash = true;

				fCrashTime = time;

				D3DXVECTOR3 vVelocityOneN = ( 1 - BOUNCE_LOST ) * D3DXVec3Dot( &vOneToTwo, &pMon->GetVelocity() ) * vOneToTwo;
				D3DXVECTOR3 vVelocityOneT = ( 1 - BOUNCE_LOST ) * pMon->GetVelocity() - vVelocityOneN;

				D3DXVECTOR3 vVelocityTwoN = ( 1 - BOUNCE_LOST ) * D3DXVec3Dot( &vOneToTwo, &pCha->GetVelocity()) * vOneToTwo;
				D3DXVECTOR3 vVelocityTwoT = ( 1 - BOUNCE_LOST ) * pCha->GetVelocity() - vVelocityTwoN;

				pMon->SetVelocity(vVelocityOneT - vVelocityOneN * ( 1 - BOUNCE_TRANSFER ) + vVelocityTwoN * BOUNCE_TRANSFER);
				pCha->SetVelocity(vVelocityTwoT - vVelocityTwoN * ( 1 - BOUNCE_TRANSFER ) + vVelocityOneN * BOUNCE_TRANSFER);

				float fDistanceToMove = ( MON_REAL_SIZE - sqrtf( DistSq ) ) * 0.5f;
				pMon->SetPosition(pMon->GetPosition()-vOneToTwo * fDistanceToMove);
				pCha->SetPosition(pCha->GetPosition()+vOneToTwo * fDistanceToMove);	
				
				pMon->SetLife(-abs((int)D3DXVec3Length(&pCha->GetVelocity())));
			}
		}
	}
}
void Moving::CrashMissile(Missile* msi){
	if(msi->GetType()!= 4){
		D3DXVECTOR3 vOneToTwo = pCha->GetPosition() - msi->GetPosition();
		float DistSq = D3DXVec3LengthSq( &vOneToTwo );
		if( DistSq < (MON_REAL_SIZE+MYSIZE) * (MON_REAL_SIZE+MYSIZE) ){
			pCha->SetLife(msi->GetDemage());
		}
	}
}