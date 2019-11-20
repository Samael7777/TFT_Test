/*
 *
 *
*/

#ifndef __FONTS_H
#define __FONTS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

//--------------------------------------------------------------
// Структура шрифта одного размера
//-------------------------------------------------------------- 
typedef enum
{
	FONT_TYPE_1BPP,
	FONT_TYPE_2BPP,
	FONT_TYPE_8BPP,
} FONT_TYPE;

typedef struct
{
   unsigned char* p;
   FONT_TYPE font_type;
   int16_t char_width;
   int16_t char_height;
   uint16_t start_char;
   uint16_t end_char;
   uint8_t  *widths;
} TFTFontType;

//--------------------------------------------------------------
// Структура пропорционального шрифта (не более 16 пикселей шириной)
//--------------------------------------------------------------
typedef struct _pFont16_t
{
  const uint16_t *table; // Таблица с данными
  uint16_t height;       // Высота символа (в пикселях)
  uint16_t first_char;   // Первый символ  (Ascii код)
  uint16_t last_char;    // Последний символ (Ascii код)
} pFont16;

//--------------------------------------------------------------
// Структура пропорционального шрифта (не более 32 пикселей шириной)
//--------------------------------------------------------------
typedef struct _pFont32_t
{
  const uint32_t *table; // Таблица с данными
  uint16_t height;       // Высота символа (в пикселях)
  uint16_t first_char;   // Первый символ  (Ascii код)
  uint16_t last_char;    // Последний символ (Ascii код)
} pFont32;

//--------------------------------------------------------------
// Активация различных шрифтов
// (Неиспользуемое закоментировать)
// Для всех используемых шрифтов должны быть соответствующие С-файлы
// которые необходимо подключить к проекту
//--------------------------------------------------------------

extern  TFTFontType CONSOLAS_12x22;
extern  TFTFontType SEVENSEG_NUM_32X50;
extern  TFTFontType SEVENSEG_NUM_64X100;

//extern  TFT_FONT_t ARIAL_SEVENSEG_NUM_32X50;
//extern  TFT_FONT_t FONT_4X6;
//extern  TFT_FONT_t FONT_5X8;
//extern  TFT_FONT_t FONT_5X12;
//extern  TFT_FONT_t FONT_6X8;
//extern  TFT_FONT_t FONT_6X10;
//extern  TFT_FONT_t FONT_7X12;
//extern  TFT_FONT_t FONT_8X8;
//extern  TFT_FONT_t FONT_8X12;
//extern  TFT_FONT_t FONT_8X12_CYR;
//extern  TFT_FONT_t FONT_8X14;
//extern  TFT_FONT_t FONT_8X14_CYR;
//extern  TFT_FONT_t FONT_10X16;
//extern  TFT_FONT_t FONT_12X16;
//extern  TFT_FONT_t FONT_16X16_CYR;
//extern  TFT_FONT_t FONT_12X20;
//extern  TFT_FONT_t FONT_16X26;
//extern  TFT_FONT_t FONT_22X36;
//extern  TFT_FONT_t FONT_24X40;
//extern  TFT_FONT_t FONT_32X53;
//extern  TFT_FONT_t FONT_20X22_CYR;
//extern  TFT_FONT_t FONT_22X20_ITALIC;
//extern  TFT_FONT_t FONT_21X26;
//extern  TFT_FONT_t FONT_34X53_CYR;


//extern  TFT_FONT_t INCONSOLA_24X32;
//extern  TFT_FONT_t TIMES_15X25_CYR;
//extern  TFT_FONT_t TIMES_16X25_CYR;

//extern  TFT_FONT_t ARIAL_7X10;
//extern  TFT_FONT_t ARIAL_8X13;
//extern  TFT_FONT_t ARIAL_10X15;
//extern  TFT_FONT_t ARIAL_11X18;
//extern  TFT_FONT_t ARIAL_13X19;
//extern  TFT_FONT_t ARIAL_14X22;
//extern  TFT_FONT_t ARIAL_16X25;
//extern  TFT_FONT_t ARIAL_18X27;


#ifdef __cplusplus
}
#endif

#endif	/* __FONTS_H */
