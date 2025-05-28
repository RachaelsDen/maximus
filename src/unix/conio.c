#include <curses.h>
#include <stdio.h>
#include <unistd.h>

inline void clrscr(void)
{
    if (!stdscr)
    {
        /* no curses - assume vt100 */
        printf("\033[2J");
        sleep(0);
        printf("\033[0;0f");
    }
    else
        clear();
}

int fputchar(int c)
{
    if (c < 0)
        return 0;
    return fputc(c, stdout);
}
