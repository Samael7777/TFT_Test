

#include <iostream>
#include <Windows.h>
#include <string>
#include "..\TFT_Test\Font\Font.h"
#include "..\TFT_Test\tft\TFT_Lib.h"
#include "GUI/GUI.h"

#define FONT SEVENSEG_NUM_32X50

int main()
{
	GuiInit();

	std::cin.get();
	TFT_Deinit();
}

