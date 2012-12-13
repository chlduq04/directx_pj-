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
#define START_WEIGHT 0
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
#define WALL_GAB  2.0f
//-----------------------------------------------------------------------------
// Mon
//-----------------------------------------------------------------------------
#define START_MON_POSITIONX 160.0f
#define START_MON_POSITIONY 30.0f
#define START_MON_POSITIONZ 160.0f

#define START_MON_VELOCITYX 0.0f
#define START_MON_VELOCITYY 0.0f
#define START_MON_VELOCITYZ 0.0f

#define MON_HEALTH 1000.0f
#define MON_WEIGHT 10

#define MSI_START_DELAY 1 //25
#define MSI_END_DELAY 1 //30
#define MSI_MOTION_DELAY 2

#define DEF_START_DELAY 5
#define DEF_END_DELAY 15
#define DEF_MOTION_DELAY 3

#define WALL_START_DELAY 10
#define WALL_END_DELAY 25
#define WALL_MOTION_DELAY 5

#define HEAL_START_DELAY 5
#define HEAL_END_DELAY 15
#define HEAL_MOTION_DELAY 5

#define RASER_START_DELAY 5
#define RASER_END_DELAY 30
#define RASER_MOTION_DELAY 5

#define RUSH_START_DELAY 5
#define RUSH_END_DELAY 10
#define RUSH_MOTION_DELAY 1

#define NATT_START_DELAY 5
#define NATT_END_DELAY 10
#define NATT_MOTION_DELAY 1
#define NATT_ATT_RANGE 5

//-----------------------------------------------------------------------------
// Setting
//-----------------------------------------------------------------------------
#define BALL_SIZE 0.02f
#define MON_SIZE 0.1f
#define MISSILE_SIZE 0.01f

#define MON_REAL_SIZE 3.0f
#define BALL_REAL_SIZE 5.0f
#define ITEM_REAL_SIZE 10.0f
#define MISSILE_REAL_SIZE 1.0f

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
#define BOUNCE_LOST 0.1f
#define BOUNCE_TRANSFER 0.05f


#endif 