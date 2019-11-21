
#ifndef __TFT_LIB_H
#define __TFT_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "../Font/Font.h"
#include "win32_drv.h"
#include "COLOR_RGB565.h"



	typedef struct {
		uint16_t x;
		uint16_t y;
		uint16_t fore_color;
		uint16_t back_color;
	} CursorType;


	typedef struct {
		uint16_t x_start;
		uint16_t y_start;
		uint16_t x_end;
		uint16_t y_end;
		uint16_t fore_color;
		uint16_t back_color;
		uint16_t max_pos;
		uint16_t max_lines;
	} ConsoleType;

	typedef struct {
		uint16_t x;
		uint16_t y;
	} PixelType;

	//---------------------------------------------------------------------------
#define swap(a, b) { int16_t t = a; a = b; b = t; }
#define convert24to16(x) (((x & 0x00F80000)>>8)|((x & 0x0000FC00)>>5)|((x & 0x000000F8)>>3))
//---------------------------------------------------------------------------

/* -------------------------------------------------------------------------------- */
/* -- PROTOTYPES                                                                 -- */
/* -------------------------------------------------------------------------------- */
/*Initialization*/
	void TFT_Init();
	void TFT_Deinit();
	/* Classic functions */
	void DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void DrawHLine(int16_t x0, int16_t y0, int16_t len, uint16_t color);
	void DrawVLine(int16_t x0, int16_t y0, int16_t len, uint16_t color);
	void Draw_Arc(int16_t x0, int16_t y0, int16_t r, uint8_t s, uint16_t color);
	void DrawMesh(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void DrawRoundRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t r, uint16_t color);
	void FillRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void FillRoundRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t r, uint16_t color);
	void DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void DrawEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color);
	void FillEllipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint16_t color);
	void DrawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color);
	void FillTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color);
	void DrawArc(int16_t x, int16_t y, int16_t r, int16_t startAngle, int16_t endAngle, int16_t thickness, uint16_t color);
	void DrawPie(int16_t x, int16_t y, int16_t r, int16_t startAngle, int16_t endAngle, uint16_t color);
	void FillScreen(uint16_t color);


	void PutChar(int16_t x, int16_t y, char chr, TFTFontType* font, uint16_t fc, uint16_t bc);
	void PutString(uint16_t x, uint16_t y, char* str, TFTFontType* font, uint16_t fc, uint16_t bc);
	void UTF8rusPutString(uint16_t x, uint16_t y, char* str, TFTFontType* font, uint16_t fc, uint16_t bc);

	void DrawImage(uint16_t x0, uint16_t y0, uint16_t size_x, uint16_t size_y, uint16_t* img);

	uint16_t DrawPChar16(uint16_t x, uint16_t y, uint8_t ascii, pFont16* font, uint16_t vg, uint16_t bg);
	void DrawPString16(uint16_t x, uint16_t y, char* ptr, pFont16* font, uint16_t vg, uint16_t bg);
	uint16_t DrawPChar32(uint16_t x, uint16_t y, uint8_t ascii, pFont32* font, uint16_t vg, uint16_t bg);

	void DrawPString32(uint16_t x, uint16_t y, char* ptr, pFont32* font, uint16_t vg, uint16_t bg);

	void ConsoleSetArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);
	uint16_t GetCursor_x(void);
	uint16_t GetCursor_y(void);
	void CursorSet(uint16_t x, uint16_t y);
	

	void FontSetHSpace(int8_t s);
	void FontSetVSpace(int8_t s);
	void FontSelect(TFTFontType* font);

	void ConsoleClean(uint16_t bc);
	uint16_t ConsoleGetMaxChars(void);
	uint16_t ConsoleGetMaxLines(void);
	uint16_t ConsoleGetLineHeight(void);
	uint16_t ConsoleGetCharidth(void);
	PixelType CursorToPixel(void);
	void ConsoleMarkLine(char* text, uint16_t line, uint16_t fc, uint16_t bc);
	void ConsoleMarkChar(char* text, uint16_t x, uint16_t y, uint16_t fc, uint16_t bc);
	void ConsolePutChar(char chr, uint16_t fc, uint16_t bc);
	void ConsolePutString(char* str, uint16_t fc, uint16_t bc);
	void ConsolePutStringln(char* str, uint16_t fc, uint16_t bc);
	void PutString_Hex8(uint8_t chr, uint16_t fc, uint16_t bc);
	void PutString_Hex16(uint16_t chr, uint16_t fc, uint16_t bc);
	void PutString_Hex32(uint32_t chr, uint16_t fc, uint16_t bc);
	void PutString_dec_xx(uint8_t data, uint16_t fc, uint16_t bc);
	void PutString_dec_xxx(uint16_t data, uint16_t fc, uint16_t bc);
	void PutString_dec_xxxx(uint16_t data, uint16_t fc, uint16_t bc);
	void PutString_Intflag(int32_t a, uint8_t flag, uint16_t fc, uint16_t bc);
	void PutString_Int(int32_t a, uint16_t fc, uint16_t bc);
	void PutString_Float(float a, uint8_t digit_after_point, uint16_t fc, uint16_t bc);

	//---------------------------------------------------------------------------
	//void DrawLoadBMP(uint16_t x, uint16_t y, char *sname);
	//---------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif /* __TFT_LIB_H */
