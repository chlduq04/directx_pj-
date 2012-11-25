#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <d3d9.h>
#include <d3dx9.h>

/*다른 header를 include 하면 여기서 include 2*/
//-----------------------------------------------------------------------------
// Camera
//-----------------------------------------------------------------------------
HWND					g_hwnd = NULL;


ZCamera*				g_pCamera = NULL;
DWORD					g_cxHeight = 0;
DWORD					g_czHeight = 0;
DWORD					g_dwMouseX = 0;
DWORD					g_dwMouseY = 0;
#endif 