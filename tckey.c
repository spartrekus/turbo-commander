
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

   int ch = 0 ; 
   int rows, cols;  
   getmaxyx( stdscr, rows, cols);
   char userinp[PATH_MAX];
   int gameover_nsc = 0;
   int gameselection = 3;

   while ( gameover_nsc == 0)
   {
           erase(); 
           mvprintw( gameselection, 3 , "x" );
           
           mvprintw( 0, 0 , "[Key: %d]", ch );
           if ( ch == KEY_DOWN ) mvprintw( 1, 0    , "[Key: KEY_DOWN]" );
           else if ( ch == KEY_UP ) mvprintw( 1, 0 , "[Key: KEY_UP]" );
           else if ( ch == KEY_HOME ) mvprintw( 1, 0 , "[Key: KEY_HOME]" );
           else if ( ch == KEY_END ) mvprintw( 1, 0 , "[Key: KEY_END]" );
           else if ( ch == KEY_ENTER ) mvprintw( 1, 0 , "[Key: KEY_ENTER]" );
           else if ( ch == KEY_EXIT ) mvprintw( 1, 0 , "[Key: KEY_EXIT]" );
           else if ( ch == 9 ) mvprintw( 1, 0 ,  "[Key: Escape with 9]" );
           else if ( ch == 27 ) mvprintw( 1, 0 , "[Key: Escape with 27]" );
           else if ( ch == KEY_F(10) ) mvprintw( 1, 0 , "[Key: KEY_F(10)]" );
           else if ( ch == KEY_F(11) ) mvprintw( 1, 0 , "[Key: KEY_F(11)]" );
           else if ( ch == KEY_F(12) ) mvprintw( 1, 0 , "[Key: KEY_F(12)]" );

           move( rows-1 , cols -1 );
           
           ch = getch();


    //if ( ch == 27) gameover_nsc = 1;

    if ( ch == 'q' ) 
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


