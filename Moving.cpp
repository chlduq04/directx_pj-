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
}