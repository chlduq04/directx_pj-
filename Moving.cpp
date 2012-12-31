#include "Moving.h"

Moving::Moving(Ball* myball){
	pCha = myball;
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
Moving::~Moving(){
	pCha = NULL;
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
}
