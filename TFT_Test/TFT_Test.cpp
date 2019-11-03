

#include <iostream>
#include <Windows.h>
#include <string>
#include "TFT_Lib.h"
#include "Font.h"

#define MAIN_FONT CONSOLAS_12x22

int main()
{
	uint16_t x, y;
	uint16_t str_w;
	char* txt = (char*)"Главное меню";
	
	TFT_Init();
	TFT_Rotate(Orientation_Landscape_1);
	str_w = strlen(txt) * MAIN_FONT.char_width;
	x = (TFT_GetWidth() - str_w) / 2;
	y = 5;

	

	FillScreen(C_BLUE);
	PutString(x, y, txt, &MAIN_FONT, C_WHITE, C_BLUE);


	std::cin.get();
	TFT_Deinit();
}

