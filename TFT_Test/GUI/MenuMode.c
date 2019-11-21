#define _CRT_SECURE_NO_WARNINGS

#include "GUI.h"
#include "MenuMode.h"
#include <stdlib.h>
#include <string.h>

//Описание пункта меню
typedef struct MenuItem
{
	char* text;				//Название пункта меню
	void* child;			//Ссылка на меню-потомка
	void* parent;			//Ссылка на заголовок меню
	void* prev;				//Ссылка на предыдущий пункт меню
	void* next;				//Ссылка на следующий пункт меню	
	enum MenuAction action;		//Определение действия
	void* param;			//Параметры действия
} MenuItemType;

//Описание заголовка меню
typedef struct Menu
{
	char* title;				//Название меню
	void* parent;				//Ссылка на меню-предка
	MenuItemType* item;			//Ссылка на первый пункт меню
} MenuType;

//Действия меню
enum MenuAction
{
	ACT_EXEC,
	ACT_EDIT,
	ACT_NEXT,
	ACT_BACK
};

//Структура выделения пункта меню
struct
{
	int pos;				//Позиция выделения (номер строки)
	MenuItemType* ptr;		//Указатель на выделенный пункт меню
} sel;


int MaxLines;											//Максимальное количество пунктов меню для вывода
int MaxChars;											//Максимальное количество символов в строке
int MenuTitle_pos_x, MenuTitle_pos_y, MenuTitle_height;	//Положение заголовка меню
int MenuBody_pos_x, MenuBody_pos_y;						//Положение тела меню								
int LCD_Width, LCD_Height;								//Размеры экрана

MenuItemType* fl_ptr;									//Указатель на первый отображаемый пункт меню


//Главное меню
MenuType m1;
MenuItemType m1_1, m1_2, m1_3, m1_4;
//Меню Настройки
MenuType m2;
MenuItemType m2_1, m2_2, m2_3;




void SetMenu(MenuType* menu);			//Показать заголовок окна и установить указатель меню на первый пункт
void ShowMenuBody(void);				//Показать меню
void ShowSelection(bool status);		//Визуализация выделения (установить, снять)
void ProcessAction(MenuItemType* mi);	//Обработка действий меню



void inline InitMenu(MenuType* menu, char* title, void* parent, MenuItemType* item);
void inline InitMenuItem(MenuItemType* menuitem, char* text, void* child, void* parent, void* prev, void* next, enum MenuAction action, void* param);

void InitMenuStructures(void)
{
	//Настройкаглавного меню
	InitMenu(&m1, (char*)"Главное меню", NULL, &m1_1);
	InitMenuItem(&m1_1, (char*)"Пайка по профилю", NULL, &m1, NULL, &m1_2, ACT_EXEC, NULL);
	InitMenuItem(&m1_2, (char*)"Пайка в ручном режиме", NULL, &m1, &m1_1, &m1_3, ACT_EXEC, NULL);
	InitMenuItem(&m1_3, (char*)"Управление с ПК", NULL, &m1, &m1_2, &m1_4, ACT_EXEC, NULL);
	InitMenuItem(&m1_4, (char*)"Настройки", &m2, &m1, &m1_3, NULL, ACT_NEXT, NULL);

	   	  
	//Настройка меню Настройки
	InitMenu(&m2, (char*)"Настройки", &m1, &m2_1);
	InitMenuItem(&m2_1, (char*)"Настройки времени", NULL, &m2, NULL, &m2_2, ACT_EXEC, NULL);
	InitMenuItem(&m2_2, (char*)"Сброс всех настроек", NULL, &m2, &m2_1, &m2_3, ACT_EXEC, NULL);
	InitMenuItem(&m2_3, (char*)"Назад", NULL, &m2, &m2_2, NULL, ACT_BACK, NULL);
}

void inline InitMenu(MenuType* menu, char* title, void* parent, MenuItemType* item)
{
	menu->item = item;
	menu->parent = parent;
	menu->title = title;
}

void inline InitMenuItem(MenuItemType* menuitem, char* text, void* child, void* parent, void* prev, void* next, enum MenuAction action, void* param)
{
	menuitem->action = action;
	menuitem->child = child;
	menuitem->next = next;
	menuitem->param = param;
	menuitem->parent = parent;
	menuitem->prev = prev;
	menuitem->text = text;
}


