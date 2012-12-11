#include "Moving.h"

Moving::Moving(){
	bCount = 0;
	isCrash = false;

	maxboundx = MAXBOUNDX;
	maxboundy = MAXBOUNDY;
	maxboundz = MAXBOUNDZ;
	minboundx = MINBOUNDX;
	minboundy = MINBOUNDY;
	minboundz = MINBOUNDZ;

	monWall = false;
	wall_bounce = 0;
	crashTime = 0;
	ActionStart = -1.0f;
}

void Moving::getItem(Ball* cha,ItemsList* itList){

	Items* nowNode = itList->getStart(); 

	while(nowNode->getNext()!=itList->getEnd()){
		nowNode=nowNode->getNext();

		D3DXVECTOR3 vOneToTwo = cha->getPosition() - nowNode->getPosition();
		float DistSq = D3DXVec3LengthSq( &vOneToTwo );
		if( DistSq < (MYSIZE+ITEM_REAL_SIZE) * (MYSIZE+ITEM_REAL_SIZE) )
		{
			D3DXVec3Normalize( &vOneToTwo, &vOneToTwo );

			float fImpact = D3DXVec3Dot( &vOneToTwo, &nowNode->getVelocity() ) - D3DXVec3Dot( &vOneToTwo, &cha->getVelocity() );	
			if( fImpact > 0.0f )
			{
				cha->setLife(nowNode->getHp());
				cha->setMana(nowNode->getMp());
				cha->setDefence(nowNode->getDef());
				itList->delNode(nowNode->getNumber());
			}
		}
	}
}


void Moving::getPosition(Ball* cha,float speed){
	if( (GRAVITY+REVERSE_GRAVITY) * ( (cha->getPosition().y + GROUND - ( MYSIZE * 1.0f ) ) + 0.5f *
		cha->getVelocity().y * cha->getVelocity().y< THRESHOLD) && cha->isGround()== false)
	{
		bCount++;
	}

	if( (GRAVITY+REVERSE_GRAVITY) * ( (cha->getPosition().y + GROUND - ( MYSIZE * 1.0f ) ) + 0.5f *
		cha->getVelocity().y * cha->getVelocity().y
		< THRESHOLD) && bCount>5)
	{
		cha->setPositionY(-GROUND +  MYSIZE * 0.5f );
		cha->setVelocityY(0.0f);
		cha->setGround(true);
		bCount=0;
	}

	if( !cha->isGround() )
	{
		cha->setPosition(cha->getPosition()+cha->getVelocity()*BALLSPEED*speed);
		if(cha->getVelocity().y>0)
			cha->setVelocityY(cha->getVelocity().y-(GRAVITY+REVERSE_GRAVITY)*BALLSPEED*speed);
		else
			cha->setVelocityY(cha->getVelocity().y-(GRAVITY*BALLSPEED*speed));

		if( cha->getPosition().y < -GROUND + ( MYSIZE * 0.5f ) )
		{
			cha->setPositionY(-GROUND + ( MYSIZE * 0.5f ));
			cha->setVelocityY(-cha->getVelocity().y* ( 1 - ABSORBANCE )*speed);
			cha->setVelocityX(cha->getVelocity().x*0.5f*speed);
			cha->setVelocityZ(cha->getVelocity().z*0.5f*speed);
		}
	}
	else
	{
		cha->setVelocityX(cha->getVelocity().x*0.5f*speed);
		cha->setVelocityZ(cha->getVelocity().z*0.5f*speed);
	}


	if( cha->getPosition().y > CEILING - ( MYSIZE * 0.5f ) )
	{
		cha->setPositionY(CEILING - ( MYSIZE * 0.5f ));
		cha->setVelocityY(-cha->getVelocity().y * ( 1 - ABSORBANCE )*speed);
		cha->setVelocityX(cha->getVelocity().x*0.5f*speed);
		cha->setVelocityZ(cha->getVelocity().z*0.5f*speed);
	}
	if( cha->getPosition().z < minboundz + ( MYSIZE * 0.5f ) )
	{
		cha->setPositionZ(minboundz + ( MYSIZE * 0.5f ));
		cha->setVelocityZ(-(cha->getVelocity().z) * ( 1 - ABSORBANCE )*speed);
	}
	if( cha->getPosition().x < minboundx + ( MYSIZE * 0.5f ) )
	{
		cha->setPositionX(minboundx + ( MYSIZE * 0.5f ));
		cha->setVelocityX(-(cha->getVelocity().x) * ( 1 - ABSORBANCE )*speed);
	}
	if( cha->getPosition().z > maxboundz - ( MYSIZE * 0.5f ) )
	{
		cha->setPositionZ(maxboundz - ( MYSIZE * 0.5f ));
		cha->setVelocityZ(-(cha->getVelocity().z) * ( 1 - ABSORBANCE )*speed);
	}
	if( cha->getPosition().x > maxboundx - ( MYSIZE * 0.5f ) )
	{
		cha->setPositionX(maxboundx - ( MYSIZE * 0.5f ));
		cha->setVelocityX(-(cha->getVelocity().x) * ( 1 - ABSORBANCE )*speed);
	}

}

