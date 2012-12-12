#include "Moving.h"

Moving::Moving(Ball* myball,Monster* monster,Wall* wallset){
	cha = myball;
	mon = monster;
	wall = wallset;

	bCount = 0;
	bWallCount = 0;
	isCrash = false;

	maxboundx = MAXBOUNDX;
	maxboundy = MAXBOUNDY;
	maxboundz = MAXBOUNDZ;
	minboundx = MINBOUNDX;
	minboundy = MINBOUNDY;
	minboundz = MINBOUNDZ;

	monWall = false;
	monMaxWallX = false;
	monMaxWallY = false;
	monMaxWallZ = false;
	monMinWallX = false;
	monMinWallY = false;
	monMinWallZ = false;
	wall_bounce = 0;
	crashTime = 0;
	ActionStart = -1.0f;
}

void Moving::getItem(ItemsList* itList){
	Items* nowNode = itList->getStart()->getNext(); 
	if(nowNode!=itList->getEnd()){
		while(nowNode->getNext()!=itList->getEnd()){
			D3DXVECTOR3 vOneToTwo = cha->getPosition() - nowNode->getPosition();
			float DistSq = D3DXVec3LengthSq( &vOneToTwo );
			if( DistSq < (MYSIZE+ITEM_REAL_SIZE) * (MYSIZE+ITEM_REAL_SIZE) )
			{
				Items* deleteNode = nowNode;
				cha->setLife(nowNode->getHp());
				cha->setMana(nowNode->getMp());
				cha->setDefence(nowNode->getDef());
				nowNode = nowNode->getNext();
				itList->delNode(deleteNode);
			}else{
				nowNode = nowNode->getNext();
			}
		}
	}
}


void Moving::getPosition(float speed){
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

void Moving::getPositionWall(D3DXVECTOR3 pos,float speed){
	monWall = true;
	if(pos.x!=0){
		if(cha->getPosition().x>pos.x){
			monMinWallX = true;
			minboundx = pos.x;
		}
		else{
			monMaxWallX = true;
			maxboundx = pos.x;
		}
	}
	else if(pos.y!=0){
		if(cha->getPosition().y>pos.y){
			monMinWallY = true;
			minboundy = pos.y;
		}
		else{
			monMaxWallY = true;
			maxboundy = pos.y;
		}
	}
	else if(pos.z!=0){
		if(cha->getPosition().z>pos.z){
			monMinWallZ = true;
			minboundz = pos.z;
		}
		else{
			monMaxWallZ = true;
			maxboundz = pos.z;
		}
	}

	if( !wall->isGround() )
	{
		wall->setPosition(wall->getPosition()+wall->getVelocity()*BALLSPEED*speed);
		if(wall->getVelocity().y>0)
			wall->setVelocityY(wall->getVelocity().y-(GRAVITY+REVERSE_GRAVITY)*BALLSPEED*speed*15.0f);
		else
			wall->setVelocityY(wall->getVelocity().y-(GRAVITY*BALLSPEED*speed)*5.0f);

		if( wall->getPosition().y < -GROUND)
		{
			if(wall->getBcount()>7){
				wall->isGround(true);
			}else{
				wall->setPositionY(-GROUND );
				wall->setVelocityY(-wall->getVelocity().y* ( 1 - ABSORBANCE*20 )*speed);
				wall->setBcount();
			}

		}
	}
}
void Moving::returnWall(){
	monWall = false;
	if(monMaxWallX){
		monMaxWallX = false; 
		maxboundx = MAXBOUNDX;
	}else if(monMinWallX){
		monMinWallX = false; 
		minboundx = MINBOUNDX;
	}else if(monMaxWallY){
		monMaxWallY = false; 
		maxboundy = MAXBOUNDY;
	}else if(monMinWallY){
		monMinWallY = false; 
		minboundy = MINBOUNDY;
	}else if(monMaxWallZ){
		monMaxWallZ = false; 
		maxboundz = MAXBOUNDZ;
	}else if(monMinWallZ){
		monMinWallZ = false; 
		minboundz = MINBOUNDZ;
	}
	wall->resetPosVel();
}
void Moving::crashMon(float time){
	if((time - crashTime > 2.0f)&&(isCrash == true)){
		mon->setisGoal(false);
		mon->setOriginType(0);
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
void Moving::crashMissile(Missile* msi){
	if(msi->getType()!= 4){
		D3DXVECTOR3 vOneToTwo = cha->getPosition() - msi->getPosition();
		float DistSq = D3DXVec3LengthSq( &vOneToTwo );
		if( DistSq < (MON_REAL_SIZE+MYSIZE) * (MON_REAL_SIZE+MYSIZE) ){
			cha->setLife(msi->getDemage());
		}
	}
}