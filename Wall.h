#ifndef _WALL_H_
#define _WALL_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "Settings.h"
class Wall{
private:
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vVelocity;
	float fHp;
	float fType;
	bool bGround;
	int nBouncecount;
	BOOL g_bView;
public:
	Wall();
	inline int GetBcount(){return nBouncecount;};
	inline void SetBcount(){nBouncecount++;};
	inline float GetHp(){return fHp;};
	inline void SetHp(float argu){fHp = argu;};
	inline float GetType(){return fType;};
	inline void SetType(float argu){fType = argu;};

	inline void SetPosition(D3DXVECTOR3 argu){vPosition = argu;};
	inline D3DXVECTOR3 GetPosition(){return vPosition;};
	inline void SetVelocity(D3DXVECTOR3 argu){vVelocity = argu;};
	inline D3DXVECTOR3 GetVelocity(){return vVelocity;};

	inline void SetPositionX(float argu){vPosition.x = argu;};
	inline void SetPositionY(float argu){vPosition.y = argu;};
	inline void SetPositionZ(float argu){vPosition.z = argu;};
	inline float GetPositionX(){return vPosition.x;};
	inline float GetPositionY(){return vPosition.y;};
	inline float GetPositionZ(){return vPosition.z;};
	inline void SetVelocityX(float argu){vVelocity.x = argu;};
	inline void SetVelocityY(float argu){vVelocity.y = argu;};
	inline void SetVelocityZ(float argu){vVelocity.z = argu;};
	inline float GetVelocityX(){return vVelocity.x;};
	inline float GetVelocityY(){return vVelocity.y;};
	inline float GetVelocityZ(){return vVelocity.z;};
	
	inline bool IsGround(){return bGround;};
	inline void IsGround(bool argu){bGround = argu;};

	inline void ResetPosVel(){
		vPosition = D3DXVECTOR3(0,MAXBOUNDY,0);
		vVelocity = D3DXVECTOR3(0,0,0);
		bGround = false;
		nBouncecount = 0;
	};
	inline bool GetView(){return g_bView;};
	inline void SetView(bool view){g_bView = view;};
};
#endif