#define _CRT_SECURE_NO_WARNINGS

#include "GUI.h"
#include "MenuMode.h"
#include <stdlib.h>
#include <string.h>

//�������� ������ ����
typedef struct MenuItem
{
	char* text;				//�������� ������ ����
	void* child;			//������ �� ����-�������
	void* parent;			//������ �� ��������� ����
	void* prev;				//������ �� ���������� ����� ����
	void* next;				//������ �� ��������� ����� ����	
	enum MenuAction action;		//����������� ��������
	void* param;			//��������� ��������
} MenuItemType;

//�������� ��������� ����
typedef struct Menu
{
	char* title;				//�������� ����
	void* parent;				//������ �� ����-������
	MenuItemType* item;			//������ �� ������ ����� ����
} MenuType;

//�������� ����
enum MenuAction
{
	ACT_EXEC,
	ACT_EDIT,
	ACT_NEXT,
	ACT_BACK
};

//��������� ��������� ������ ����
struct
{
	int pos;				//������� ��������� (����� ������)
	MenuItemType* ptr;		//��������� �� ���������� ����� ����
} sel;


int MaxLines;											//������������ ���������� ������� ���� ��� ������
int MaxChars;											//������������ ���������� �������� � ������
int MenuTitle_pos_x, MenuTitle_pos_y, MenuTitle_height;	//��������� ��������� ����
int MenuBody_pos_x, MenuBody_pos_y;						//��������� ���� ����								
int LCD_Width, LCD_Height;								//������� ������

MenuItemType* fl_ptr;									//��������� �� ������ ������������ ����� ����


//������� ����
MenuType m1;
MenuItemType m1_1, m1_2, m1_3, m1_4;
//���� ���������
MenuType m2;
MenuItemType m2_1, m2_2, m2_3;




void SetMenu(MenuType* menu);			//�������� ��������� ���� � ���������� ��������� ���� �� ������ �����
void ShowMenuBody(void);				//�������� ����
void ShowSelection(bool status);		//������������ ��������� (����������, �����)
void ProcessAction(MenuItemType* mi);	//��������� �������� ����



void inline InitMenu(MenuType* menu, char* title, void* parent, MenuItemType* item);
void inline InitMenuItem(MenuItemType* menuitem, char* text, void* child, void* parent, void* prev, void* next, enum MenuAction action, void* param);

void InitMenuStructures(void)
{
	//����������������� ����
	InitMenu(&m1, (char*)"������� ����", NULL, &m1_1);
	InitMenuItem(&m1_1, (char*)"����� �� �������", NULL, &m1, NULL, &m1_2, ACT_EXEC, NULL);
	InitMenuItem(&m1_2, (char*)"����� � ������ ������", NULL, &m1, &m1_1, &m1_3, ACT_EXEC, NULL);
	InitMenuItem(&m1_3, (char*)"���������� � ��", NULL, &m1, &m1_2, &m1_4, ACT_EXEC, NULL);
	InitMenuItem(&m1_4, (char*)"���������", &m2, &m1, &m1_3, NULL, ACT_NEXT, NULL);

	   	  
	//��������� ���� ���������
	InitMenu(&m2, (char*)"���������", &m1, &m2_1);
	InitMenuItem(&m2_1, (char*)"��������� �������", NULL, &m2, NULL, &m2_2, ACT_EXEC, NULL);
	InitMenuItem(&m2_2, (char*)"����� ���� ��������", NULL, &m2, &m2_1, &m2_3, ACT_EXEC, NULL);
	InitMenuItem(&m2_3, (char*)"�����", NULL, &m2, &m2_2, NULL, ACT_BACK, NULL);
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
	//��������� ������
	FontSelect(&MAIN_FONT);
	FontSetVSpace(LINE_VERT_INT);
	FontSetHSpace(0);
	//��������� ��������� ����
	MenuTitle_pos_y = SBAR_HEIGHT + LINE_VERT_INT + 10;
	MenuTitle_height = MAIN_FONT.char_height + LINE_VERT_INT + 1;
	MenuBody_pos_y = MenuTitle_pos_y + MenuTitle_height + 10;
	//���������� �������

	ConsoleSetArea(BORDER, MenuBody_pos_y, LCD_Width - BORDER, LCD_Height - BORDER);
	MaxLines = ConsoleGetMaxLines();
	MaxChars = ConsoleGetMaxChars();
	SetMenu(&m1);
	ShowMenuBody();
	ShowSelection(true);
}


void SetMenu(MenuType *menu)
{
	FillRectangle(0, MenuTitle_pos_y, LCD_Width, MenuBody_pos_y, BKG_COLOR); //������� ������� ��� ���������
	MenuTitle_pos_x = (LCD_Width - strlen(menu->title) * MAIN_FONT.char_width) / 2; //������������ ��������� �� �������� ������
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
	ConsoleClean(BKG_COLOR); //������� ������� ���� ����
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