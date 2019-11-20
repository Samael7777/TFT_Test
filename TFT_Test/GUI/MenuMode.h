
#ifndef __MENUMODE_H
#define __MENUMODE_H

#include <stdint.h>
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
	MenuItemType *item;			//Ссылка на первый пункт меню
} MenuType;

enum MenuAction
{
	ACT_EXEC,
	ACT_EDIT,
	ACT_MENU,
	ACT_BACK
};

void InitMenuStructures(void);	
void NavigateMenu(CommandType com);
void SetMenuMode(void);

#endif //__MENUMODE_H


