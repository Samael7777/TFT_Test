#include "GUI.h"
#define _CRT_SECURE_NO_WARNINGS

int LCD_Height, LCD_Width;								//������� ������
int MaxLines;											//������������ ���������� ������� ���� ��� ������
int MaxChars;											//������������ ���������� �������� � ������
int MenuTitle_pos_x, MenuTitle_pos_y, MenuTitle_height;	//��������� ��������� ����
int MenuBody_pos_x, MenuBody_pos_y;						//��������� ���� ����								
MenuItem_t* fl_ptr;										//��������� �� ������ ������������ ����� ����

//��������� ��������� ������ ����
struct
{
	int pos = 0;				//������� ��������� (����� ������)
	MenuItem_t* ptr;			//��������� �� ���������� ����� ����
	char* buf;					//��������� �� �������� ������ ����
} sel;


//������� ����
Menu_t m1;
MenuItem_t m1_1, m1_2, m1_3, m1_4;



void MenuInit(void);					//������������� ����
void ShowMenuHeader(Menu_t* menu);		//�������� ��������� ���� � ���������� ��������� ���� �� ������ �����
void ShowMenu(void);					//�������� ����
void Selection(bool status);			//������������ ��������� (����������, �����)


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
	NavigateMenu(MNU_DOWN);
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
	m1_1.prev = NULL;
	m1_1.next = &m1_2;
	m1_2.prev = &m1_1;
	m1_2.next = &m1_3;
	m1_3.prev = &m1_2;
	m1_3.next = &m1_4;
	m1_4.prev = &m1_3;
	m1_4.next = NULL;
}

void ShowMenuHeader(Menu_t* menu)
{
	FillRectangle(0, LCD_Width, MenuTitle_pos_y, MenuBody_pos_y, BKG_COLOR); //������� ������� ��� ���������
	MenuTitle_pos_x = (LCD_Width - strlen(menu->title) * MAIN_FONT.char_width) / 2; //������������ ��������� �� �������� ������
	PutString(MenuTitle_pos_x, MenuTitle_pos_y, menu->title, &MAIN_FONT ,FONT_COLOR, BKG_COLOR);
	DrawHLine(MenuTitle_pos_x, (MenuBody_pos_y - 1), (strlen(menu->title) * MAIN_FONT.char_width), FONT_COLOR);
	if (menu->item != NULL) 
	{
		sel.ptr = (MenuItem_t*)menu->item;
		sel.pos = 0;
		fl_ptr = menu->item;
	}
	ShowMenu();
	Selection(true);
}


void ShowMenu()
{
	uint16_t fc, bc;
	ConsoleClean(BKG_COLOR); //������� ������� ���� ����
	SetCursor(0, 0);
	MenuItem_t* ptr = (MenuItem_t*)fl_ptr;
	while (ptr != NULL)
	{
		fc = FONT_COLOR;
		bc = BKG_COLOR;
		char* txt = ptr->Text;
		char* buf = (char*)calloc(MaxChars, sizeof(char));
		if (!buf) return;
		strncat(buf, txt, MaxChars);
		ConsolePutStringln(buf, fc, bc);
		free(buf);
		ptr = (MenuItem_t*)ptr->next;
	}
}

void Selection(bool status)
{
	int fc, bc;

	SetCursor(0, sel.pos);

	sel.buf = (char*)calloc(MaxChars + 2, sizeof(char));
	if (sel.buf == NULL) return;

	strcat(sel.buf, sel.ptr->Text);
	int spl = MaxChars - strlen(sel.buf) + 1;				//���������� ���������� ��������
	
	char* sp = (char*)calloc(spl + 1, sizeof(char));
	if (!sp) return;

	memset(sp, ' ', spl);
	strcat(sel.buf, sp);
	
	free(sp);
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
	ConsolePutString(sel.buf, fc, bc);
	
	free(sel.buf);
}

void NavigateMenu(Command_t com)
{
	switch (com)
	{
		case MNU_DOWN:
			if ((MenuItem_t*)(sel.ptr->next) != NULL)
			{
				Selection(false);
				sel.ptr = (MenuItem_t*)(sel.ptr->next);
				sel.pos++;
				if (sel.pos >= MaxLines)
				{
					sel.pos = MaxLines;
					if (fl_ptr->next != NULL)
					{
						fl_ptr = (MenuItem_t*)fl_ptr->next;
					}
				}
				Selection(true);
			}
			break;
		case MNU_UP:
			if ((MenuItem_t*)(sel.ptr->prev) != NULL)
			{
				Selection(false);
				sel.ptr = (MenuItem_t*)(sel.ptr->prev);
				sel.pos--;
				if (sel.pos < 0)
				{
					sel.pos = 0;
					if (fl_ptr->prev != NULL)
					{
						fl_ptr = (MenuItem_t*)fl_ptr->prev;
					}
				}
				Selection(true);
			}
			break;
		case MNU_SEL:
			//TODO
			break;
		default:
			break;
	}
	


}