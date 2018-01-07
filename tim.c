
/////////////////////////////////////
/////////////////////////////////////
#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif


#define DATAMAX 2500  


#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>  
#include <time.h>

#include <ncurses.h>




int rows, cols; 
int curs_y;
int curs_x;
int win_y1, win_x1, win_y2, win_x2;
int ch;
char idata[DATAMAX];
int idatasel = 0;
int idataselmax = DATAMAX;



/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *straddchar(char *str, int mycharpostmp , int mychar )
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      int mycharpos = mycharpostmp;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( i == mycharpos ) 
	{
          ptr[j++]=mychar;
          ptr[j++]=str[i];
	}
        else
	{
          ptr[j++]=str[i];
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}





/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *strrmchar(char *str, int mycharpos )
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        //if ( str[i] == '&' ) 
        if ( i == mycharpos ) 
	{
	}
        else
	{
          ptr[j++]=str[i];
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}





////////////////////////////////////////////////////////////////////
char *strrlf(char *str) 
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}
////////////////////////////////////////////////////////////////////
char *strcut( char *str , int myposstart, int myposend )
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}






   void gfxhline( int posyy )
   {
      int foo;
      for( foo = 0 ; foo <= cols-1 ; foo++)   
          mvaddch( posyy , foo , ' ');
   }










////////////////////////
////////////////////////
////////////////////////
////////////////////////
char *strninput( char *myinitstring )
{

   int strninput_gameover = 0; 
   char strmsg[PATH_MAX];
   char charo[PATH_MAX];
   strncpy( strmsg, myinitstring , PATH_MAX );

   int ch ;  int foo ; 
   int fooj; 
   while ( strninput_gameover == 0 )
   {
                  getmaxyx( stdscr, rows, cols);
                  attroff( A_REVERSE );
                  for ( fooj = 0 ; fooj <= cols-1;  fooj++)
                  {
                    mvaddch( rows-1, fooj , ' ' );
                  }
                  mvprintw( rows-1, 0, ":> %s" , strrlf( strmsg ) );
                  attron( A_REVERSE );
                  printw( " " );
                  attroff( A_REVERSE );
                  refresh() ; ch = getch();

		  if ( ch == KEY_BACKSPACE ) 
		  {
		      strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );
		  }
		  else if ( ch == 4 ) 
		  {
			   strncpy( strmsg, ""  ,  PATH_MAX );
		  }
		  else if ( ch == 27 ) 
		  {
			   strncpy( strmsg, ""  ,  PATH_MAX );
		  }
	          else if (
			(( ch >= 'a' ) && ( ch <= 'z' ) ) 
		        || (( ch >= 'A' ) && ( ch <= 'Z' ) ) 
		        || (( ch >= '1' ) && ( ch <= '9' ) ) 
		        || (( ch == '0' ) ) 
		        || (( ch == '~' ) ) 
		        || (( ch == '!' ) ) 
		        || (( ch == '&' ) ) 
		        || (( ch == '=' ) ) 
		        || (( ch == ':' ) ) 
		        || (( ch == ';' ) ) 
		        || (( ch == '<' ) ) 
		        || (( ch == '>' ) ) 
		        || (( ch == ' ' ) ) 
		        || (( ch == '|' ) ) 
		        || (( ch == '#' ) ) 
		        || (( ch == '?' ) ) 
		        || (( ch == '+' ) ) 
		        || (( ch == '/' ) ) 
		        || (( ch == '\\' ) ) 
		        || (( ch == '.' ) ) 
		        || (( ch == '$' ) ) 
		        || (( ch == '%' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == ',' ) ) 
		        || (( ch == '{' ) ) 
		        || (( ch == '}' ) ) 
		        || (( ch == '(' ) ) 
		        || (( ch == ')' ) ) 
		        || (( ch == ']' ) ) 
		        || (( ch == '[' ) ) 
		        || (( ch == '*' ) ) 
		        || (( ch == '"' ) ) 
		        || (( ch == '@' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '_' ) ) 
		        || (( ch == '^' ) ) 
		        || (( ch == '\'' ) ) 
	             ) 
		  {
                           foo = snprintf( charo, PATH_MAX , "%s%c",  strmsg, ch );
			   strncpy( strmsg,  charo ,  PATH_MAX );
		  }
		  else if ( ch == 10 ) 
		  {
                        strninput_gameover = 1;
		  }
     }
     char ptr[PATH_MAX];
     strncpy( ptr, strmsg, PATH_MAX );
     size_t siz = sizeof ptr ; 
     char *r = malloc( sizeof ptr );
     return r ? memcpy(r, ptr, siz ) : NULL;
}







