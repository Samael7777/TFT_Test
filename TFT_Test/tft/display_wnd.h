#pragma once
#include "..\tft\win32_drv.h"
#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

HWND DisplayInit();
void DisplayDeinit();

#ifdef __cplusplus
}
#endif