#define _CRT_SECURE_NO_WARNINGS

#include "GUI.h"
#include "MenuMode.h"

GuiModeType CurrentMode;



//Прототипы

void SetEditMode(void* param);
void SetPCMode(void);
void SetAutoMode(void);
void SetManualMode(void);
void SetFirmwareMode(void);

//**********Локальные функции************
void StatusbarInit(void);

void GuiProcess(CommandType cmd)
{
	switch (CurrentMode)
	{
		case GUI_MENU:
		{
			NavigateMenu(cmd);
			break;
		}
		default:
			break;
	}
}

void GuiInit(void)
{
	//Инициализация дисплея
	TFT_Init();
	TFT_Rotate(Orientation_Landscape_1);
	FillScreen(BKG_COLOR);	//Очистка экрана
	//Инициализация статусбара
	StatusbarInit();
	InitMenuStructures();
	GuiSetMode(GUI_MENU);

}

void StatusbarInit(void)
{
	FillRectangle(0, 0, TFT_GetWidth(), SBAR_HEIGHT, SBAR_BG_COLOR);		//Зона статусбара
}



void GuiSetMode(GuiModeType mode)
{
	switch (mode)
	{
		case GUI_MENU:
		{
			SetMenuMode();
			break;
		}
		case GUI_AUTO:
		{
			//SetAutoMode();
			break;
		}
		case GUI_MANUAL:
		{
			//SetManualMode();
			break;
		}
		case GUI_FIRMWARE:
		{
			//SetFirmwareMode();
			break;
		}
		default:
			break;
	}	
}

GuiModeType GuiGetMode(void)
{
	return CurrentMode;
}

void GuiDeinit(void)
{
	TFT_Deinit();
}

