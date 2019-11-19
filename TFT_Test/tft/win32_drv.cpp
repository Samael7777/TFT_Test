//
//******************************************************************************
//***       ÈÍÈÖÈÀËÈÇÀÖÈß ÄÈÑÏËÅß
//******************************************************************************

#include "win32_drv.h"

Options_t TFT_Opts;
HWND display;


COLORREF Color565to888(u16 color)
{
	u8 r, g, b;
	r = (u8)((color >> 11) & 0x1F) << 3;
	g = (u8)((color >> 5) & 0x3F) << 2;
	b = (u8)(color & 0x1F) << 3;
	return RGB(r, g, b);
}


//---------------------------------------------------------------------------------------
void DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	COLORREF col = Color565to888(color);
	HBRUSH brush = CreateSolidBrush(col);
	HDC dc = GetDC(display); //Öåïëÿåìñÿ ê îêíó
	//SelectObject(dc, brush);
	SetPixel(dc, x, y, col);
	DeleteObject(brush);
	ReleaseDC(display, dc);
}
//---------------------------------------------------------------------------------------
void TFT_Rotate(Orientation_t orientation)
{
	RECT pos, csize;
	UINT hh, bw;
	GetWindowRect(display, &pos);
	GetClientRect(display, &csize);
	bw = pos.right - pos.left - csize.right;
	hh = pos.bottom - pos.top - csize.bottom;
	switch (orientation)
	{
	case Orientation_Portrait_1:					// portrait		  0 ãðàäóñîâ	
		TFT_Opts.Width = TFT_WIDTH;
		TFT_Opts.Height = TFT_HEIGHT;
		SetWindowPos(display, HWND_TOP, pos.top, pos.left, TFT_Opts.Width + bw, TFT_Opts.Height + hh, SWP_SHOWWINDOW);
		TFT_Opts.orientation = Portrait;
		TFT_Opts.orient = Orientation_Portrait_1;
		break;
	case Orientation_Landscape_1:					// landscape	 90 ãðàäóñîâ
		
		TFT_Opts.Width = TFT_HEIGHT;
		TFT_Opts.Height = TFT_WIDTH;
		SetWindowPos(display, HWND_TOP, pos.top, pos.left, TFT_Opts.Width + bw, TFT_Opts.Height + hh, SWP_SHOWWINDOW);
		TFT_Opts.orientation = Landscape;
		TFT_Opts.orient = Orientation_Landscape_1;
		break;
	case Orientation_Portrait_2:					// portrait		180 ãðàäóñîâ
		TFT_Opts.Width = TFT_WIDTH;
		TFT_Opts.Height = TFT_HEIGHT;
		SetWindowPos(display, HWND_TOP, pos.top, pos.left, TFT_Opts.Width + bw, TFT_Opts.Height + hh, SWP_SHOWWINDOW);
		TFT_Opts.orientation = Portrait;
		TFT_Opts.orient = Orientation_Portrait_2;
		break;
	case Orientation_Landscape_2:					// landscape	270 ãðàäóñîâ
		TFT_Opts.Width = TFT_HEIGHT;
		TFT_Opts.Height = TFT_WIDTH;
		SetWindowPos(display, HWND_TOP, pos.top, pos.left, TFT_Opts.Width + bw, TFT_Opts.Height + hh, SWP_SHOWWINDOW);
		TFT_Opts.orientation = Landscape;
		TFT_Opts.orient = Orientation_Landscape_2;
		break;
	}
}
//---------------------------------------------------------------------------------------
uint16_t TFT_GetWidth(void)
{
	return (TFT_Opts.Width);
}
//---------------------------------------------------------------------------------------
uint16_t TFT_GetHeight(void)
{
	return (TFT_Opts.Height);
}
//---------------------------------------------------------------------------------------
/*
void TFT_Fill(uint16_t color)
{
	uint32_t n;
	SetWindow(0, 0, TFT_Opts.Width - 1, TFT_Opts.Height - 1);
	TFT_SendCommand(0x2C);

	for (n = 0; n < TFT_PIXEL_COUNT; n++)
	{
		TFT_SendData(color);
	}
}
*/

//---------------------------------------------------------------------------------------
void TFT_FillWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	COLORREF col = Color565to888(color);
	RECT wnd;
	HBRUSH Brush = CreateSolidBrush(col);
	HDC dc = GetDC(display);
	wnd.left = x1;
	wnd.right = x2;
	wnd.top = y1;
	wnd.bottom = y2;
	FillRect(dc, &wnd, Brush);
	DeleteObject(Brush);
	ReleaseDC(display, dc);
}
//---------------------------------------------------------------------------------------
void TFT_FillScreen(uint16_t color)
{
	COLORREF col = Color565to888(color);
	RECT ClientRect;
	HBRUSH Brush = CreateSolidBrush(col);
	HDC dc = GetDC(display);
	GetClientRect(display, &ClientRect);
	FillRect(dc, &ClientRect, Brush);
	DeleteObject(Brush);
	ReleaseDC(display, dc);
}
//---------------------------------------------------------------------------------------
/*
void TFT_Flood(uint16_t color, uint32_t len)
{
	uint16_t blocks;
	uint8_t i;
	TFT_SendCommand(0x2C);
	TFT_SendData(color);
	len--;
	blocks = (uint16_t)(len / 64);        //64pixels/blocks
	while (blocks--)
	{
		i = 16;
		do
		{
			TFT_SendData(color);
			TFT_SendData(color);
			TFT_SendData(color);
			TFT_SendData(color);
			TFT_SendData(color);
		} while (--i);
	}
	//Fill any remaining pixels (1 to 64);
	for (i = (uint8_t)len & 63; i--;)
	{
		TFT_SendData(color);
	}
}
*/


void TFT_Reset(void)
{
	RECT ClientRect;
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	HDC dc = GetDC(display);
	GetClientRect(display, &ClientRect);
	FillRect(dc, &ClientRect, Brush);
	DeleteObject(Brush);
	ReleaseDC(display, dc);
}
//---------------------------------------------------------------------------------------




void Drv_init()
{
	TFT_Opts.Width = TFT_WIDTH;
	TFT_Opts.Height = TFT_HEIGHT;
	TFT_Opts.orientation = Portrait;
	TFT_Opts.orient = Orientation_Portrait_1;
	display = DisplayInit();
}

HWND GetDisplayContext(void) 
{
	return display;
}
void Drv_deinit(void)
{
	DisplayDeinit();
}

//---------------------------------------------------------------------------------------
