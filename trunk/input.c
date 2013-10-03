#include "console.h"

#include <windows.h>

int isUpArrowPressed(void)
{
    return GetAsyncKeyState(VK_UP);
}
int isRightArrowPressed(void)
{
    return GetAsyncKeyState(VK_RIGHT);
}
int isDownArrowPressed(void)
{
    return GetAsyncKeyState(VK_DOWN);
}
int isLeftArrowPressed(void)
{
    return GetAsyncKeyState(VK_LEFT);
}
int isConsoleActive(void)
{
    return IsWindowEnabled((void*)GetConsoleWindow());
}
int setConsoleTitle(char *title)
{
    return SetConsoleTitle(title);
}
int setConsoleOutputTo(unsigned int textMode)
{
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textMode);
}
