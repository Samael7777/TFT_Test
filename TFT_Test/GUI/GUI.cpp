#include "GUI.h"
#define _CRT_SECURE_NO_WARNINGS

int LCD_Height, LCD_Width;	//Размеры экрана
int MaxLines;			//Максимальное количество пунктов меню для вывода
int MaxChars;			//Максимальное количество символов в строке
int MenuTitle_pos_x, MenuTitle_pos_y, MenuTitle_height;	//Положение заголовка меню
int MenuBody_pos_x, MenuBody_pos_y;		//Положение тела меню


//Главное меню
Menu_t m1;
MenuItem_t m1_1, m1_2, m1_3, m1_4;



void MenuInit(void);			//Инициализация меню
void CleanMenuArea(void);		//Очистка области меню
void ShowMenuHeader(Menu_t* menu);	//Показать заголовок окна
void ShowMenu(Menu_t* menu);		//Показать меню

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
	ShowMenu(&m1);
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
	FillRectangle(0, LCD_Width, MenuTitle_pos_y, MenuBody_pos_y, BKG_COLOR); //Очистка области под заголовок
	MenuTitle_pos_x = (LCD_Width - strlen(menu->title) * MAIN_FONT.char_width) / 2; //Выравнивание заголовка по середине экрана
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