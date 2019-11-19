#ifndef __GUI_H
#define __GUI_H

#include "..\tft\TFT_Lib.h"
#include <stdio.h>


//�������� ���������

#define MAIN_FONT		CONSOLAS_12x22	//�������� �����
#define FONT_COLOR		C_WHITE			//���� ������
#define BKG_COLOR		C_BLUE			//���� ����
#define SEL_COLOR		C_WHITE			//���� ����������� ������
#define SEL_BG_COLOR	C_RED			//���� ���� ���������

constexpr auto LINE_VERT_INT =	0;		//���������� ����� ��������� �������� � ��������;
constexpr auto BORDER =			20;		//������ �� ����� ������ � ��������;
constexpr auto MENU_SPACE =		10;		//������ �� �������� ����;
constexpr auto HEADER_HEIGHT =	30;		//������ ������ � ��������;

//�������� ������ ����
typedef struct MenuItem
{
	char*	Text;				//�������� ������ ����
	void*	child = NULL;		//������ �� ����-�������
	void*	prev = NULL;		//������ �� ���������� ����� ����
	void*	next = NULL;		//������ �� ��������� ����� ����
	void*	Exec = NULL;		//������ �� ��������
} MenuItem_t;

//�������� ��������� ����
typedef struct Menu
{
	char*		title;				//�������� ����
	void*		parent = NULL;		//������ �� ����-������
	MenuItem_t*	item;				//������ �� ������ ����� ����
} Menu_t;

//�������� ������ ����
typedef enum Command
{
	MNU_UP,
	MNU_DOWN,
	MNU_SEL
} Command_t;

//��������� ������� ������
typedef struct
{
	boolean fan;
	boolean z1;
	boolean z2;
	boolean z3;
} HeaderData_t;

//��������� �������
void GuiInit(void);						//�������������
void NavigateMenu(Command_t com);		//��������� �� ����
void UpdateTime(void);					//�������� �����
void SetHeaderData(HeaderData_t* hd);	//���������� ������ ������

#endif
