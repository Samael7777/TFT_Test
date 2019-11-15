#ifndef __GUI_H
#define __GUI_H

#include "TFT_Lib.h"

//Основные параметры

#define MAIN_FONT		CONSOLAS_12x22	//Основной шрифт
#define FONT_COLOR		C_WHITE			//Цвет текста
#define BKG_COLOR		C_BLUE			//Цвет фона
#define SEL_COLOR		C_WHITE			//Цвет выделенного текста
#define SEL_BG_COLOR	C_RED			//Цвет фона выделения

constexpr auto LINE_VERT_INT =	1;		//Расстояние между соседними строками в пикселях;
constexpr auto BORDER =			10;		//Отступ от краев экрана в пикселях;
constexpr auto MENU_SPACE =		10;		//Отступ от названия меню;
constexpr auto HEADER_LINES =	1;		//Количество строк в хедере;

//Описание пункта меню
typedef struct MenuItem
{
	char*	Text;					//Название пункта меню
	struct	MenuRoot* parent;		//Ссылка на меню-предка
	struct	MenuRoot* child;		//Ссылка на меню-потомка
	void*	Exec;					//Ссылка на действие
} MenuItemType;

//Описание заголовка меню
typedef struct MenuRoot
{
	char* title;					//Название меню
	struct MenuItem* element[];		//Ссылка на первый пункт меню
} MenuRootType;


//Структура навигации по интерфейсу
typedef enum
{
	KEY_LEFT,						
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_EXEC,
	KEY_ESC,
	KEY_F1,
	KEY_F2,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_SH,
	KEY_ST,
	KEY_FAN,
	KEY_Z1,
	KEY_Z2,
	KEY_Z3,
	KEY_PWR
} KeyPressedType;

//Структура режимов работы
typedef enum
{
	MODE_MENU,						//Режим главного меню
	MODE_SET_PARAM,					//Режим установки параметра
	MODE_MANUAL_SOLDING,			//Режим ручной пайки
	MODE_PROFILE_SOLDING,			//Режим пайки по профилю
	MODE_PC_CONTROL,				//Режим управления с ПК
	MODE_FIRMWARE_UPDATE			//Режим обновления прошивки
} ModeType;


//Константы

const int LINE_HEIGHT = MAIN_FONT.char_height + LINE_VERT_INT;			//Высота строки в пикселях
const int HEADER_HEIGHT = LINE_HEIGHT * HEADER_LINES;					//Высота хедера в пикселях
const int MENU_TITLE_POS_Y = HEADER_HEIGHT + MENU_SPACE;				//Позиция начала заголовка меню по вертикали
const int MENU_BODY_POS_Y = MENU_TITLE_POS_Y + MENU_SPACE;				//Позиция начала тела меню по вертикали


//Прототипы функций

void GuiInit(void);					//Инициализация интерфейса
//void UpdateTime(void);				//Обновить время и дату
//void SetMode(ModeType mode);
//void Navigate(KeyPressedType key);

#endif