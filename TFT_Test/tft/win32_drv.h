#pragma once
/**
 *  win32_drv.h
 * 
 */
#include <stdint.h>

#ifndef __WIN32_DRV_H
#define __WIN32_DRV_H


#define TFT_WIDTH       ((uint16_t)320)
#define TFT_HEIGHT      ((uint16_t)480)
#define TFT_PIXEL_COUNT ((uint32_t)(TFT_WIDTH * TFT_HEIGHT))        // 153600

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;

typedef enum {
	Orientation_Portrait_1,
	Orientation_Portrait_2,
	Orientation_Landscape_1,
	Orientation_Landscape_2
} Orientation_t;

typedef enum {
	Landscape,
	Portrait
} TFT_Orientation;

typedef struct {
	uint16_t Width;
	uint16_t Height;
	Orientation_t orient;
	TFT_Orientation orientation; // 1 = portrait; 0 = landscape
} OptionsType;

//Commands

uint16_t TFT_GetWidth(void);
uint16_t TFT_GetHeight(void);
//void SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void TFT_Rotate(Orientation_t orientation);
//void TFT_Fill(uint16_t color);
void TFT_FillWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void TFT_FillScreen(uint16_t color);
//void TFT_Flood(uint16_t color, uint32_t len);
void TFT_Reset(void);
void Drv_init(void);
void Drv_deinit(void);




#endif /* __WIN32_DRV_H */
