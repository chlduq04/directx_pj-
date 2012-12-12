#ifndef _WALL_H_
#define _WALL_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "Settings.h"
class Wall{
private:
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vVelocity;
	float hp;
	float type;
	bool ground;
public:
	Wall();
	inline float getHp(){return hp;};
	inline void setHp(float argu){hp = argu;};
	inline float getType(){return type;};
	inline void setType(float argu){type = argu;};

	inline void setPosition(D3DXVECTOR3 argu){vPosition = argu;};
	inline D3DXVECTOR3 getPosition(){return vPosition;};
	inline void setVelocity(D3DXVECTOR3 argu){vVelocity = argu;};
	inline D3DXVECTOR3 getVelocity(){return vVelocity;};

	inline void setPositionX(float argu){vPosition.x = argu;};
	inline void setPositionY(float argu){vPosition.y = argu;};
	inline void setPositionZ(float argu){vPosition.z = argu;};
	inline float getPositionX(){return vPosition.x;};
	inline float getPositionY(){return vPosition.y;};
	inline float getPositionZ(){return vPosition.z;};
	inline void setVelocityX(float argu){vVelocity.x = argu;};
	inline void setVelocityY(float argu){vVelocity.y = argu;};
	inline void setVelocityZ(float argu){vVelocity.z = argu;};
	inline float getVelocityX(){return vVelocity.x;};
	inline float getVelocityY(){return vVelocity.y;};
	inline float getVelocityZ(){return vVelocity.z;};
	
	inline bool isGround(){return ground;};
	inline void isGround(bool argu){ground = argu;};
};
#endif