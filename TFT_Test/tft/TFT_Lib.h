
#ifndef __TFT_LIB_H
#define __TFT_LIB_H

#include <stdint.h>
#include <Windows.h>
#include "../Font/Font.h"
#include "win32_drv.h"
#include "COLOR_RGB565.h"


typedef struct {
	uint16_t cur_x;
	uint16_t cur_y;
	uint16_t fore_color;
	uint16_t back_color;
	uint16_t max_pos;
	uint16_t max_lines;
} Cursor_t;


typedef struct {
    uint16_t x_pos;
    uint16_t y_pos;
    uint16_t x_start;
    uint16_t y_start;
    uint16_t x_end;
    uint16_t y_end;
    uint16_t fore_color;
    uint16_t back_color;
} Console_t;

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
void DrawLine( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color );
void DrawHLine( int16_t x0, int16_t y0, int16_t len, uint16_t color );
void DrawVLine( int16_t x0, int16_t y0, int16_t len, uint16_t color );
void Draw_Arc( int16_t x0, int16_t y0, int16_t r, uint8_t s, uint16_t color );
void DrawMesh( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color );
void DrawRectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color );
void DrawRoundRectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t r, uint16_t color );
void FillRectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color );
void FillRoundRectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t r, uint16_t color );
void DrawCircle( int16_t x0, int16_t y0, int16_t r, uint16_t color );
void FillCircle( int16_t x0, int16_t y0, int16_t r, uint16_t color );
void DrawEllipse( int16_t x0, int16_t y0, int16_t rx,int16_t ry, uint16_t color );
void FillEllipse( int16_t x0, int16_t y0, int16_t rx,int16_t ry, uint16_t color );
void DrawTriangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color );
void FillTriangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3,  uint16_t color );
void DrawArc( int16_t x, int16_t y, int16_t r, int16_t startAngle, int16_t endAngle, int16_t thickness, uint16_t color );
void DrawPie( int16_t x, int16_t y, int16_t r, int16_t startAngle, int16_t endAngle, uint16_t color );
void FillScreen(uint16_t color);


void PutChar( int16_t x, int16_t y, char chr, TFT_FONT_t *font, uint16_t fc, uint16_t bc );
void PutString( uint16_t x, uint16_t y, char *str, TFT_FONT_t *font, uint16_t fc, uint16_t bc);
void UTF8rusPutString( uint16_t x, uint16_t y, char *str, TFT_FONT_t *font, uint16_t fc, uint16_t bc );

void DrawImage( uint16_t x0, uint16_t y0, uint16_t size_x, uint16_t size_y, uint16_t *img );

uint16_t DrawPChar16( uint16_t x, uint16_t y, uint8_t ascii, pFont16 *font, uint16_t vg, uint16_t bg );
void DrawPString16( uint16_t x, uint16_t y,char *ptr, pFont16 *font, uint16_t vg, uint16_t bg );
uint16_t DrawPChar32( uint16_t x, uint16_t y, uint8_t ascii, pFont32 *font, uint16_t vg, uint16_t bg );

void DrawPString32( uint16_t x, uint16_t y,char *ptr, pFont32 *font, uint16_t vg, uint16_t bg );

void ConsoleSetArea( uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye );
uint16_t GetCursor_x(void);
uint16_t GetCursor_y(void);
void SetCursor(uint16_t x, uint16_t y);

void FontSetHSpace(int8_t s);
void FontSetVSpace(int8_t s);
void FontSelect(TFT_FONT_t* font);

void ConsoleClean(uint16_t bc);
void ConsolePutChar( char chr, uint16_t fc, uint16_t bc );
void ConsolePutString( char* str, uint16_t fc, uint16_t bc );
void ConsolePutStringln(char* str, uint16_t fc, uint16_t bc);
void PutString_Hex8(uint8_t chr, uint16_t fc, uint16_t bc );
void PutString_Hex16(uint16_t chr, uint16_t fc, uint16_t bc );
void PutString_Hex32(uint32_t chr, uint16_t fc, uint16_t bc );
void PutString_dec_xx( uint8_t data, uint16_t fc, uint16_t bc );
void PutString_dec_xxx( uint16_t data, uint16_t fc, uint16_t bc );
void PutString_dec_xxxx( uint16_t data, uint16_t fc, uint16_t bc );
void PutString_Intflag(int32_t a, uint8_t flag, uint16_t fc, uint16_t bc );
void PutString_Int( int32_t a, uint16_t fc, uint16_t bc );
void PutString_Float( float a, uint8_t digit_after_point, uint16_t fc, uint16_t bc );

//---------------------------------------------------------------------------
//void DrawLoadBMP(uint16_t x, uint16_t y, char *sname);
//---------------------------------------------------------------------------

#endif /* __TFT_LIB_H */