void SetMenuMode(void)
{
	LCD_Height = TFT_GetHeight();
	LCD_Width = TFT_GetWidth();
	//Параметры шрифта
	FontSelect(&MAIN_FONT);
	FontSetVSpace(LINE_VERT_INT);
	FontSetHSpace(0);
	//Положение элементов меню
	MenuTitle_pos_y = SBAR_HEIGHT + LINE_VERT_INT + 10;
	MenuTitle_height = MAIN_FONT.char_height + LINE_VERT_INT + 1;
	MenuBody_pos_y = MenuTitle_pos_y + MenuTitle_height + 10;
	//Предельные размеры

	ConsoleSetArea(BORDER, MenuBody_pos_y, LCD_Width - BORDER, LCD_Height - BORDER);
	MaxLines = ConsoleGetMaxLines();
	MaxChars = ConsoleGetMaxChars();
	SetMenu(&m1);
	ShowMenuBody();
	ShowSelection(true);
}


void SetMenu(MenuType *menu)
{
	FillRectangle(0, MenuTitle_pos_y, LCD_Width, MenuBody_pos_y, BKG_COLOR); //Очистка области под заголовок
	MenuTitle_pos_x = (LCD_Width - strlen(menu->title) * MAIN_FONT.char_width) / 2; //Выравнивание заголовка по середине экрана
	PutString(MenuTitle_pos_x, MenuTitle_pos_y, menu->title, &MAIN_FONT, FONT_COLOR, BKG_COLOR);
	DrawHLine(MenuTitle_pos_x, (MenuTitle_pos_y + ConsoleGetLineHeight() + 1), (strlen(menu->title) * MAIN_FONT.char_width), FONT_COLOR);
	if (menu->item != NULL)
	{
		sel.ptr = (MenuItemType*)menu->item;
		sel.pos = 0;
		fl_ptr = menu->item;
	}
}


void ShowMenuBody()
{
	uint16_t fc, bc;
	uint16_t pos;
	ConsoleClean(BKG_COLOR); //Очистка области тела меню
	CursorSet(0, 0);
	pos = 0;
	MenuItemType *ptr = (MenuItemType*)fl_ptr;
	while ((ptr != NULL) && (pos < MaxLines))
	{
		fc = FONT_COLOR;
		bc = BKG_COLOR;
		CursorSet(0, pos);
		ConsolePutString(ptr->text, fc, bc);
		ptr = (MenuItemType*)ptr->next;
		pos++;
	}
	ShowSelection(true);

}

void ShowSelection(bool status)
{
	int fc, bc;

	if (status)
	{
		fc = SEL_COLOR;
		bc = SEL_BG_COLOR;
	}
	else
	{
		fc = FONT_COLOR;
		bc = BKG_COLOR;
	}
	ConsoleMarkLine(sel.ptr->text, sel.pos, fc, bc);
}

void NavigateMenu(CommandType com)
{
	switch (com)
	{
	case KEY_DOWN:
		if ((MenuItemType*)(sel.ptr->next) != NULL)
		{
			ShowSelection(false);
			sel.ptr = (MenuItemType*)(sel.ptr->next);
			sel.pos++;
			if (sel.pos >= MaxLines)
			{
				sel.pos = MaxLines-1;
				if (fl_ptr->next != NULL)
				{
					fl_ptr = (MenuItemType*)fl_ptr->next;
					ShowMenuBody();
				}
			}
			ShowSelection(true);
		}
		break;
	case KEY_UP:
		if ((MenuItemType*)(sel.ptr->prev) != NULL)
		{
			ShowSelection(false);
			sel.ptr = (MenuItemType*)(sel.ptr->prev);
			sel.pos--;
			if (sel.pos < 0)
			{
				sel.pos = 0;
				if (fl_ptr->prev != NULL)
				{
					fl_ptr = (MenuItemType*)fl_ptr->prev;
					ShowMenuBody();
				}
			}
			ShowSelection(true);
		}
		break;
	case KEY_ENT:
		ProcessAction(sel.ptr);
		break;
	default:
		break;
	}
}

void ProcessAction(MenuItemType* mi)
{
	if ((mi->action) == NULL) return;
	switch (mi->action)
	{
		case ACT_NEXT:
			if ((mi->child) != NULL)
			{
				SetMenu((MenuType*)(mi->child));
				ShowMenuBody();
			}
			break;
		case ACT_BACK:
			if ((mi->parent) != NULL)
			{
				MenuType* m = (MenuType *)(mi->parent);
				SetMenu(m->parent);
				ShowMenuBody();
			}
			break;
		default: break;
	}
}