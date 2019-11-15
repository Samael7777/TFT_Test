#ifndef __GUI_H
#define __GUI_H

#include "TFT_Lib.h"

//�������� ���������

#define MAIN_FONT		CONSOLAS_12x22	//�������� �����
#define FONT_COLOR		C_WHITE			//���� ������
#define BKG_COLOR		C_BLUE			//���� ����
#define SEL_COLOR		C_WHITE			//���� ����������� ������
#define SEL_BG_COLOR	C_RED			//���� ���� ���������

constexpr auto LINE_VERT_INT =	1;		//���������� ����� ��������� �������� � ��������;
constexpr auto BORDER =			10;		//������ �� ����� ������ � ��������;
constexpr auto MENU_SPACE =		10;		//������ �� �������� ����;
constexpr auto HEADER_LINES =	1;		//���������� ����� � ������;

//�������� ������ ����
typedef struct MenuItem
{
	char*	Text;					//�������� ������ ����
	struct	MenuRoot* parent;		//������ �� ����-������
	struct	MenuRoot* child;		//������ �� ����-�������
	void*	Exec;					//������ �� ��������
} MenuItemType;

//�������� ��������� ����
typedef struct MenuRoot
{
	char* title;					//�������� ����
	struct MenuItem* element[];		//������ �� ������ ����� ����
} MenuRootType;


//��������� ��������� �� ����������
typedef enum
{
	KEY_LEFT,						
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_EXEC,
	KEY_ESC,
	KEY_F1,
	KEY_F2,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_SH,
	KEY_ST,
	KEY_FAN,
	KEY_Z1,
	KEY_Z2,
	KEY_Z3,
	KEY_PWR
} KeyPressedType;

//��������� ������� ������
typedef enum
{
	MODE_MENU,						//����� �������� ����
	MODE_SET_PARAM,					//����� ��������� ���������
	MODE_MANUAL_SOLDING,			//����� ������ �����
	MODE_PROFILE_SOLDING,			//����� ����� �� �������
	MODE_PC_CONTROL,				//����� ���������� � ��
	MODE_FIRMWARE_UPDATE			//����� ���������� ��������
} ModeType;


//���������

const int LINE_HEIGHT = MAIN_FONT.char_height + LINE_VERT_INT;			//������ ������ � ��������
const int HEADER_HEIGHT = LINE_HEIGHT * HEADER_LINES;					//������ ������ � ��������
const int MENU_TITLE_POS_Y = HEADER_HEIGHT + MENU_SPACE;				//������� ������ ��������� ���� �� ���������
const int MENU_BODY_POS_Y = MENU_TITLE_POS_Y + MENU_SPACE;				//������� ������ ���� ���� �� ���������


//��������� �������

void GuiInit(void);					//������������� ����������
//void UpdateTime(void);				//�������� ����� � ����
//void SetMode(ModeType mode);
//void Navigate(KeyPressedType key);

#endif