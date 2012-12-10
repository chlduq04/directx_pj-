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

	void upLevel();
	void downLevel();
	
	void setDefence(int argu);
	void getDefence();

	void move();

	
	inline bool isAlive(){return alive;};
	inline void setAlive(bool argu){alive = argu;};
	inline int hisLife(){return life;};
	inline int hisMana(){return mana;};
	inline int hisWeight(){return weight;};
	inline int hisDef(){return def;};
	inline void setPosition(D3DXVECTOR3 xyz){ptPosition = xyz;};
	inline void setVelocity(D3DXVECTOR3 xyz){ptVelocity= xyz;};
	inline void setGoal(D3DXVECTOR3 xyz){ptGoal = xyz;};
	
	inline bool isGround(){return ptGround;}
	inline void setGround(bool argu){ptGround = argu;}

	inline void setPositionX(float argu){ptPosition.x = argu;}
	inline void setPositionY(float argu){ptPosition.y = argu;}
	inline void setPositionZ(float argu){ptPosition.z = argu;}
	inline void setVelocityX(float argu){ptVelocity.x = argu;}
	inline void setVelocityY(float argu){ptVelocity.y = argu;}
	inline void setVelocityZ(float argu){ptVelocity.z = argu;}
	inline void setGoalX(float argu){ptGoal.x = argu;}
	inline void setGoalY(float argu){ptGoal.y = argu;}
	inline void setGoalZ(float argu){ptGoal.z = argu;}
	inline D3DXVECTOR3 getPosition(){return ptPosition;}
	inline D3DXVECTOR3 getVelocity(){return ptVelocity;}
	inline D3DXVECTOR3 getGoal(){return ptGoal;}


};
#endif 