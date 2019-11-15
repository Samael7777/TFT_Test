#include "GUI.h"

int LCDHeight, LCDWidth;
int MaxLines;			//Максимальное количество пунктов меню для вывода
int MaxLineLenght;		//Максимальное количество символов в строке
char* DisplayBuff;		//Буфер для вывода меню

MenuItemType* Selected;		//Ссылка на выбранный пункт меню
int index = 0;				//Номер 

//Главное меню
MenuItemType MMProfiles = { (char*)"Пайка по профилю",NULL,NULL,NULL,NULL,NULL };
MenuItemType MMManual = { (char*)"Пайка в ручном режиме",NULL,NULL,NULL,NULL,NULL };
MenuItemType MMPCControl = { (char*)"Управление с ПК",NULL,NULL,NULL,NULL,NULL };
MenuItemType MMSettings = { (char*)"Настройки",NULL,NULL,NULL,NULL,NULL };
MenuRootType MainMenuTitle = { (char*)"Главное меню",NULL };
MenuItemType* MainMenuBody

void MenuInit(void);			//Инициализация меню
void CleanMenuArea(void);		//Очистка области меню
void

void GuiInit(void)
{
	//Инициализация дисплея
	TFT_Init();
	TFT_Rotate(Orientation_Landscape_1);
	//Текущие размеры экрана
	LCDHeight = TFT_GetHeight();
	LCDWidth = TFT_GetWidth();
	MaxLines = (LCDHeight - MENU_BODY_POS_Y) / LINE_HEIGHT;
	
	MenuInit(); //Инициализация меню
	
	FillScreen(BKG_COLOR);	//Очистка экрана
	DrawLine(BORDER / 2, HEADER_HEIGHT, LCDWidth - BORDER / 2, HEADER_HEIGHT, FONT_COLOR);

}

void MenuInit(void)
{
	//Настройка связей главного меню


void CleanMenuArea(void)
{
	FillRectangle(0, MENU_TITLE_POS_Y, LCDWidth, LCDHeight, BKG_COLOR);
}