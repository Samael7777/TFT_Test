#include "GUI.h"
#define _CRT_SECURE_NO_WARNINGS

int LCD_Height, LCD_Width;								//Размеры экрана
int MaxLines;											//Максимальное количество пунктов меню для вывода
int MaxChars;											//Максимальное количество символов в строке
int MenuTitle_pos_x, MenuTitle_pos_y, MenuTitle_height;	//Положение заголовка меню
int MenuBody_pos_x, MenuBody_pos_y;						//Положение тела меню								
MenuItem_t* fl_ptr;										//Указатель на первый отображаемый пункт меню

//Структура выделения пункта меню
struct
{
	int pos = 0;				//Позиция выделения (номер строки)
	MenuItem_t* ptr;			//Указатель на выделенный пункт меню
	char* buf;					//Указатель на название пункта меню
} sel;


//Главное меню
Menu_t m1;
MenuItem_t m1_1, m1_2, m1_3, m1_4;



void MenuInit(void);					//Инициализация меню
void ShowMenuHeader(Menu_t* menu);		//Показать заголовок окна и установить указатель меню на первый пункт
void ShowMenu(void);					//Показать меню
void Selection(bool status);			//Визуализация выделения (установить, снять)


void GuiInit(void)
{
	//Инициализация дисплея
	TFT_Init();
	TFT_Rotate(Orientation_Landscape_1);
	//Текущие размеры экрана
	LCD_Height = TFT_GetHeight();
	LCD_Width = TFT_GetWidth();
	//Параметры шрифта
	FontSelect(&MAIN_FONT);
	FontSetVSpace(LINE_VERT_INT);
	FontSetHSpace(0);
	//Положение элементов меню
	MenuTitle_pos_y = HEADER_HEIGHT + LINE_VERT_INT + 10;
	MenuTitle_height = MAIN_FONT.char_height + LINE_VERT_INT + 1;
	MenuBody_pos_y = MenuTitle_pos_y + MenuTitle_height + 1;
	//Предельные размеры
	MaxLines = (LCD_Height - MenuBody_pos_y) / (MAIN_FONT.char_height + LINE_VERT_INT);
	MaxChars = (LCD_Width - 2 * BORDER) / MAIN_FONT.char_width;
	
	FillScreen(BKG_COLOR);	//Очистка экрана
	DrawLine(BORDER / 2, HEADER_HEIGHT, LCD_Width - BORDER / 2, HEADER_HEIGHT, FONT_COLOR); // Линия, отделяющая хедер
	ConsoleSetArea(BORDER, MenuBody_pos_y, LCD_Width - BORDER, LCD_Height - BORDER);

	MenuInit(); //Инициализация меню
	ShowMenuHeader(&m1);
	NavigateMenu(MNU_DOWN);
}

void MenuInit(void)
{
	//Настройка связей главного меню
	m1.title = (char*)"Главное меню";
	m1_1.Text = (char*)"Пайка по профилю";
	m1_2.Text = (char*)"Пайка в ручном режиме";
	m1_3.Text = (char*)"Управление с ПК";
	m1_4.Text = (char*)"Настройки";
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
	FillRectangle(0, LCD_Width, MenuTitle_pos_y, MenuBody_pos_y, BKG_COLOR); //Очистка области под заголовок
	MenuTitle_pos_x = (LCD_Width - strlen(menu->title) * MAIN_FONT.char_width) / 2; //Выравнивание заголовка по середине экрана
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
	ConsoleClean(BKG_COLOR); //Очистка области тела меню
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
	int spl = MaxChars - strlen(sel.buf) + 1;				//Количество добавочных пробелов
	
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