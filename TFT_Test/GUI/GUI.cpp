#include "GUI.h"

int LCDHeight, LCDWidth;
int MaxLines;			//������������ ���������� ������� ���� ��� ������
int MaxLineLenght;		//������������ ���������� �������� � ������
char* DisplayBuff;		//����� ��� ������ ����

MenuItemType* Selected;		//������ �� ��������� ����� ����
int index = 0;				//����� 

//������� ����
MenuItemType MMProfiles = { (char*)"����� �� �������",NULL,NULL,NULL,NULL,NULL };
MenuItemType MMManual = { (char*)"����� � ������ ������",NULL,NULL,NULL,NULL,NULL };
MenuItemType MMPCControl = { (char*)"���������� � ��",NULL,NULL,NULL,NULL,NULL };
MenuItemType MMSettings = { (char*)"���������",NULL,NULL,NULL,NULL,NULL };
MenuRootType MainMenuTitle = { (char*)"������� ����",NULL };
MenuItemType* MainMenuBody

void MenuInit(void);			//������������� ����
void CleanMenuArea(void);		//������� ������� ����
void

void GuiInit(void)
{
	//������������� �������
	TFT_Init();
	TFT_Rotate(Orientation_Landscape_1);
	//������� ������� ������
	LCDHeight = TFT_GetHeight();
	LCDWidth = TFT_GetWidth();
	MaxLines = (LCDHeight - MENU_BODY_POS_Y) / LINE_HEIGHT;
	
	MenuInit(); //������������� ����
	
	FillScreen(BKG_COLOR);	//������� ������
	DrawLine(BORDER / 2, HEADER_HEIGHT, LCDWidth - BORDER / 2, HEADER_HEIGHT, FONT_COLOR);

}

void MenuInit(void)
{
	//��������� ������ �������� ����


void CleanMenuArea(void)
{
	FillRectangle(0, MENU_TITLE_POS_Y, LCDWidth, LCDHeight, BKG_COLOR);
}