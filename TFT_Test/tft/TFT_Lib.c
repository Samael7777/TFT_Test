#pragma warning(disable: 4244 26451) 


#include "TFT_Lib.h"
#include <math.h>

//uint16_t x, y;
int8_t char_h_space = 0;		// разряженость шрифта по горизонтали (кол-во пикселей между символами)
int8_t char_v_space = 0;		// разряженость шрифта по вертикали (кол-во пикселей между строками)

const uint8_t hex_decode[] =
{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const uint32_t digits[] =
{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};


extern OptionsType TFT_Opts;
TFTFontType tft_font;

CursorType cur;
ConsoleType console;

uint16_t LineHeight;		//Высота 1 линии в пикселях
uint16_t CharWidth;			//Ширина 1 символа в пикселях

void ConsoleSetArea(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
	uint16_t d_width, d_height;
	d_width = TFT_GetWidth();
	d_height = TFT_GetHeight();
	console.x_start = (xs <= d_width) ? xs : (d_width);
	console.x_end = (xe <= d_width) ? xe : d_width;
	console.y_start = (ys <= d_height) ? ys : (d_height);
	console.y_end = (ye <= d_height) ? ye : d_height;
	console.max_pos = (console.x_end - console.x_start) / (tft_font.char_width + char_h_space)-1;
	console.max_lines = (console.y_end - console.y_start) / (tft_font.char_height + char_v_space);
	cur.x = 0;
	cur.y = 0;
}

uint16_t ConsoleGetMaxChars(void)
{
	return console.max_pos;
}

uint16_t ConsoleGetMaxLines(void)
{
	return console.max_lines;
}

void ConsoleClean(uint16_t bc)
{
	FillRectangle(0, console.y_start, TFT_GetWidth(), console.y_end, bc);
	cur.x = 0;
	cur.y = 0;
}

PixelType CursorToPixel(void)
{
	PixelType pix;
	pix.x = console.x_start + cur.x * (tft_font.char_width + char_h_space);
	pix.y = console.y_start + cur.y * (tft_font.char_height + char_v_space);
	return pix;
}

void ConsoleMarkLine(char* text, uint16_t line, uint16_t fc, uint16_t bc)
{
	if (line >= console.max_lines) line = console.max_lines - 1;
	CursorSet(0, line);
	PixelType pix = CursorToPixel();
	uint16_t ye = pix.y + LineHeight;
	FillRectangle(console.x_start, pix.y, console.x_end, ye, bc);
	ConsolePutString(text, fc, bc);
}

void ConsoleMarkChar(char* text, uint16_t x, uint16_t y, uint16_t fc, uint16_t bc)
{
	if (x >= console.max_pos) x = console.max_pos - 1;
	if (y >= console.max_lines) x = console.max_lines - 1;
	CursorSet(x, y);
	PixelType s = CursorToPixel();
	uint16_t xe = s.x + tft_font.char_width + char_h_space;
	uint16_t ye = s.y + tft_font.char_height + char_v_space;
	FillRectangle(s.x, s.y, xe, ye, bc);
	ConsolePutChar(text, fc, bc);
}


uint16_t ConsoleGetLineHeight(void)
{
	return LineHeight;
}

uint16_t ConsoleGetCharWidth(void)
{
	return CharWidth;
}

void TFT_Init()
{
	Drv_init();
}



void TFT_Deinit()
{
	Drv_deinit();
}
//---------------------------------------------------------------------------------------
void CursorSet(uint16_t x, uint16_t y)
{
	cur.x = x;
	cur.y = y;
}
//---------------------------------------------------------------------------------------
uint16_t GetCursor_x(void)
{
  return (cur.x);
}
//---------------------------------------------------------------------------------------
uint16_t GetCursor_y(void)
{
  return (cur.y);
}
//---------------------------------------------------------------------------------------
void DrawLine( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color )
{
   int16_t n, dx, dy, sgndx, sgndy, dxabs, dyabs, x, y, drawx, drawy;

   dx = x2 - x1;
   dy = y2 - y1;
   dxabs = (dx>0)?dx:-dx;
   dyabs = (dy>0)?dy:-dy;
   sgndx = (dx>0)?1:-1;
   sgndy = (dy>0)?1:-1;
   x = dyabs >> 1;
   y = dxabs >> 1;
   drawx = x1;
   drawy = y1;

   DrawPixel(drawx, drawy, color);

   if( dxabs >= dyabs )
   {
      for( n=0; n<dxabs; n++ )
      {
         y += dyabs;
         if( y >= dxabs )
         {
            y -= dxabs;
            drawy += sgndy;
         }
         drawx += sgndx;
         DrawPixel(drawx, drawy, color);
      }
   }
   else
   {
      for( n=0; n<dyabs; n++ )
      {
         x += dxabs;
         if( x >= dyabs )
         {
            x -= dyabs;
            drawx += sgndx;
         }
         drawy += sgndy;
         DrawPixel(drawx, drawy, color);
      }
   }  
}
//---------------------------------------------------------------------------------------
void DrawHLine( int16_t x0, int16_t y0, int16_t len, uint16_t color )
{
	DrawLine( x0, y0, x0 + len, y0, color );
}
//---------------------------------------------------------------------------------------
void DrawVLine( int16_t x0, int16_t y0, int16_t len, uint16_t color )
{
	DrawLine( x0, y0, x0, y0 + len, color );
}

//---------------------------------------------------------------------------------------
void Draw_Arc( int16_t x0, int16_t y0, int16_t r, uint8_t s, uint16_t color )
{
   int16_t x, y, xd, yd, e;

   if ( x0 < 0 ) return;
   if ( y0 < 0 ) return;
   if ( r <= 0 ) return;

   xd = 1 - (r << 1);
   yd = 0;
   e = 0;
   x = r;
   y = 0;

   while ( x >= y )
   {
      // Q1
      if ( s & 0x01 ) DrawPixel(x0 + x, y0 - y, color);
      if ( s & 0x02 ) DrawPixel(x0 + y, y0 - x, color);

      // Q2
      if ( s & 0x04 ) DrawPixel(x0 - y, y0 - x, color);
      if ( s & 0x08 ) DrawPixel(x0 - x, y0 - y, color);

      // Q3
      if ( s & 0x10 ) DrawPixel(x0 - x, y0 + y, color);
      if ( s & 0x20 ) DrawPixel(x0 - y, y0 + x, color);

      // Q4
      if ( s & 0x40 ) DrawPixel(x0 + y, y0 + x, color);
      if ( s & 0x80 ) DrawPixel(x0 + x, y0 + y, color);

      y++;
      e += yd;
      yd += 2;
      if ( ((e << 1) + xd) > 0 )
      {
         x--;
         e += xd;
         xd += 2;
      }
   }
}
//---------------------------------------------------------------------------------------
void DrawMesh( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color )
{
   int16_t n, m;

   if ( x2 < x1 ) swap(x1, x2);
   if ( y2 < y1 ) swap(y1, y2);

   for( m = y1; m <= y2; m +=2 )
   {
      for( n = x1; n <= x2; n +=2 )
      {
         DrawPixel(n, m, color);
      }
   }
}
//---------------------------------------------------------------------------------------
void DrawRectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color )
{
   DrawLine(x1, y1, x2, y1, color);
   DrawLine(x1, y2, x2, y2, color);
   DrawLine(x1, y1, x1, y2, color);
   DrawLine(x2, y1, x2, y2, color);
}
//---------------------------------------------------------------------------------------
void DrawRoundRectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t r, uint16_t color )
{
   if ( x2 < x1 ) swap(x1, x2);
   if ( y2 < y1 ) swap(y1, y2);
   if ( r > x2 ) return;
   if ( r > y2 ) return;

   DrawLine(x1+r, y1, x2-r, y1, color);
   DrawLine(x1+r, y2, x2-r, y2, color);
   DrawLine(x1, y1+r, x1, y2-r, color);
   DrawLine(x2, y1+r, x2, y2-r, color);
   Draw_Arc(x1+r, y1+r, r, 0x0C, color);
   Draw_Arc(x2-r, y1+r, r, 0x03, color);
   Draw_Arc(x1+r, y2-r, r, 0x30, color);
   Draw_Arc(x2-r, y2-r, r, 0xC0, color);
}
//---------------------------------------------------------------------------------------
void FillScreen(uint16_t color) 
{
	TFT_FillScreen(color);
}
//---------------------------------------------------------------------------------------
void FillRectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color )
{

   if ( x2 < x1 ) swap(x1, x2);
   if ( y2 < y1 ) swap(y1, y2);
	 TFT_FillWindow(x1, y1, x2, y2, color);
}
//---------------------------------------------------------------------------------------
void FillRoundRectangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t r, uint16_t color )
{
   int16_t  x, y, xd;

   if ( x2 < x1 ) swap(x1, x2);
   if ( y2 < y1 ) swap(y1, y2);
   if ( r<=0 ) return;

   xd = 3 - (r << 1);
   x = 0;
   y = r;

   FillRectangle(x1 + r, y1, x2 - r, y2, color);

   while ( x <= y )
   {
     if( y > 0 )
     {
        DrawLine(x2 + x - r, y1 - y + r, x2+ x - r, y + y2 - r, color);
        DrawLine(x1 - x + r, y1 - y + r, x1- x + r, y + y2 - r, color);
     }
     if( x > 0 )
     {
        DrawLine(x1 - y + r, y1 - x + r, x1 - y + r, x + y2 - r, color);
        DrawLine(x2 + y - r, y1 - x + r, x2 + y - r, x + y2 - r, color);
     }
     if ( xd < 0 )
     {
        xd += (x << 2) + 6;
     }
     else
     {
        xd += ((x - y) << 2) + 10;
        y--;
     }
     x++;
   }
}
//---------------------------------------------------------------------------------------
void DrawCircle( int16_t x0, int16_t y0, int16_t r, uint16_t color )
{
   int16_t x, y, xd, yd, e;

   if ( x0<0 ) return;
   if ( y0<0 ) return;
   if ( r<=0 ) return;

   xd = 1 - (r << 1);
   yd = 0;
   e = 0;
   x = r;
   y = 0;

   while ( x >= y )
   {
      DrawPixel(x0 - x, y0 + y, color);
      DrawPixel(x0 - x, y0 - y, color);
      DrawPixel(x0 + x, y0 + y, color);
      DrawPixel(x0 + x, y0 - y, color);
      DrawPixel(x0 - y, y0 + x, color);
      DrawPixel(x0 - y, y0 - x, color);
      DrawPixel(x0 + y, y0 + x, color);
      DrawPixel(x0 + y, y0 - x, color);

      y++;
      e += yd;
      yd += 2;
      if ( ((e << 1) + xd) > 0 )
      {
         x--;
         e += xd;
         xd += 2;
      }
   }
}
//---------------------------------------------------------------------------------------
void FillCircle( int16_t x0, int16_t y0, int16_t r, uint16_t color )
{
   int16_t  x, y, xd;

   if ( x0<0 ) return;
   if ( y0<0 ) return;
   if ( r<=0 ) return;

   xd = 3 - (r << 1);
   x = 0;
   y = r;

   while ( x <= y )
   {
     if( y > 0 )
     {
        DrawLine(x0 - x, y0 - y,x0 - x, y0 + y, color);
        DrawLine(x0 + x, y0 - y,x0 + x, y0 + y, color);
     }
     if( x > 0 )
     {
        DrawLine(x0 - y, y0 - x,x0 - y, y0 + x, color);
        DrawLine(x0 + y, y0 - x,x0 + y, y0 + x, color);
     }
     if ( xd < 0 )
     {
        xd += (x << 2) + 6;
     }
     else
     {
        xd += ((x - y) << 2) + 10;
        y--;
     }
     x++;
   }
   DrawCircle(x0, y0, r, color);
}
//---------------------------------------------------------------------------------------
void DrawEllipse( int16_t x0, int16_t y0, int16_t rx,int16_t ry, uint16_t color )
{
  int x = 0, y = -ry, err = 2-2*rx, e2;
  float k = 0, radi1 = 0, radi2 = 0;

  radi1 = rx;
  radi2 = ry;

  k = (float)(radi2/radi1);  

  do { 
    DrawPixel((x0-(uint16_t)(x/k)), (y0+y), color);
    DrawPixel((x0+(uint16_t)(x/k)), (y0+y), color);
    DrawPixel((x0+(uint16_t)(x/k)), (y0-y), color);
    DrawPixel((x0-(uint16_t)(x/k)), (y0-y), color);      

    e2 = err;
    if (e2 <= x) {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;     
  }
  while (y <= 0);
}
//---------------------------------------------------------------------------------------
void FillEllipse( int16_t x0, int16_t y0, int16_t rx,int16_t ry, uint16_t color )
{
  int x = 0, y = -ry, err = 2-2*rx, e2;
  float k, radi1 , radi2;

  radi1 = rx;
  radi2 = ry;

  k = (float)(radi2/radi1);

  do 
  {       
    DrawHLine((x0-(uint16_t)(x/k)), (y0+y), (2*(uint16_t)(x/k) + 1), color);
    DrawHLine((x0-(uint16_t)(x/k)), (y0-y), (2*(uint16_t)(x/k) + 1), color);

    e2 = err;
    if (e2 <= x) 
    {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;
  }
  while (y <= 0);
}
//---------------------------------------------------------------------------------------
void DrawTriangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color )
{
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
}
//---------------------------------------------------------------------------------------
void FillTriangle( int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3,  uint16_t color )
{
	int32_t xs, xe;
	int16_t y, ly;

	if (y1 > y2)
	{
		swap(y1, y2); 
		swap(x1, x2);
	}
	if (y2 > y3)
	{
		swap(y3, y2);
		swap(x3, x2);
	}
	if (y1 > y2)
	{
		swap(y1, y2);
		swap(x1, x2);
	}
	
	if(y1 == y3)	// Single line triangles
	{
		xs = xe = x1;
		if(x2 < xs)			xs = x2;
		else if(x2 > xe)	xe = x2;
		if(x3 < xs)			xs = x3;
		else if(x3 > xe)	xe = x3;
		DrawHLine(xs, y1, xe - xs, color);
		return;
	}
	
	// Upper part
	if (y2 == y3) ly = y2;
	else          ly = y2-1;
	
	for(y = y1; y <= ly; y++)
	{
		xs = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		xe = x1 + (x3 - x1) * (y - y1) / (y3 - y1);
		DrawHLine(xs, y, xe - xs, color);
	}
	
	// Lower part
	for(; y <= y3; y++)
	{
		xs = x2 + (x3 - x2) * (y - y2) / (y3 - y2);
		xe = x1 + (x3 - x1) * (y - y1) / (y3 - y1);
		DrawHLine(xs, y, xe - xs, color);
	}
}
//---------------------------------------------------------------------------------------
void DrawArc( int16_t x, int16_t y, int16_t r, int16_t startAngle, int16_t endAngle, int16_t thickness, uint16_t color )
{
  int16_t rDelta = -(thickness/2);
  int16_t px, py, cx, cy;

  startAngle -= 180;
  endAngle   -= 180;

  if (startAngle != endAngle)
    {
      for (int i=0; i<thickness; i++)
	    {
	       px = x + cos((startAngle * 3.14) / 180) * (r + rDelta + i);
	       py = y + sin((startAngle * 3.14) / 180) * (r + rDelta + i);

	       for (int d = startAngle + 1; d < endAngle + 1; d++)
	         {
	           cx = x + cos((d * 3.14) / 180) * (r + rDelta + i);
	           cy = y + sin((d * 3.14) / 180) * (r + rDelta + i);
	           DrawLine(px, py, cx, cy, color);
	           px = cx;
	           py = cy;
	         }
        }
    }
  else
    {
       px = x + cos((startAngle * 3.14) / 180) * (r + rDelta);
       py = y + sin((startAngle * 3.14) / 180) * (r + rDelta);
       cx = x + cos((startAngle * 3.14) / 180) * (r - rDelta);
       cy = y + sin((startAngle * 3.14) / 180) * (r - rDelta);
       DrawLine(px, py, cx, cy, color);
    }
}
//---------------------------------------------------------------------------------------
void DrawPie( int16_t x, int16_t y, int16_t r, int16_t startAngle, int16_t endAngle, uint16_t color )
{
  int16_t px, py, cx, cy;

  startAngle -= 180;
  endAngle   -= 180;

  if (startAngle > endAngle)
    startAngle -= 360;

  px = x + cos((startAngle * 3.14) / 180) * r;
  py = y + sin((startAngle * 3.14) / 180) * r;
  DrawLine(x, y, px, py, color);

  for (int d = startAngle + 1; d < endAngle + 1; d++)
    {
      cx = x + cos((d * 3.14) / 180) * r;
      cy = y + sin((d * 3.14) / 180) * r;
      DrawLine(px, py, cx, cy, color);
      px = cx;
      py = cy;
    }
  DrawLine(x, y, px, py, color);
}
//---------------------------------------------------------------------------------------
void FontSetHSpace( int8_t s )
{
   char_h_space = s;
}
//---------------------------------------------------------------------------------------
void FontSetVSpace( int8_t s )
{
   char_v_space = s;
   LineHeight = tft_font.char_height + char_v_space;
   CharWidth = tft_font.char_width + char_h_space;
}
//---------------------------------------------------------------------------------------
void FontSelect( TFTFontType *font )
{
  tft_font = *font;
  LineHeight = tft_font.char_height + char_v_space;
}
//---------------------------------------------------------------------------------------
// Рисует ASCII символ шрифтом одного размера на позиции х, у.
// Цвет шрифта и фон
// Шрифт должен быть передан с оператором & 
//---------------------------------------------------------------------------------------
void PutChar( int16_t x, int16_t y, char chr, TFTFontType *font, uint16_t fc, uint16_t bc )
{
	uint16_t i, j, k, c, bn, actual_char_width;
	uint8_t b, bt;
	uint32_t index;
	uint32_t color;
	PixelType pixel;

	bt = (uint8_t)chr;

	if (bt < font->start_char || bt > font->end_char) return;

	pixel.y = y;
	bn = font->char_width;
	if ( !bn ) return;
	bn >>= 3;
	if ( font->char_width % 8 ) bn++;
	actual_char_width = (font->widths ? font->widths[bt - font->start_char] : font->char_width);

	if (font->font_type == FONT_TYPE_1BPP)
	{
		 index = (bt - font->start_char)* font->char_height * bn;
		 for( j = 0; j < font->char_height; j++ )			// цикл по оси "y"
		 {
			 pixel.x = x;
			 c = actual_char_width;
			 for( i = 0; i < bn; i++ )									// цикл по ширине символа в байтах
			 {
				 b = font->p[index++]; 
				 for( k = 0; (k<8) && c; k++ )						// цикл по оси "x"
				 {
					 if( b & 0x01 )
					 {
							DrawPixel(pixel.x, pixel.y, fc);
					 }
					 else
					 {
							DrawPixel(pixel.x, pixel.y, bc);
					 }
					 b >>= 1;
					 pixel.x++;
					 c--;
				 }
			 }
			 pixel.y++;
		 }
	}
	else if (font->font_type == FONT_TYPE_2BPP)
	{
		 index = (bt - font->start_char)* font->char_height * bn;
		 for( j = 0; j < font->char_height; j++ )			// цикл по оси "y"
		 {
			 pixel.x = x;
			 c = actual_char_width;
			 for( i = 0; i < bn; i++ )									// цикл по ширине символа в байтах
			 {
				 b = font->p[index++]; 
				 for( k = 0; (k<8) && c; k++ )						// цикл по оси "x"
				 {
					 if( b & 0x80 )
					 {
							DrawPixel(pixel.x, pixel.y, fc);
					 }
					 else
					 {
							DrawPixel(pixel.x, pixel.y, bc);
						 
					 }
					 b <<= 1;
					 pixel.x++;
					 c--;
				 }
			 }
			 pixel.y++;
		 }
	}
	else if (font->font_type == FONT_TYPE_8BPP)
	{
		 index = (bt - font->start_char)* font->char_height * font->char_width;
		 for( j=0; j<font->char_height; j++ )
		 {
				pixel.x = x;
				for( i=0; i<actual_char_width; i++ )
				{
					 b = font->p[index++];
					 color = ((((fc & 0xFF) * b + (bc & 0xFF) * (256 - b)) >> 8) & 0xFF) |							//Blue component
									 ((((fc & 0xFF00) * b + (bc & 0xFF00) * (256 - b)) >> 8)  & 0xFF00) |			//Green component
									 ((((fc & 0xFF0000) * b + (bc & 0xFF0000) * (256 - b)) >> 8) & 0xFF0000);		//Red component
					 DrawPixel(pixel.x, pixel.y, color);
					 pixel.x++;
				}
				index += font->char_width - actual_char_width;
				pixel.y++;
		 }
	}
}
//---------------------------------------------------------------------------------------
// Рисует строку шрифтом одного размера на позиции х, у.
// Цвет шрифта и фон
// Шрифт должен быть передан с оператором & 
//---------------------------------------------------------------------------------------
void PutString( uint16_t x, uint16_t y, char *str, TFTFontType *font, uint16_t fc, uint16_t bc )
{
  uint8_t cw;
  unsigned char chr;

  cur.x = x;
  cur.y = y;

  while ( *str != 0 )
   {
      chr = *str++;

		  if ( chr == '\r' )
        {
          cur.x = 0;
          continue;
        }

	    cw = font->widths ? font->widths[chr - font->start_char] : font->char_width;

		  if ( chr == '\n' )
        {
          cur.y += font->char_height + char_v_space;
          continue;
        }

		  if ((cur.x + cw + char_h_space) > TFT_Opts.Width - 1)
        {
          cur.x = 0;
          cur.y += font->char_height + char_v_space;
        }

		  if ((cur.y + font->char_height + char_v_space) > TFT_Opts.Height - 1)
        {
          cur.x = 0;
          cur.y = 0;
        }

      PutChar(cur.x, cur.y, chr, font, fc, bc);
      cur.x += cw + char_h_space;
   }
}
//---------------------------------------------------------------------------------------
void UTF8rusPutString( uint16_t x, uint16_t y, char *str, TFTFontType *font, uint16_t fc, uint16_t bc )
{
  unsigned char chr;
  uint8_t cw;
 
  cur.x = x;
  cur.y = y;

  while (*str != 0)
   {
      chr = *str++;
      cw = font->widths ? font->widths[chr - font->start_char] : font->char_width;

      if (chr >= 0xC0)
        {
          switch (chr)
            {
              case 0xD0: {
                chr = *str++;
                if (chr == 0x81) { chr = 0xA8; break; }
                if (chr >= 0x90 && chr <= 0xBF) chr = chr + 0x30;
              break;
              }
              case 0xD1: {
                chr = *str++;
                if (chr == 0x91) { chr = 0xB8; break; }
                if (chr >= 0x80 && chr <= 0x8F) chr = chr + 0x70;
              break;
              }
            }
        }

      if ( chr == '\r' )
        {
          cur.x = 0;
          continue;
        }

      if ( chr == '\n' )
        {
					cur.y += font->char_height + char_v_space;
					continue;
				}

      if ((cur.x + cw + char_h_space) > TFT_Opts.Width - 1)
        {
          cur.x = 0;
          cur.y += font->char_height + char_v_space;
        }

	  if ((cur.y + font->char_height + char_v_space) > TFT_Opts.Height - 1)
        {
          cur.x = 0;
          cur.y = 0;
        }

      PutChar(cur.x, cur.y, chr, font, fc, bc);
      cur.x += cw + char_h_space;
   }
}
//---------------------------------------------------------------------------------------
/* Recode russian fonts from UTF-8 to Windows-1251 */
//String utf8rus(String source)
//{
//  int i,k;
//  String target;
//  unsigned char n;
//  char m[2] = { '0', '\0' };
//
//  k = source.length(); i = 0;
//
//  while (i < k) {
//    n = source[i]; i++;
//
//    if (n >= 0xC0) {
//      switch (n) {
//        case 0xD0: {
//          n = source[i]; i++;
//          if (n == 0x81) { n = 0xA8; break; }
//          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
//          break;
//        }
//        case 0xD1: {
//          n = source[i]; i++;
//          if (n == 0x91) { n = 0xB8; break; }
//          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
//          break;
//        }
//      }
//    }
//    m[0] = n; target = target + String(m);
//  }
//return target;
//}
//---------------------------------------------------------------------------------------
void DrawImage( uint16_t x0, uint16_t y0, uint16_t size_x, uint16_t size_y, uint16_t *img )
{
	uint16_t n, m, color;
	uint32_t dt = 0;

  for(m = 0; m < size_y; m++)
	{
		for (n = 0; n < size_x; n++) 
			{
				color = img[n + dt];
				DrawPixel( x0 + n, y0 + m, color );
			}
		dt += size_x;
	}
}
//---------------------------------------------------------------------------------------
//void DrawBMP( int16_t xp, int16_t yp, UG_BMP* bmp )
//{
//   int16_t x,y,xs;
//   UG_U8 r,g,b;
//   uint16_t* p;
//   uint16_t tmp;
//   uint16_t color;

//   if ( bmp->p == NULL ) return;

//   /* Only support 16 BPP so far */
//   if ( bmp->bpp == BMP_BPP_16 )
//   {
//      p = (uint16_t*)bmp->p;
//   }
//   else
//   {
//      return;
//   }

//   xs = xp;
//   for(y = 0; y < bmp->height; y++)
//   {
//      xp = xs;
//      for(x = 0; x < bmp->width; x++)
//      {
//         tmp = *p++;
//         /* Convert RGB565 to RGB888 */
//         r = (tmp>>11)&0x1F;
//         r<<=3;
//         g = (tmp>>5)&0x3F;
//         g<<=2;
//         b = (tmp)&0x1F;
//         b<<=3;
//         color = ((uint16_t)r<<16) | ((uint16_t)g<<8) | (uint16_t)b;
//         DrawPixel( xp++, yp, color );
//      }
//      yp++;
//   }
//}
//---------------------------------------------------------------------------------------
// Рисование ASCII символ пропорционального шрифта с позицией X, Y
// Цвет шрифта плана и фона (шрифт = макс 16 пикселей в ширину)
// Шрифт должен быть передан с оператором & 
// Возвращает: ширину нарисованного символа
//---------------------------------------------------------------------------------------
uint16_t DrawPChar16( uint16_t x, uint16_t y, uint8_t ascii, pFont16 *font, uint16_t vg, uint16_t bg )
{
  uint16_t xn, yn, start_maske, maske, width;
  const uint16_t *wert;

  // Проверка границы символа
  if(ascii<font->first_char) return 0;
  if(ascii>font->last_char) return 0;

  ascii -= font->first_char;
  wert = &font->table[ascii * (font->height + 1)];
  width = wert[0];

    start_maske = 0x01;
    start_maske = start_maske << (width - 1);

    for(yn = 0; yn < font->height; yn++) {
      maske = start_maske;
      for(xn = 0; xn < width; xn++) {
        if((wert[yn + 1] & maske) == 0x00) {
          // Рисование пикселя цветом фона
          DrawPixel(x + xn, y + yn, bg);
        }
        else {
          // Рисование пикселя шрифта
          DrawPixel(x + xn, y + yn, vg);
        }
        maske = (maske>>1);
      }
    }
  return(width);
}
//---------------------------------------------------------------------------------------
// Рисование строки пропорционального шрифта с позицией X, Y
// Цвет шрифта плана и фона (шрифт = макс 16 пикселей в ширину)
// Шрифт должен быть передан с оператором & 
//---------------------------------------------------------------------------------------
void DrawPString16( uint16_t x, uint16_t y,char *ptr, pFont16 *font, uint16_t vg, uint16_t bg )
{
  uint16_t pos, width;

    pos = x;
    while (*ptr != 0) {
      width = DrawPChar16(pos, y, *ptr, font, vg, bg);
      pos += width;
      ptr++;
    }
}
//---------------------------------------------------------------------------------------
// Рисование ASCII символ пропорционального шрифта с позицией X, Y
// Цвет шрифта плана и фона (шрифт = макс 32 пикселя в ширину)
// Шрифт должен быть передан с оператором & 
// Возвращает: ширину нарисованного символа
//---------------------------------------------------------------------------------------
uint16_t DrawPChar32( uint16_t x, uint16_t y, uint8_t ascii, pFont32 *font, uint16_t vg, uint16_t bg )
{
  uint16_t xn, yn, width;
  uint32_t start_maske, maske;
  const uint32_t *wert;

  // Проверка границы символа
  if(ascii<font->first_char) return 0;
  if(ascii>font->last_char) return 0;

  ascii -= font->first_char;
  wert = &font->table[ascii * (font->height + 1)];
  width = wert[0];

    start_maske = 0x01;
    start_maske = start_maske << (width - 1);

    for(yn = 0; yn < font->height; yn++) {
      maske = start_maske;
      for(xn = 0; xn < width; xn++) {
        if((wert[yn + 1] & maske) == 0x00) {
          // Рисование пикселя цветом фона
          DrawPixel(x + xn, y + yn, bg);
        }
        else {
          // Рисование пикселя шрифта
          DrawPixel(x + xn, y + yn, vg);
        }
        maske = (maske>>1);
      }
    }
  return(width);
}
//---------------------------------------------------------------------------------------
// Рисование строку пропорционального шрифта с позицией X, Y
// Цвет шрифта плана и фона (шрифт = макс 32 пикселя в ширину)
// Шрифт должен быть передан с оператором & 
//---------------------------------------------------------------------------------------
void DrawPString32( uint16_t x, uint16_t y,char *ptr, pFont32 *font, uint16_t vg, uint16_t bg )
{
  uint16_t pos, width;

    pos = x;
    while (*ptr != 0) {
      width = DrawPChar32(pos, y, *ptr, font, vg, bg);
      pos += width;
      ptr++;
    }
}
//---------------------------------------------------------------------------------------
/*
void DrawLoadBMP(uint16_t x, uint16_t y, char *sname)
{
	uint16_t i, h;
	uint32_t index=0, width=0, height=0, bitpixel=0;
	FRESULT res; 										//FatFs function common result code
	uint32_t bytesread;
	uint32_t tmpcolor;
	uint8_t *bufbmp = NULL;

	if(f_open(&MyFile, sname, FA_READ)!=FR_OK)
	{
		TFT_FillScreen(C_RED);
		Error_Handler();
	}
	else
	{
		bufbmp = (uint8_t*) malloc(100);
		if(f_read(&MyFile, bufbmp, 30, (UINT *)&bytesread)!=FR_OK)
		{
			TFT_FillScreen(C_RED);
			Error_Handler();
		}
		else
		{
			index=bufbmp[10];			//адрес начала данных в файле
			index|=bufbmp[11]<<8;
			index|=bufbmp[12]<<16;
			index|=bufbmp[13]<<24;
			width=bufbmp[18];			//ширина растра
			width|=bufbmp[19]<<8;
			width|=bufbmp[20]<<16;
			width|=bufbmp[21]<<24;
			height=bufbmp[22];			//высота растра
			height|=bufbmp[23]<<8;
			height|=bufbmp[24]<<16;
			height|=bufbmp[25]<<24;
			bitpixel=bufbmp[28];		//формат пикселя (бит/пиксель)
			bitpixel|=bufbmp[29]<<8;
			for(h=0; h<height; h++)
			{
				for(i=0; i<width; i++)
				{
					switch(bitpixel)
					{
						case 24:
							f_lseek(&MyFile, index+((height-h-1)*width*3)+(i*3));
							res = f_read(&MyFile, bufbmp, 3, (void*)&bytesread);
							if((bytesread==0)||(res!=FR_OK))
							{
								Error_Handler();
							}
							else
							{
								tmpcolor=bufbmp[0];
								tmpcolor|=bufbmp[1]<<8;
								tmpcolor|=bufbmp[2]<<16;
							}
							break;
					}
					if(((i+x)<width)|((h+y)<height))
					DrawPixel(i+x, h+y, (uint16_t)convert24to16(tmpcolor));
				}
			}
			f_close(&MyFile);
		}
		free(bufbmp);
	}
}
*/

//---------------------------------------------------------------------------------------
void ConsolePutChar( char chr, uint16_t fc, uint16_t bc )
{
	int x,y;

	if ((cur.x) >= console.max_pos)
	{
		cur.x = 0;
		cur.y += 1;
	}

	if ((cur.y) >= console.max_lines)
	{
		cur.x = 0;
		cur.y = 0;
	}
	x = console.x_start + cur.x * (tft_font.char_width + char_h_space);
	y = console.y_start + cur.y * (tft_font.char_height+ char_v_space);
	PutChar( x, y, chr, &tft_font, fc, bc );
	cur.x++;
}
//---------------------------------------------------------------------------------------
void ConsolePutString( char* str, uint16_t fc, uint16_t bc )
{
  char chr;

  while ( *str != 0 )
   {
      chr = *str++;

		if ( chr == '\r' )
        {
          cur.x = 0;
          continue;
        }

		if ( chr == '\n' )
        {
		  cur.y += 1;
          continue;
        }

      if ((cur.x) > console.max_pos)
        {
          cur.x = 0;
          cur.y += 1;
        }

	  if ((cur.y) > console.max_lines)
        {
          cur.x = 0;
          cur.y = 0;
        }

      ConsolePutChar(chr, fc, bc);
   }
}
//---------------------------------------------------------------------------------------
void ConsolePutStringln(char* str, uint16_t fc, uint16_t bc) 
{
	if ((cur.y) >= console.max_lines)
	{
		cur.x = 0;
		cur.y = 0;
	}
	ConsolePutString(str, fc, bc);
	cur.y++;
	cur.x = 0;
}
//---------------------------------------------------------------------------------------
void PutString_Hex8( uint8_t data, uint16_t fc, uint16_t bc )
{
	ConsolePutChar((hex_decode[(data >> 4) & 0x0F]), fc, bc);
	ConsolePutChar((hex_decode[data & 0x0F]), fc, bc);
}
//---------------------------------------------------------------------------------------
void PutString_Hex16( uint16_t data, uint16_t fc, uint16_t bc )
{
	uint16_t i;

	for (i = 12; i; i -= 4) ConsolePutChar((hex_decode[(data >> i) & 0x0F]), fc, bc);
	ConsolePutChar((hex_decode[data & 0x0F]), fc, bc);
}
//---------------------------------------------------------------------------------------
void PutString_Hex32( uint32_t data, uint16_t fc, uint16_t bc )
{
	uint32_t i;

	for (i = 28; i; i -= 4) ConsolePutChar((hex_decode[(data >> i) & 0x0F]), fc, bc);
	ConsolePutChar((hex_decode[data & 0x0F]), fc, bc);
}
//---------------------------------------------------------------------------------------
void PutString_dec_xx( uint8_t data, uint16_t fc, uint16_t bc )
{
	ConsolePutChar((hex_decode[((data % 100) / 10) & 0x0F]), fc, bc );
	ConsolePutChar((hex_decode[((data % 100) % 10) & 0x0F]), fc, bc );
}
//---------------------------------------------------------------------------------------
void PutString_dec_xxx( uint16_t data, uint16_t fc, uint16_t bc )
{
	ConsolePutChar((hex_decode[(data / 100) & 0x0F]), fc, bc);
	ConsolePutChar((hex_decode[((data % 100) / 10) & 0x0F]), fc, bc);
	ConsolePutChar((hex_decode[((data % 100) % 10) & 0x0F]), fc, bc);
}
//---------------------------------------------------------------------------------------
void PutString_dec_xxxx( uint16_t data, uint16_t fc, uint16_t bc )
{
	ConsolePutChar((hex_decode[(data / 1000) & 0x0F]), fc, bc);
	ConsolePutChar((hex_decode[((data % 1000) / 100) & 0x0F]), fc, bc);
	ConsolePutChar((hex_decode[((data % 1000) % 100) / 10 & 0x0F]), fc, bc);
	ConsolePutChar((hex_decode[((data % 1000) % 100) % 10 & 0x0F]), fc, bc);
}
//---------------------------------------------------------------------------------------
void PutString_Intflag(int32_t a, uint8_t flag, uint16_t fc, uint16_t bc )
{
	uint32_t b;
	int8_t i;

	if (a < 0)
	{
		ConsolePutChar(('-'), fc, bc);
		a = -a;
	}
	for (i = 9; i >= 0; i--)
	{
		b = a / digits[i];
		if ((flag>i) || ( b))
		{
			ConsolePutChar(('0' + b), fc, bc);
			flag = i;
		}
		a = a % digits[i];
	}
}
//---------------------------------------------------------------------------------------
void PutString_Int( int32_t a, uint16_t fc, uint16_t bc )
{
	PutString_Intflag(a, 1, fc, bc);
}
//---------------------------------------------------------------------------------------
void PutString_Float( float a, uint8_t digit_after_point, uint16_t fc, uint16_t bc )
{
  float b;

	b = a + (0.5001 / digits[digit_after_point]);
	PutString_Intflag(b, 1, fc, bc);
	if (b < 0)
		b = -b;
	ConsolePutChar(('.'), fc, bc);
	b = (b - ((uint32_t)b)) * (digits[digit_after_point]);
	PutString_Intflag(b, digit_after_point, fc, bc);
}
//---------------------------------------------------------------------------------------
/*
void PutString_Int( int32_t num, TFT_FONT_t *font, uint16_t fc, uint16_t bc )
{
	char str[10]; // 10 chars max for INT32_MAX
	int i = 0;

	if (num < 0) {
		ConsolePutChar(('-'), font, fc, bc);
		num *= -1;
	}
	do str[i++] = num % 10 + '0'; while ((num /= 10) > 0);
	while (i) ConsolePutChar(str[--i], font, fc, bc);
}
*/
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
