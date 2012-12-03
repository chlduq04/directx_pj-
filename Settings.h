#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <d3d9.h>
#include <d3dx9.h>

//-----------------------------------------------------------------------------
// My
//-----------------------------------------------------------------------------
#define START_POSITIONX 10.0f
#define START_POSITIONY 10.0f
#define START_POSITIONZ 10.0f

#define START_VELOCITYX 0.0f
#define START_VELOCITYY 0.0f
#define START_VELOCITYZ 0.0f

#define START_LIFE	100 
#define START_MANA	100

#define CHARACTER_MAX_LEVEL 10


//-----------------------------------------------------------------------------
// Room
//-----------------------------------------------------------------------------
#define MINBOUNDX 1.0f
#define MINBOUNDY 1.0f
#define MINBOUNDZ 1.0f

#define MAXBOUNDX 160.0f
#define MAXBOUNDY 160.0f
#define MAXBOUNDZ 160.0f

//-----------------------------------------------------------------------------
// Mon
//-----------------------------------------------------------------------------
#define START_MON_POSITIONX 130.0f
#define START_MON_POSITIONY 0.0f
#define START_MON_POSITIONZ 130.0f

#define START_MON_VELOCITYX 0.0f
#define START_MON_VELOCITYY 0.0f
#define START_MON_VELOCITYZ 0.0f

#define MON_HEALTH 1000.0f

//-----------------------------------------------------------------------------
// Setting
//-----------------------------------------------------------------------------
#define BALL_SIZE 0.02f
#define MON_SIZE 0.1f

#define MON_REAL_SIZE 8.0f
#define BALL_REAL_SIZE 5.0f
#define ITEM_REAL_SIZE 10.0f

#define GRAVITY 0.5f
#define REVERSE_GRAVITY 0.05f

#define GROUND 1.0f
#define MYSIZE 1.0f
#define CEILING 160.0f
#define THRESHOLD 0.04f
#define BALLSPEED 0.1f
#define GAMESPEED 1.0f
#define ABSORBANCE 0.02f

#define MOUSE_SENSITIVE 0.001f

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

float GSpeed = GAMESPEED;

#endif 