
#ifndef __MENUMODE_H
#define __MENUMODE_H

#include <stdint.h>
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
	MenuItemType *item;			//������ �� ������ ����� ����
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


