#include "GUI.h"
#define _CRT_SECURE_NO_WARNINGS

int LCD_Height, LCD_Width;	//������� ������
int MaxLines;			//������������ ���������� ������� ���� ��� ������
int MaxChars;			//������������ ���������� �������� � ������
int MenuTitle_pos_x, MenuTitle_pos_y, MenuTitle_height;	//��������� ��������� ����
int MenuBody_pos_x, MenuBody_pos_y;		//��������� ���� ����


//������� ����
Menu_t m1;
MenuItem_t m1_1, m1_2, m1_3, m1_4;



void MenuInit(void);			//������������� ����
void CleanMenuArea(void);		//������� ������� ����
void ShowMenuHeader(Menu_t* menu);	//�������� ��������� ����
void ShowMenu(Menu_t* menu);		//�������� ����

void GuiInit(void)
{
	//������������� �������
	TFT_Init();
	TFT_Rotate(Orientation_Landscape_1);
	//������� ������� ������
	LCD_Height = TFT_GetHeight();
	LCD_Width = TFT_GetWidth();
	//��������� ������
	FontSelect(&MAIN_FONT);
	FontSetVSpace(LINE_VERT_INT);
	FontSetHSpace(0);
	//��������� ��������� ����
	MenuTitle_pos_y = HEADER_HEIGHT + LINE_VERT_INT + 10;
	MenuTitle_height = MAIN_FONT.char_height + LINE_VERT_INT + 1;
	MenuBody_pos_y = MenuTitle_pos_y + MenuTitle_height + 1;
	//���������� �������
	MaxLines = (LCD_Height - MenuBody_pos_y) / (MAIN_FONT.char_height + LINE_VERT_INT);
	MaxChars = (LCD_Width - 2 * BORDER) / MAIN_FONT.char_width;
	
	FillScreen(BKG_COLOR);	//������� ������
	DrawLine(BORDER / 2, HEADER_HEIGHT, LCD_Width - BORDER / 2, HEADER_HEIGHT, FONT_COLOR); // �����, ���������� �����
	ConsoleSetArea(BORDER, MenuBody_pos_y, LCD_Width - BORDER, LCD_Height - BORDER);

	MenuInit(); //������������� ����
	ShowMenuHeader(&m1);
	ShowMenu(&m1);
}

void MenuInit(void)
{
	//��������� ������ �������� ����
	m1.title = (char*)"������� ����";
	m1_1.Text = (char*)"����� �� �������";
	m1_2.Text = (char*)"����� � ������ ������";
	m1_3.Text = (char*)"���������� � ��";
	m1_4.Text = (char*)"���������";
	m1.item = &m1_1;
	m1.parent = NULL;
	m1_1.id = 0;
	m1_1.prev = NULL;
	m1_1.next = &m1_2;
	m1_2.id = m1_1.id + 1;
	m1_2.prev = &m1_1;
	m1_2.next = &m1_3;
	m1_3.id = m1_2.id + 1;
	m1_3.prev = &m1_2;
	m1_3.next = &m1_4;
	m1_4.id = m1_3.id + 1;
	m1_4.prev = &m1_3;
	m1_4.next = NULL;
}

void ShowMenuHeader(Menu_t* menu)
{
	FillRectangle(0, LCD_Width, MenuTitle_pos_y, MenuBody_pos_y, BKG_COLOR); //������� ������� ��� ���������
	MenuTitle_pos_x = (LCD_Width - strlen(menu->title) * MAIN_FONT.char_width) / 2; //������������ ��������� �� �������� ������
	PutString(MenuTitle_pos_x, MenuTitle_pos_y, menu->title, &MAIN_FONT ,FONT_COLOR, BKG_COLOR);
	DrawHLine(MenuTitle_pos_x, (MenuBody_pos_y - 1), (strlen(menu->title) * MAIN_FONT.char_width), FONT_COLOR);
}

void CleanMenuArea(void)
{
	ConsoleClean(BKG_COLOR);
}

void ShowMenu(Menu_t* menu)
{
	MenuItem_t* ptr;
	char* txt;
	int id;
	ConsoleClean(BKG_COLOR);
	SetCursor(0, 0);
	ptr = (MenuItem_t *)menu->item;
	while (ptr != NULL)
	{
		id = ptr->id + 1;
		txt = ptr->Text;
		char* buf = (char*)calloc(MaxChars, sizeof(char));
		if (buf != NULL) 
		{
			sprintf(buf, "%d. %s\r\n", id, txt);
			ConsolePutString(buf, FONT_COLOR, BKG_COLOR);
			free(buf);
		
		}
		ptr = (MenuItem_t*)ptr->next;
	}
}