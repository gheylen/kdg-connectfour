#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#define _WIN32_WINNT 0x0500

/* Already defined in win api: obsolete

#define VK_LEFT			0x25
#define VK_UP			0x26
#define VK_RIGHT        0x27
#define VK_DOWN         0x28

*/

int isUpArrowPressed(void);
int isDownArrowPressed(void);
int isLeftArrowPressed(void);
int isRightArrowPressed(void);
int isConsoleActive(void);
int setConsoleTitle(char*);

#endif
