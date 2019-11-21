#ifndef __GUI_H
#define __GUI_H

#include "..\tft\TFT_Lib.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif



	//Основные параметры

#define MAIN_FONT			CONSOLAS_12x22	//Основной шрифт
#define FONT_COLOR			0x1354 			//Цвет текста
#define BKG_COLOR			C_WHITE			//Цвет фона
#define SEL_COLOR			C_WHITE			//Цвет выделенного текста
#define SEL_BG_COLOR		0x1354 			//Цвет фона выделения
#define SBAR_BG_COLOR		0x1354			//Фон статусбара
#define SBAR_F_COLOR		C_WHITE			//Цвет шрифта статусбара

#define LINE_VERT_INT		0				//Расстояние между соседними строками в пикселях;
#define BORDER				20				//Отступ от краев экрана в пикселях;
#define MENU_SPACE			10				//Отступ от названия меню;
#define SBAR_HEIGHT			44				//Высота статусбара в пикселях;


//Описание команд меню
	typedef enum Command
	{
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_ESC,
		KEY_ENT,
		KEY_Z1,
		KEY_Z2,
		KEY_Z3,
		KEY_FAN
	} CommandType;

	typedef enum GuiMode		//Режим работы GUI
	{
		GUI_MENU,
		GUI_PC,
		GUI_AUTO,
		GUI_MANUAL,
		GUI_FIRMWARE
	} GuiModeType;

	//Структура статуса хедера
	typedef struct
	{
		bool fan;
		bool z1;
		bool z2;
		bool z3;
	} StatusBarDataType;

	//Прототипы функций
	void GuiInit(void);							//Инициализация
	void GuiDeinit(void);						//Деинициализация
	void GuiProcess(CommandType cmd);			//Обработка команд
	void UpdateTime(void);						//Обновить время
	void SetSBarData(StatusBarDataType* sbd);	//Установить параметры статусбара
	GuiModeType GuiGetMode(void);
	void GuiSetMode(GuiModeType mode);
	void SetMenuMode(void);						//Включение режима меню
#ifdef __cplusplus
}
#endif

#endif
