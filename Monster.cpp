#include "Monster.h"

Monster::~Monster(){}
Monster::Monster(float life,int weight,D3DXVECTOR3 position,D3DXVECTOR3 velocity,D3DXVECTOR3 goal){
	maxLife = life;
	mLife = life;
	mWeight = weight;
	mAttack = 0;
	mDefence = 0;
	mType = 0;
	sType = 0;
	mMotion = 0;
	mAlive = true;
	vPosition = position; 
	vVelocity = velocity;
	vGoal = goal;
	bGround = true;
	bMove = false;
	bJump = false;
	bGoal = false;

	defendTime = 8.0f;
}
void Monster::setisGoal(bool argu){
	bGoal = argu;
}
bool Monster::isGoal(){
	return bGoal;
}
bool Monster::isAlive(){
	return mAlive;
}
int Monster::hisLife(){
	return mLife;
}
bool Monster::isbGround(){
	return bGround;
}

void Monster::setGoal(D3DXVECTOR3 goal){
	vGoal = goal;
}
void Monster::setGoalX(float goal){
	vGoal.x = goal;
}
void Monster::setGoalY(float goal){
	vGoal.y = goal;
}
void Monster::setGoalZ(float goal){
	vGoal.z = goal;
}


D3DXVECTOR3 Monster::getGoal(){
	return vGoal;
}

void Monster::setPostion(D3DXVECTOR3 position){
	vPosition = position;
}
void Monster::setPostionX(float position){
	vPosition.x = position;
}
void Monster::setPostionY(float position){
	vPosition.y = position;
}
void Monster::setPostionZ(float position){
	vPosition.z = position;
}
D3DXVECTOR3 Monster::getPosition(){
	return vPosition;
}

void Monster::setMove(bool argu){
	bMove = argu;
}
bool Monster::isMove(){
	return bMove;
}

void Monster::setJump(bool argu){
	bJump = argu;
}
bool Monster::isJump(){
	return bJump;
}
void Monster::monDefence(int def){
	mDefence = def;
}
void Monster::monAttack(){
	mAttack = 20;
}
void Monster::monMissile(){

}
void Monster::monJump(){
	
}
void Monster::monHealing(){
	if(mLife<maxLife){
		mLife += 0.1;
	}
}
void Monster::setVelocity(D3DXVECTOR3 vel){
	vVelocity = vel;
}
void Monster::setVelocityX(float vel){
	vVelocity.x = vel;
}
void Monster::setVelocityY(float vel){
	vVelocity.y = vel;
}
void Monster::setVelocityZ(float vel){
	vVelocity.z = vel;
}

D3DXVECTOR3 Monster::getVelocity(){
	return vVelocity;
}

void Monster::setmType(int type){
	mType = type;
}
int Monster::getmType(){
	return mType;
}
void Monster::setsType(int type){
	sType= type;
}
int Monster::getsType(){
	return sType;
}

float Monster::getDefTime(){
	return defendTime;
}
