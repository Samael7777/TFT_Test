#ifndef __GUI_H
#define __GUI_H

#include "..\tft\TFT_Lib.h"
#include <stdio.h>


//Основные параметры

#define MAIN_FONT		CONSOLAS_12x22	//Основной шрифт
#define FONT_COLOR		C_WHITE			//Цвет текста
#define BKG_COLOR		C_BLUE			//Цвет фона
#define SEL_COLOR		C_WHITE			//Цвет выделенного текста
#define SEL_BG_COLOR	C_RED			//Цвет фона выделения

constexpr auto LINE_VERT_INT =	0;		//Расстояние между соседними строками в пикселях;
constexpr auto BORDER =			20;		//Отступ от краев экрана в пикселях;
constexpr auto MENU_SPACE =		10;		//Отступ от названия меню;
constexpr auto HEADER_HEIGHT =	30;		//Высота хедера в пикселях;

//Описание пункта меню
typedef struct MenuItem
{
	char*		Text;		//Название пункта меню
	uint16_t	id = 0;		//Id пункта меню
	void* child = NULL;		//Ссылка на меню-потомка
	void*	prev = NULL;	//Ссылка на предыдущий пункт меню
	void*	next = NULL;	//Ссылка на следующий пункт меню
	void* Exec = NULL;		//Ссылка на действие
} MenuItem_t;

//Описание заголовка меню
typedef struct Menu
{
	char*	title;				//Название меню
	void*	parent = NULL;		//Ссылка на меню-предка
	void*	item;					//Ссылка на первый пункт меню
} Menu_t;

//Прототипы функций
void GuiInit(void);

#endif