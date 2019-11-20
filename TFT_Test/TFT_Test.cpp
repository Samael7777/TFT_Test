

#include <iostream>
#include <Windows.h>
#include "GUI/GUI.h"

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	
	MSG msg;

	GuiInit();
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	
}


