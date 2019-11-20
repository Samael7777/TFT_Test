#include "display_wnd.h"
#include "..\GUI\GUI.h"
#include <Windows.h>


HANDLE thrd;
HWND hWnd;
MSG msg;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DisplayThread();
void ProcessKey(WPARAM key);

void ProcessKey(WPARAM key)
{
	switch (key)
	{
	case VK_UP:
		GuiProcess(KEY_UP);
		break;
	case VK_DOWN:
		GuiProcess(KEY_DOWN);
		break;
	case VK_RETURN:
		GuiProcess(KEY_ENT);
		break;
	default:
		break;
	}
}

HWND DisplayInit() 
{
	thrd = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&DisplayThread, 0, 0, 0);
	while (!hWnd);
	if (hWnd) 
	{
		RECT ws, cs;
		UINT hh, bw, wh, ww;
		GetWindowRect(hWnd, &ws);
		GetClientRect(hWnd, &cs);
		ww = ws.right - ws.left;
		wh = ws.bottom - ws.top;
		bw = ww - cs.right;
		hh = wh - cs.bottom;
		SetWindowPos(hWnd, HWND_TOP, ws.top, ws.bottom, TFT_WIDTH + bw, TFT_HEIGHT + hh, SWP_SHOWWINDOW);
	}
	return hWnd;
}

void DisplayDeinit() 
{
	SendMessage(hWnd, WM_DESTROY, NULL, NULL);
}

//Работа с GDI

void DisplayThread()
{
	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = NULL;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = NULL;
	//wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("TFT Display");


	RegisterClass(&wndClass);


	hWnd = CreateWindow(
		TEXT("TFT Display"),	  // window class name
		TEXT("TFT Display"),	  // window caption
		WS_DLGFRAME,
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		TFT_WIDTH,				  // initial x size
		TFT_HEIGHT,				  // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		NULL,				      // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ExitProcess(0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_SIZING: // I use this message to redraw window on sizing (o rly?)
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_INTERNALPAINT);
		return 0;
	case WM_PAINT:
	{
		return 0;
	}
	case WM_KEYDOWN:
	{
		ProcessKey(wParam);
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}