///////////////////////////////////
void colornorm(void);
void crossgraphvga_init(void)
{
  initscr();			
  keypad(stdscr, true);
  noecho();
  curs_set( 0 );
  //start_color();

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
    //colornorm(); 

    //color_set( i , NULL );
    mvprintw( x, 2 , "%d ", i );

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





void win_draw()
{
     if ( idatasel <= 0 ) idatasel = 0;

     int i, j ; 
     int posy , posx ;  int charskip;
     posy = win_y1 ;  posx = win_x1;
     for ( j = 0 ; j <= rows-1  ; j++) 
      for ( i = 0 ;  i <= cols-1  ; i++) 
        mvaddch( j, i , ' ' );

      for ( i = 0 ; i <= DATAMAX ; i++)
      {
        attroff( A_REVERSE );
        charskip = 0;
        if ( idata[ i ] == '\n' )  { charskip = 1; 

      if ( i == idatasel ) attron( A_REVERSE );
      if ( i == idatasel ) addch( ' ' );
       posy++;  posx = win_x1; }

        move( posy, posx);
        if ( charskip == 0 )
        {
          if ( i == idatasel ) attron( A_REVERSE );
          if ( posx <= win_x2 )
           if ( posy <= win_y2 )
             addch( idata[ i ] );
          posx++;
        }
      }

    // top bar
    attron(  A_REVERSE ); 
    gfxhline( 0 );
    mvaddch( 0 , 1,  ' ' );
    printw( "TIM (TINY) %d/%d", idatasel, idataselmax );
    attroff(  A_REVERSE ); 


     /// borders
     for ( j = win_y1 ; j <= win_y2  ; j++) 
        mvaddch( j, win_x1-1 , ACS_VLINE );
     for ( j = win_y1 ; j <= win_y2  ; j++) 
        mvaddch( j, win_x2+1 , ACS_VLINE );
     for ( i = win_x1 ; i <= win_x2  ; i++) 
        mvaddch( win_y1-1 , i ,  ACS_HLINE );
     for ( i = win_x1 ; i <= win_x2  ; i++) 
        mvaddch( win_y2+1 , i  , ACS_HLINE );


    mvaddch( win_y1-1 , win_x1 - 1 , ACS_ULCORNER );
    mvaddch( win_y1-1 , win_x2 + 1 , ACS_URCORNER );
    mvaddch( win_y2+1 , win_x1 - 1 , ACS_LLCORNER );
    mvaddch( win_y2+1 , win_x2 + 1 , ACS_LRCORNER );


  attroff( A_REVERSE );


}







void win_keypress()
{
  int win_key_gameover = 0;
  while( win_key_gameover == 0)
  {
       erase();
       mvprintw( 0, 0, "Key Win Content" );
       mvprintw( 5,5, "%d", ch );
       ch = getch();
       if ( ch == 'i' ) 
           win_key_gameover = 1 ;
       else if ( ch == 'q' ) 
           win_key_gameover = 1 ;
  }
}

void file_load()
{
}


void file_save()
{
    FILE *fp;
    fp = fopen( "document.mrk" , "wb" );
    int foo ; 
    char charo[PATH_MAX];
    for ( foo = 0 ; foo <= DATAMAX ; foo++)
    {
      snprintf( charo, PATH_MAX , "%c",  idata[ foo ] );
      fputs( charo , fp );
    }
    fclose( fp );
}



void win_edit()
{
  int win_edit_gameover = 0;
  int lastkey=0;
  while( win_edit_gameover == 0)
  {
       win_draw();
       mvprintw( rows-1, 0, "Edit Win Content" );
       ch = getch();
       switch( ch )
       {
           case KEY_F(10):
           case KEY_EXIT:
           case 27:
             win_edit_gameover = 1;
             break; 

           case KEY_F(2):
                file_save();
              break;

	     case KEY_UP:
	     idatasel--;
             break; 
	     case KEY_DOWN:
	     idatasel++;
             break; 
	     case KEY_LEFT:
	     idatasel--;
             break; 
	     case KEY_RIGHT:
	     idatasel++;
             break; 

	     case 263:
              idatasel--;
	      strncpy( idata, strrmchar( idata ,  idatasel ) , DATAMAX );
              break; 

	     case 330:
	      strncpy( idata, strrmchar( idata ,  idatasel ) , DATAMAX );
              break; 

	     case 4:
	     strncpy( idata, ""  ,  PATH_MAX );
             break; 

           default:
             if ( (  lastkey == 'j' ) && (  ch == 'j' ) )
             {
                idatasel--;
	        strncpy( idata, strrmchar( idata ,  idatasel ) , DATAMAX );
                win_edit_gameover = 1;
             }
             else 
             {
               //idata[ idatasel ] = ch ;
	       strncpy( idata, straddchar( idata , idatasel, ch ) , DATAMAX );
               lastkey = ch; 
               idatasel++;
             }
             break;
        }
  }

}





void win_menubar()
{
  //color_set( 0, NULL ); attroff( A_REVERSE ); attroff( A_BOLD ); attroff( A_BLINK );
  attroff(  A_REVERSE ); 
  gfxhline( rows-1);
  attron(  A_REVERSE ); 
  gfxhline( rows-1 );
  mvprintw( rows-1, 1, "F1:(O)pen F2:(S)ave F3:(R)ead F4:(E)dit F5:E(x)port F10:Quit" );
  attroff( A_REVERSE );
}






void win_change()
{
  int win_change_gameover = 0;
  while( win_change_gameover == 0)
  {
       win_draw();
       mvprintw( rows-1, 0, "Change Win Size" );
       ch = getch();
       switch( ch )
       {
           case 'i': 
             win_change_gameover = 1;
             break;

           case 'j':
             win_y2 +=1 ;
             break; 
           case 'k':
             win_y2 -=1 ;
             break; 
           case 'l':
             win_x2 +=1 ;
             break; 
           case 'h':
             win_x2 -=1 ;
             break; 

           case KEY_DOWN:
           case 's':
             win_y1 +=1 ;
             break; 
           case KEY_UP:
           case 'w':
             win_y1 -=1 ;
             break; 
           case KEY_RIGHT:
           case 'd':
             win_x1 +=1 ;
             break; 
           case KEY_LEFT:
           case 'a':
             win_x1 -=1 ;
             break; 
        }
  }

}

int main(void)
{
  //crossgraphvga_init();
  //crossgraphvga_colors();

  initscr();			
  keypad(stdscr, true);
  noecho();
  curs_set( 0 );


  erase();
   
  strncpy( idata , "", DATAMAX );
  int foo ; 
  for ( foo = 0 ; foo <= DATAMAX ; foo++)
     idata[ foo ] = ' ';

  getmaxyx( stdscr, rows, cols );
  int gameover = 0;

  win_y1= 2; 
  win_x1= 2; 
  win_y2=  rows-3; 
  win_x2 = cols -2 ; 
   
  while( gameover == 0)
  {
      win_draw(); 
      win_menubar();
      ch = getch();
      switch( ch )
      { 

           case KEY_HOME:
             curs_x =1 ;
             curs_y =1 ;
             break; 

          case 'g': 
	     idatasel = 0 ;
             curs_x =1 ;
             curs_y =1 ;
             break; 

           case KEY_END:
           case 'G':
             curs_x = cols-2 -6 ;
             curs_y = rows-2 ;
             break; 

           case 'o':
           case KEY_F(1):
              erase(); mvprintw( 0,0, "Load [Y/n]?" );
              ch = getch();
              if ( ch == 'y' )
              file_load();
              break;
             break; 

           case 'w':
           case KEY_F(9):
              win_change();
              break;

           case 'i':
           case KEY_F(4):
              win_edit();
              break;

           case KEY_F(2):
           case 's':
              erase(); mvprintw( 0,0, "Save [Y/n]?" );
              ch = getch();
              if ( ch == 'y' )
                file_save();
              else if ( ch == '1' )
                file_save();
              break;


           case 'c':
           case 'C':
             erase();
             crossgraphvga_colors();
             getch();
             break; 

          case 'q':
          case 'Q':
          case KEY_F(10):
              erase(); mvprintw( 0,0, "Quit [Y/n]?" );
              ch = getch();
              if ( ch == 'y' )
                gameover =1 ;
              else if ( ch == '1' )
                gameover =1 ;
              break;

          case ':': 
             //color_set( 0, NULL ); attroff( A_REVERSE ); attroff( A_BOLD ); attroff( A_BLINK );
             erase( );
             mvprintw( 0, 0, "CMD" );
             strninput( "" );
             break; 

          case 'a': 
             //color_set( 0, NULL ); attroff( A_REVERSE ); attroff( A_BOLD ); attroff( A_BLINK );
             strninput( "" );
             break; 

          case 'K': 
             win_keypress();
             break; 

	  case KEY_UP:
          case 'k': 
	     idatasel--;
             break; 
	     case KEY_DOWN:


          case 'j': 
	     idatasel++;
             break; 

	     case KEY_LEFT:
          case 'h': 
	     idatasel--;
             break; 
	     case KEY_RIGHT:
          case 'l': 
	     idatasel++;
             break; 


	   case 263:
              idatasel--;
	      strncpy( idata, strrmchar( idata ,  idatasel ) , DATAMAX );
              break; 

	  case 'x':
	  case 330:
	      strncpy( idata, strrmchar( idata ,  idatasel ) , DATAMAX );
              break; 


      }
  }


  curs_set( 1 );
  endwin();			/* End curses mode		  */
  return(0);
}








