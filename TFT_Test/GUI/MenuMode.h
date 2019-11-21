
#ifndef __MENUMODE_H
#define __MENUMODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

	void InitMenuStructures(void);
	void NavigateMenu(CommandType com);
	void SetMenuMode(void);


#ifdef __cplusplus
}
#endif
#endif //__MENUMODE_H


