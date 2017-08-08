/*  checkthis.c  */

#include <curses.h>

int main()

{

initscr();

wclear(stdscr);

mvprintw(5,15,"hello world\n");

wrefresh(stdscr);

system("pause");

endwin();

}
