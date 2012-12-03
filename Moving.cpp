#include "Moving.h"

Moving::Moving(float gravity,float reversegravity,float ground,float mysize,float ceiling,float threshold,float ballspeed,float gamespeed,float absorbance,float minboundx,float minboundy,float minboundz,float maxboundx,float maxboundy,float maxboundz){
	bCount = 0;
	vGravity = gravity;
	rGravity = reversegravity;
	yGround = ground;
	mySize = mysize;
	rCeiling = ceiling;
	rThreshold = threshold;
	bSpeed = ballspeed;//공 속도
	gSpeed = gamespeed;//게임속도
	gAbsorbance = absorbance;
	minBoundx = minboundx;
	minBoundy = minboundy;
	minBoundz = minboundz;
	maxBoundx = maxboundx;
	maxBoundy = maxboundy;
	maxBoundz = maxboundz;

	wallxr = false;
	wallyr = false;
	wallzr = false;
	wallxl = false;
	wallyl = false;
	wallzl = false;
	wall_position = 0.0f;
	wall_bounce = 0;

	ActionStart = -1.0f;
}

void Moving::getItem(Ball* cha,ItemsList* itList,int mySize,int itemSize){

	Items* nowNode = itList->getStart(); 

	while(nowNode->getNext()!=itList->getEnd()){
		nowNode=nowNode->getNext();

		D3DXVECTOR3 vOneToTwo = cha->getPosition() - nowNode->getPosition();
		float DistSq = D3DXVec3LengthSq( &vOneToTwo );
		if( DistSq < (mySize+itemSize) * (mySize+itemSize) )
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

	if( (vGravity+rGravity) * ( (cha->getPosition().y + yGround - ( mySize * 1.0f ) ) + 0.5f *
		cha->getVelocity().y * cha->getVelocity().y< rThreshold) && cha->isGround()== false)
	{
		bCount++;
	}

	if( (vGravity+rGravity) * ( (cha->getPosition().y + yGround - ( mySize * 1.0f ) ) + 0.5f *
		cha->getVelocity().y * cha->getVelocity().y
		< rThreshold) && bCount>5)
	{
		cha->setPositionY(-yGround +  mySize * 0.5f );
		cha->setVelocityY(0.0f);
		cha->setGround(true);
		bCount=0;
	}

	if( !cha->isGround() )
	{
		cha->setPosition(cha->getPosition()+cha->getVelocity()*bSpeed*speed);
		if(cha->getVelocity().y>0)
			cha->setVelocityY(cha->getVelocity().y-(vGravity+rGravity)*bSpeed*speed);
		else
			cha->setVelocityY(cha->getVelocity().y-(vGravity*bSpeed*speed));

		if( cha->getPosition().y < -yGround + ( mySize * 0.5f ) )
		{
			cha->setPositionY(-yGround + ( mySize * 0.5f ));
			cha->setVelocityY(-cha->getVelocity().y* ( 1 - gAbsorbance )*speed);
			cha->setVelocityX(cha->getVelocity().x*0.5f*speed);
			cha->setVelocityZ(cha->getVelocity().z*0.5f*speed);
		}
	}
	else
	{
		cha->setVelocityX(cha->getVelocity().x*0.5f*speed);
		cha->setVelocityZ(cha->getVelocity().z*0.5f*speed);
	}


	if( cha->getPosition().y > rCeiling - ( mySize * 0.5f ) )
	{
		cha->setPositionY(rCeiling - ( mySize * 0.5f ));
		cha->setVelocityY(-cha->getVelocity().y * ( 1 - gAbsorbance )*speed);
		cha->setVelocityX(cha->getVelocity().x*0.5f*speed);
		cha->setVelocityZ(cha->getVelocity().z*0.5f*speed);
	}

	if( cha->getPosition().z < minBoundz + ( mySize * 0.5f ) )
	{
		cha->setPositionZ(minBoundz + ( mySize * 0.5f ));
		cha->setVelocityZ(-(cha->getVelocity().z) * ( 1 - gAbsorbance )*speed);
	}
	if( cha->getPosition().x < minBoundx + ( mySize * 0.5f ) )
	{
		cha->setPositionX(minBoundx + ( mySize * 0.5f ));
		cha->setVelocityX(-(cha->getVelocity().x) * ( 1 - gAbsorbance )*speed);
	}
	if( cha->getPosition().z > maxBoundz - ( mySize * 0.5f ) )
	{
		cha->setPositionZ(maxBoundz - ( mySize * 0.5f ));
		cha->setVelocityZ(-(cha->getVelocity().z) * ( 1 - gAbsorbance )*speed);
	}
	if( cha->getPosition().x > maxBoundx - ( mySize * 0.5f ) )
	{
		cha->setPositionX(maxBoundx - ( mySize * 0.5f ));
		cha->setVelocityX(-(cha->getVelocity().x) * ( 1 - gAbsorbance )*speed);
	}

	if(wallxr){
		if( cha->getPosition().x > wall_position - ( mySize * 0.5f ) )
		{
			cha->setPositionX(wall_position - ( mySize * 0.5f ));
			cha->setVelocityX(-(cha->getVelocity().x) * ( 1 - gAbsorbance )*speed);
		}
	}
	if(wallxl){
		if( cha->getPosition().x < wall_position + ( mySize * 0.5f ) )
		{
			cha->setPositionX(wall_position + ( mySize * 0.5f ));
			cha->setVelocityX(-(cha->getVelocity().x) * ( 1 - gAbsorbance )*speed);
		}
	}
	if(wallyr){
	}
	if(wallyl){
	}
	if(wallzr){
		if( cha->getPosition().z > minBoundz - ( mySize * 0.5f ) )
		{
			cha->setPositionZ(minBoundz - ( mySize * 0.5f ));
			cha->setVelocityZ(-(cha->getVelocity().z) * ( 1 - gAbsorbance )*speed);
		}
	}
	if(wallzl){
		if( cha->getPosition().z < minBoundz + ( mySize * 0.5f ) )
		{
			cha->setPositionZ(minBoundz + ( mySize * 0.5f ));
			cha->setVelocityZ(-(cha->getVelocity().z) * ( 1 - gAbsorbance )*speed);
		}

	}
}

void Moving::getPositionWall(Ball* cha,float speed,D3DXVECTOR3 wall){
	wallxl = false;
	wallxr = false;
	wallyl = false;
	wallyr = false;
	wallzl = false;
	wallzr = false;

	if(wall.x!=0){
		wall_position = wall.x;
		if(cha->getPosition().x>wall_position)
			wallxr = true;
		else
			wallxl = true;
	}
	else if(wall.y!=0){
		wall_position = wall.y;
		if(cha->getPosition().y>wall_position)
			wallyr = true;
		else
			wallyl = true;
	}
	else if(wall.z!=0){
		wall_position = wall.z;
		if(cha->getPosition().z>wall_position)
			wallzr = true;
		else
			wallzl = true;
	}
}