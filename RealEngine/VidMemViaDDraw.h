#ifndef _VIDMEMVIADDRAW_H_
#define _VIDMEMVIADDRAW_H_
//----------------------------------------------------------------------------
// File: VidMemViaDDraw.cpp
//
// This method queries the DirectDraw 7 interfaces for the amount of available 
// video memory. On a discrete video card, this is often close to the amount 
// of dedicated video memory and usually does not take into account the amount 
// of shared system memory. This number can end up smaller than expected
// on systems with large memories and/or large VRAM video cards due to
// 32-bit overflow. DXGI doesn't suffer from these issues.
//
// Copyright (c) Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#define INITGUID
#include <winuser.inl>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <ddraw.h>


//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=nullptr; } }
#endif

typedef HRESULT(WINAPI* LPDIRECTDRAWCREATE)(GUID FAR* lpGUID, LPDIRECTDRAW FAR* lplpDD, IUnknown FAR* pUnkOuter);

struct DDRAW_MATCH {
	GUID guid;
	HMONITOR hMonitor;
	CHAR strDriverName[512];
	bool bFound;
};


//-----------------------------------------------------------------------------
BOOL WINAPI DDEnumCallbackEx(GUID FAR* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext, HMONITOR hm);
//-----------------------------------------------------------------------------
HRESULT GetVideoMemoryViaDirectDraw(HMONITOR hMonitor, DWORD* pdwAvailableVidMem); //Returns the avaliable memory dedicated to video

float vramBudget();
float vramUsage();
float vramAvailable();
float vramReserved();


#endif