#ifndef _WALL_H_
#define _WALL_H_

#include <d3d9.h>
#include <d3dx9.h>

class Wall{
private:
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vVelocity;
	float hp;
	float type;
public:
	inline float getHp(){return hp;};
	inline void setHp(float argu){hp = argu;};
	inline float getType(){return type;};
	inline void setType(float argu){type = argu;};

	inline void setPosition(D3DXVECTOR3 argu){vPosition = argu;};
	inline D3DXVECTOR3 getPosition(){return vPosition;};
	inline void setVelocity(D3DXVECTOR3 argu){vVelocity = argu;};
	inline D3DXVECTOR3 getvelocity(){return vVelocity;};
};
#endif