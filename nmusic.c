
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

int rows, cols; 
int curs_y;
int curs_x;

#define PATH_MAX 2400 


////////////////////////////////
void nruncmd( char *thecmd   )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
}




///////////////////////////////////
void colornorm(void);
void crossgraphvga_init(void)
{
  initscr();			
  keypad(stdscr, true);
  noecho();
  curs_set( 0 );
  start_color();

  /// basic ncurses colors
  init_pair(0, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_CYAN, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);

  /// extra tc colors
  init_pair(8, COLOR_BLUE,   COLOR_YELLOW);
  init_pair(9, COLOR_YELLOW, COLOR_BLUE);

}
void crossgraphvga_colors(void)
{
  color_set( 7 , NULL ); attroff( A_REVERSE ); mvprintw( 2,2, "Darker  ;  Brighter (bold)" );
  
  getmaxyx( stdscr, rows, cols );

  int x = 5; int i = 1;
  for( i = 0; i <= rows-1 ; i++)  //ncurses as by default 8 colors
  { 
    colornorm(); 

    color_set( i , NULL );
    mvprintw( x, x , "%d ", i );

    attron( A_REVERSE );
    attroff( A_BOLD );
    color_set( i , NULL );
    printw( "%d", i );
    colornorm(); printw( " " );

    attroff( A_REVERSE );
    attron(  A_BOLD );
    color_set( i , NULL );
    printw( " ; %d", i );
    colornorm(); printw( " " );

    // reverse and bold
    color_set( i , NULL );
    attron( A_REVERSE );
    attroff( A_BOLD ); //for the console
    attron(  A_BLINK ); //for the console
    printw( " R%d", i );
    colornorm(); printw( " " );


    color_set( i , NULL );
    attron(  A_REVERSE );
    attron(  A_BOLD ); //for the console
    attroff( A_BLINK ); //for the console
    printw( " Rev,Bold%d", i );
    colornorm(); printw( " " );

    color_set( i , NULL );
    attron(  A_REVERSE );
    attron(  A_BOLD ); //for the console
    attron(  A_BLINK ); //for the console
    printw( " Rev,Bold,Blink%d", i );
    colornorm(); printw( " " );

    x += 1; 
    colornorm(); printw( " " );
    color_set( 7 , NULL ); printw( " (#.%d)", i );

    mvprintw( rows-1, cols-8, "|%d,%d|" , rows, cols );
  } 

  refresh();
  x += 2; 
  attroff( A_REVERSE );
  color_set( 7, NULL ); mvprintw(  x, 5 , "<Press Key>" );
}


void colornorm(void)
{
    attroff(  A_REVERSE );
    attroff( A_BOLD );
    attroff( A_BLINK );
    attroff( A_UNDERLINE );
    color_set( 7, NULL ); 
}






int main(void)
{
  crossgraphvga_init();
  crossgraphvga_colors();
  //getch();

  getmaxyx( stdscr, rows, cols );
  int i, j, ch ; int gameover = 0;
  int posy ; 
  ch = 0;
   
  while( gameover == 0)
  {
     erase();
     color_set( 8 , NULL ); attron(  A_REVERSE ); attron(  A_BOLD ); attroff(  A_BLINK ); 

     color_set( 2 , NULL ); attroff(  A_REVERSE ); attroff(  A_BOLD ); attroff(  A_BLINK ); 
     attron( A_BOLD );

     for ( j = 0 ; j <= rows-1  ; j++) 
      for ( i = 0 ;  i <= cols-1  ; i++) 
        mvaddch( j, i , ' ' );


      mvaddch( curs_y, curs_x, 'M' );
      printw( "Music" );
      
      posy = curs_y;
      mvprintw( posy++, curs_x, " ** NMUSIC ** ");
      mvprintw( posy++, curs_x, "1: Audio Settings (alsamixer) ");
      mvprintw( posy++, curs_x, "2: Mylene Radio (mpg123) ");
      mvprintw( posy++, curs_x, "3: Mylene Radio (mplayer) ");
      mvprintw( posy++, curs_x, "q: Quit");
      mvprintw( posy++, curs_x, "?: Help");
       
      ch = getch();
      switch( ch )
      { 

          case KEY_NPAGE:
          case 'q':
          case 'i':
             gameover =1 ;
             break; 

          case '1':
             nruncmd( " alsamixer " );
             break; 
          case '2':
             nruncmd( " mplayer  -vo null -ao alsa:device=hw=0,0    \"http://listen.radionomy.com/mylenefarmerwebradio\" " );
             break; 
          case '3':
             nruncmd( " mpg123   \"http://listen.radionomy.com/mylenefarmerwebradio\" " );
             break; 

           case KEY_HOME:
           case 'g':
             curs_x =1 ;
             curs_y =1 ;
             break; 

           case KEY_END:
           case 'G':
             curs_x = cols-2 -6 ;
             curs_y = rows-2 ;
             break; 

           case 'j':
           case 's': 
           case KEY_DOWN:
             curs_y +=1 ;
             break; 

           case 'k':
           case 'w': 
           case KEY_UP:
             curs_y -=1 ;
             break; 
           case 'l':
           case 'd': 
           case KEY_RIGHT:
             curs_x +=1 ;
             break; 
           case 'h':
           case 'a': 
           case KEY_LEFT:
             curs_x -=1 ;
             break; 

           case 'c':
             erase();
             crossgraphvga_colors();
             getch();
             break; 

      }
  }


  curs_set( 1 );
  endwin();			/* End curses mode		  */
  return(0);
}








