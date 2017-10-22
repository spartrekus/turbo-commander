
////////////////////////////
///  TC rocks
///  Turbo Commander
////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // the classical ones
  
#include <dirent.h>  // this will define path_max!!!!!!!!!!!!!!
#include <ncurses.h>


///////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{
   initscr();
   //raw();  //ctrl+c is with raw() disabled.
   keypad(stdscr, true); // keypad allows to F1,... arrows to be operational.
   noecho();
   // getmaxyx(stdscr, maxy, maxx);

   int ch ; 
   int rows, cols;  
   getmaxyx( stdscr, rows, cols);
   char userinp[PATH_MAX];
   int gameover_nsc = 0;
   int gameselection = 3;

   while ( gameover_nsc == 0)
   {
           erase(); 
           mvprintw( gameselection, 3 , "x" );
           ch = getch();

    if ( ch == 27) 
        gameover_nsc = 1;

    else if ( ch == 'q' ) 
        gameover_nsc = 1;

    else if ( ch == 'k' )
        gameselection--;
    else if ( ch == 'j' )
        gameselection++;

    else if ( ch ==  KEY_UP )
        gameselection--;
    else if ( ch == KEY_DOWN )
        gameselection++;

    else if ( ch ==  KEY_LEFT )
        gameselection--;

    else if ( ch ==  KEY_RIGHT )
        gameselection++;

    }

    curs_set( 1 );
    endwin();		/* End curses mode		  */
    return 0;
}


