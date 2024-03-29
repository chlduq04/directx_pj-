#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <d3d9.h>
#include <d3dx9.h>
const DWORD  VERTEXFVF = D3DFVF_XYZ | D3DFVF_TEX2; 
#define DEL(p)	{ if(p) { delete (p); (p) = NULL;}} 
#define DELS(p)	{ if(p) { delete[] (p); (p) = NULL;}} 
#define REL(p)	{ if(p) { (p)->Release(); (p) = NULL;}} 
#define CHANGE_ACTION_NUM 6
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
#define MISSILE_COUNT 35
#define MISSILE_INITIAL_COUNT 15
#define START_MON_POSITIONX 160.0f
#define START_MON_POSITIONY 20.0f
#define START_MON_POSITIONZ 20.0f

#define START_MON_VELOCITYX 0.0f
#define START_MON_VELOCITYY 0.0f
#define START_MON_VELOCITYZ 0.0f

#define MON_ATTACK_RANGE 5
#define MON_HEALTH 1000.0f
#define MON_WEIGHT 10

#define DODGE_DELAY 10
#define JUMP_DELAY 6

#define MSI_START_DELAY 25//25
#define MSI_END_DELAY 30// 30
#define MSI_MOTION_DELAY 4

#define DEF_START_DELAY 5
#define DEF_END_DELAY 15
#define DEF_MOTION_DELAY 3

#define WALL_START_DELAY 10
#define WALL_END_DELAY 25
#define WALL_MOTION_DELAY 5

#define HEAL_START_DELAY 5
#define HEAL_END_DELAY 15
#define HEAL_MOTION_DELAY 5

#define LASER_START_DELAY 5
#define LASER_END_DELAY 30
#define LASER_MOTION_DELAY 3

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
#define NORMAL_MOVE_PATTERN 0
#define	CONTECT_MOVE_PATTERN 1
#define DODGE_MOVE_PATTERN 2
#define STOP_MOVE_PATTERN 3
#define JUMP_MOVE_PATTERN 4

#define MISSILE_ACTION_PATTERN 0
#define HEALING_ACTION_PATTERN 1
#define DEFENCE_ACTION_PATTERN 2
#define LASER_ACTION_PATTERN 3
#define NATTACK_ACTION_PATTERN 4
#define WALL_ACTION_PATTERN 5

#define MOVE_PATTERN_COUNT 5
#define ACTION_PATTERN_COUNT 6

#define BALL_SIZE 0.02f
#define MON_SIZE 0.2f
#define MISSILE_SIZE 0.02f

#define MON_REAL_SIZE 10.0f
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

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define BOUNCE_LOST 0.1f
#define BOUNCE_TRANSFER 0.05f

#define LASER_SIZE 5.0f
#endif 