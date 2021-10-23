#include "VidMemViaDDraw.h"
#include "glew\include\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */





BOOL WINAPI DDEnumCallbackEx(GUID FAR* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext, HMONITOR hm)
{
    UNREFERENCED_PARAMETER(lpDriverDescription);

    DDRAW_MATCH* pDDMatch = (DDRAW_MATCH*)lpContext;
    if (pDDMatch->hMonitor == hm)
    {
        pDDMatch->bFound = true;
        strcpy_s(pDDMatch->strDriverName, 512, lpDriverName);
        memcpy(&pDDMatch->guid, lpGUID, sizeof(GUID));
    }
    return TRUE;
}


//-----------------------------------------------------------------------------
HRESULT GetVideoMemoryViaDirectDraw(HMONITOR hMonitor, DWORD* pdwAvailableVidMem)
{
    LPDIRECTDRAW pDDraw = nullptr;
    LPDIRECTDRAWENUMERATEEXA pDirectDrawEnumerateEx = nullptr;
    HRESULT hr;
    bool bGotMemory = false;
    *pdwAvailableVidMem = 0;

    HINSTANCE hInstDDraw;
    LPDIRECTDRAWCREATE pDDCreate = nullptr;

    hInstDDraw = LoadLibrary("ddraw.dll");
    if (hInstDDraw)
    {
        DDRAW_MATCH match = {};
        match.hMonitor = hMonitor;

        pDirectDrawEnumerateEx = (LPDIRECTDRAWENUMERATEEXA)GetProcAddress(hInstDDraw, "DirectDrawEnumerateExA");

        if (pDirectDrawEnumerateEx)
        {
            hr = pDirectDrawEnumerateEx(DDEnumCallbackEx, (VOID*)&match, DDENUM_ATTACHEDSECONDARYDEVICES);
        }

        pDDCreate = (LPDIRECTDRAWCREATE)GetProcAddress(hInstDDraw, "DirectDrawCreate");
        if (pDDCreate)
        {
            pDDCreate(&match.guid, &pDDraw, nullptr);

            LPDIRECTDRAW7 pDDraw7;
            if (SUCCEEDED(pDDraw->QueryInterface(IID_IDirectDraw7, (VOID**)&pDDraw7)))
            {
                DDSCAPS2 ddscaps = {};
                ddscaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;
                hr = pDDraw7->GetAvailableVidMem(&ddscaps, pdwAvailableVidMem, nullptr);
                if (SUCCEEDED(hr))
                    bGotMemory = true;
                pDDraw7->Release();
            }
        }
        FreeLibrary(hInstDDraw);
    }


    if (bGotMemory)
        return S_OK;
    else
        return E_FAIL;
}

float vramBudget()
{
    GLint total_mem_kb = 0;
    glGetIntegerv(0x9048, &total_mem_kb);
    return total_mem_kb / (1000); // KB to MB
    
}

float vramAvailable()
{
    GLint avaliable_mem_kb = 0;
    glGetIntegerv(0x9049, &avaliable_mem_kb);
    return avaliable_mem_kb / (1000); // KB to MB
  
}

float vramReserved()
{
    return 0.0f;
}


HRESULT GetDeviceIDFromHMonitor(HMONITOR hm, WCHAR* strDeviceID, int cchDeviceID)
{

    HINSTANCE hInstDDraw;

    hInstDDraw = LoadLibrary("ddraw.dll");
    if (hInstDDraw)
    {
        DDRAW_MATCH match = {};
        match.hMonitor = hm;

        LPDIRECTDRAWENUMERATEEXA pDirectDrawEnumerateEx = nullptr;
        pDirectDrawEnumerateEx = (LPDIRECTDRAWENUMERATEEXA)GetProcAddress(hInstDDraw, "DirectDrawEnumerateExA");

        if (pDirectDrawEnumerateEx)
            pDirectDrawEnumerateEx(DDEnumCallbackEx, (VOID*)&match, DDENUM_ATTACHEDSECONDARYDEVICES);

        if (match.bFound)
        {
            LONG iDevice = 0;
            DISPLAY_DEVICEA dispdev = {};
            dispdev.cb = sizeof(dispdev);

            while (EnumDisplayDevicesA(nullptr, iDevice, (DISPLAY_DEVICEA*)&dispdev, 0))
            {
                // Skip devices that are monitors that echo another display
                if (dispdev.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER)
                {
                    iDevice++;
                    continue;
                }

                // Skip devices that aren't attached since they cause problems
                if ((dispdev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) == 0)
                {
                    iDevice++;
                    continue;
                }

                if (_stricmp(match.strDriverName, dispdev.DeviceName) == 0)
                {
                    MultiByteToWideChar(CP_ACP, 0, dispdev.DeviceID, -1, strDeviceID, cchDeviceID);
                    return S_OK;
                }

                iDevice++;
            }
        }

        FreeLibrary(hInstDDraw);
    }


    return E_FAIL;
}