void Moving::getPositionWall(Ball* cha,D3DXVECTOR3 wall){
	if(wall.x!=0){
		monWall = true;
		if(cha->getPosition().x>wall.x)
			minboundx = wall.x;
		else
			maxboundx = wall.x;
	}
	else if(wall.y!=0){
		monWall = true;
		if(cha->getPosition().y>wall.y)
			minboundy = wall.y;
		else
			maxboundy = wall.y;
	}
	else if(wall.z!=0){
		monWall = true;
		if(cha->getPosition().z>wall.z)
			minboundz = wall.z;
		else
			maxboundz = wall.z;
	}
}
void Moving::crashMon(Ball* cha, Monster* mon,float time){
	if((time - crashTime > 2.0f)&&(isCrash == true)){
		mon->setisGoal(false);
		isCrash = false;
	}
	if(mon->isAlive()==true)//is alive?
	{
		D3DXVECTOR3 vOneToTwo = cha->getPosition() - mon->getPosition();
		float DistSq = D3DXVec3LengthSq( &vOneToTwo );

		if( DistSq < (MON_REAL_SIZE+MYSIZE) * (MON_REAL_SIZE+MYSIZE) )
		{
			D3DXVec3Normalize( &vOneToTwo, &vOneToTwo );
			float fImpact = D3DXVec3Dot( &vOneToTwo, &mon->getVelocity() ) - D3DXVec3Dot( &vOneToTwo, &cha->getVelocity());	

			if( fImpact > 0.0f )
			{
				isCrash = true;
				crashTime = time;

				D3DXVECTOR3 vVelocityOneN = ( 1 - BOUNCE_LOST ) * D3DXVec3Dot( &vOneToTwo, &mon->getVelocity() ) * vOneToTwo;
				D3DXVECTOR3 vVelocityOneT = ( 1 - BOUNCE_LOST ) * mon->getVelocity() - vVelocityOneN;

				D3DXVECTOR3 vVelocityTwoN = ( 1 - BOUNCE_LOST ) * D3DXVec3Dot( &vOneToTwo, &cha->getVelocity()) * vOneToTwo;
				D3DXVECTOR3 vVelocityTwoT = ( 1 - BOUNCE_LOST ) * cha->getVelocity() - vVelocityTwoN;

				mon->setVelocity(vVelocityOneT - vVelocityOneN * ( 1 - BOUNCE_TRANSFER ) + vVelocityTwoN * BOUNCE_TRANSFER);
				cha->setVelocity(vVelocityTwoT - vVelocityTwoN * ( 1 - BOUNCE_TRANSFER ) + vVelocityOneN * BOUNCE_TRANSFER);

				float fDistanceToMove = ( MON_REAL_SIZE - sqrtf( DistSq ) ) * 0.5f;
				mon->setPostion(mon->getPosition()-vOneToTwo * fDistanceToMove);
				cha->setPosition(cha->getPosition()+vOneToTwo * fDistanceToMove);
				if(D3DXVec3LengthSq(&cha->getVelocity())>5.0f)
				{
				}
			}
		}
	}
}
void Moving::crashMissile(Ball* cha,Missile* msi){
	if(msi->getType()!= 4){
		D3DXVECTOR3 vOneToTwo = cha->getPosition() - msi->getPosition();
		float DistSq = D3DXVec3LengthSq( &vOneToTwo );
		if( DistSq < (MON_REAL_SIZE+MYSIZE) * (MON_REAL_SIZE+MYSIZE) ){
			cha->setLife(msi->getDemage());
		}
	}
}