#ifndef __GUI_H
#define __GUI_H

#include "..\tft\TFT_Lib.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif



	//�������� ���������

#define MAIN_FONT			CONSOLAS_12x22	//�������� �����
#define FONT_COLOR			0x1354 			//���� ������
#define BKG_COLOR			C_WHITE			//���� ����
#define SEL_COLOR			C_WHITE			//���� ����������� ������
#define SEL_BG_COLOR		0x1354 			//���� ���� ���������
#define SBAR_BG_COLOR		0x1354			//��� ����������
#define SBAR_F_COLOR		C_WHITE			//���� ������ ����������

#define LINE_VERT_INT		0				//���������� ����� ��������� �������� � ��������;
#define BORDER				20				//������ �� ����� ������ � ��������;
#define MENU_SPACE			10				//������ �� �������� ����;
#define SBAR_HEIGHT			44				//������ ���������� � ��������;


//�������� ������ ����
	typedef enum Command
	{
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_ESC,
		KEY_ENT,
		KEY_Z1,
		KEY_Z2,
		KEY_Z3,
		KEY_FAN
	} CommandType;

	typedef enum GuiMode		//����� ������ GUI
	{
		GUI_MENU,
		GUI_PC,
		GUI_AUTO,
		GUI_MANUAL,
		GUI_FIRMWARE
	} GuiModeType;

	//��������� ������� ������
	typedef struct
	{
		bool fan;
		bool z1;
		bool z2;
		bool z3;
	} StatusBarDataType;

	//��������� �������
	void GuiInit(void);							//�������������
	void GuiDeinit(void);						//���������������
	void GuiProcess(CommandType cmd);			//��������� ������
	void UpdateTime(void);						//�������� �����
	void SetSBarData(StatusBarDataType* sbd);	//���������� ��������� ����������
	GuiModeType GuiGetMode(void);
	void GuiSetMode(GuiModeType mode);
	void SetMenuMode(void);						//��������� ������ ����
#ifdef __cplusplus
}
#endif

#endif
