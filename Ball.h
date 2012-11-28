#ifndef _BALL_H_
#define _BALL_H_

#include <d3d9.h>
#include <d3dx9.h>

class Ball{
private:
	int level;
	int maxLevel;

	bool alive;
	int life;
	int mana;
	int weight;
	int def;

	int maxLife;
	int maxMana;
	int maxWeight;
	int maxDef;
	bool ptGround;

	D3DXVECTOR3 ptPosition;
	D3DXVECTOR3 ptVelocity;
	D3DXVECTOR3 ptGoal;
	

public:
	Ball();
	Ball(int life,int mana,int weight,int setMaxLevel,D3DXVECTOR3 position,D3DXVECTOR3 velocity,D3DXVECTOR3 goal);
	bool isAlive();
	void setAlive(bool argu);
	int hisLife();
	int hisMana();
	int hisWeight();
	int hisDef();
	
	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getVelocity();
	D3DXVECTOR3 getGoal();

	bool isGround();
	void setGround(bool argu);

	void setMaxLife(int argu);
	void setMaxMana(int argu);
	void setMaxWeight(int argu);
	void setMaxDef(int argu);

	void setLife(int argu);
	void setMana(int argu);
	void setWeight(int argu);
	void setDef(int argu);

	bool spendLife(int argu);
	bool spendMana(int argu);
	bool spendWeight(int argu);
	bool spendDef(int argu);

	void setPosition(D3DXVECTOR3 xyz);
	void setVelocity(D3DXVECTOR3 xyz);
	void setGoal(D3DXVECTOR3 xyz);

	void setPositionX(float argu);
	void setPositionY(float argu);
	void setPositionZ(float argu);

	void setVelocityX(float argu);
	void setVelocityY(float argu);
	void setVelocityZ(float argu);

	void setGoalX(float argu);
	void setGoalY(float argu);
	void setGoalZ(float argu);

	void upLevel();
	void downLevel();
	
	void setDefence(int argu);
	void getDefence();

	void move();
};
#endif 