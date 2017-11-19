
////////////////////////////
///  TC tcchar
///  Turbo Commander
////////////////////////////

// [Pos:58][Char:^L][Dec:12]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <ncurses.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>



int rows, cols;  
int nconsole_explorer = 1;
int gameselection = 1;
int gamesel_x=1 ;
int gamesel_y=1 ;
char fileselection[PATH_MAX];
char filechar;
double filepos = 1;


/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
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




////////////////////////////////
void nrunwith( char *theprg , char *thefile )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , "   " , PATH_MAX );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , theprg , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thefile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
}


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
                    //mvaddch( rows-2, fooj , ' ' );
                    mvaddch( rows-1, fooj , ' ' );
                  }
                  mvprintw( rows-1, 0, ":> %s" , strrlf( strmsg ) );
                  attron( A_REVERSE );
                  printw( " " );
                  attroff( A_REVERSE );
                  refresh() ; ch = getch();
		  //if ( ch == 127  ) 
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
		        || (( ch == ',' ) ) 
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
		        || (( ch == ',' ) ) 
		        || (( ch == '-' ) ) 
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



void drawit()
{
        int fooj; 
        char foocwd[PATH_MAX];
        getmaxyx( stdscr, rows, cols);
        color_set( 2 , NULL );
        attroff( A_REVERSE );
        color_set( 2 , NULL );
        attroff( A_REVERSE );
        erase();  


        // bottom bar
        color_set( 15 , NULL );
        attron( A_REVERSE );
        for ( fooj = 0 ; fooj <= cols-1;  fooj++)
        {
            mvaddch( rows-2, fooj , ' ' );
            mvaddch( 0, fooj , ' ' );
        }

        color_set( 15 , NULL ); attron( A_REVERSE );
        for ( fooj = 0 ; fooj <= cols-1;  fooj++)
            mvaddch( 0, fooj , ' ' );
        mvprintw( 0, 0, "|TCCHAR|" );

        color_set( 0 , NULL ); attroff( A_REVERSE );
        mvprintw( 1, 1 , "[File: %s]", fileselection );

        //////////// read a bit
        
  int c; 
  int readpos = 1; int freader = 1;
   if ( fexist( fileselection ) == 1 )
   {
     FILE *fd = fopen( fileselection  ,"r");
     while ( freader == 1 )
     {
        c = fgetc( fd );
          
        if ( filepos == readpos )
           filechar = (char) c;


        if ( readpos >= filepos )
           freader = 0;

        if ( c == EOF) freader = 0;

        readpos++;
     }
     fclose( fd );
    }

        color_set( 0 , NULL ); attroff( A_REVERSE );
        mvprintw( 5 , 0 , "[Pos:%g][Char:%c][Dec:%d]", filepos , filechar , filechar );

        color_set( 0 , NULL ); attroff( A_REVERSE );
        for ( fooj = 0 ; fooj <= cols-1;  fooj++)
            mvaddch( rows-1, fooj , ' ' );
        mvprintw( rows-1, 0 , "[%d,%d][Pos:%g]", gamesel_y, gamesel_x , filepos );

        move( rows-1, 0 );
        color_set( 2 , NULL );
        attroff( A_REVERSE );
}







///////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{

   initscr();
   keypad(stdscr, true);
   curs_set( 0 );
   noecho();
   start_color();
   init_pair(0, COLOR_WHITE, COLOR_BLACK);
   init_pair(1, COLOR_RED, COLOR_BLACK);
   init_pair(2, COLOR_GREEN, COLOR_BLACK);
   init_pair(3, COLOR_BLUE, COLOR_BLACK);
   init_pair(4, COLOR_CYAN, COLOR_BLACK);
   init_pair(6, COLOR_YELLOW, COLOR_BLACK);
   init_pair(15, COLOR_BLUE, COLOR_WHITE);
   color_set( 2, NULL );

   int ch ; 
   int rows, cols;  
   getmaxyx( stdscr, rows, cols);
   char userinp[PATH_MAX];
   int gameover_nsc = 0;
   char gamefilter[PATH_MAX];
   strncpy( gamefilter, "", PATH_MAX );
   strncpy( fileselection, "", PATH_MAX );

    int i ; 
    if ( argc >= 2)
    {
          for( i = 1 ; i < argc ; i++) 
          {
	    printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i ] );
            if ( i == 1 ) strncpy( fileselection , argv[ i ] , PATH_MAX );
          }
    }


   while ( gameover_nsc == 0)
   {
           drawit();
	   refresh();			/* Print it on to the real screen */
           ch = getch();

           if ( ch == 'q' ) 
              gameover_nsc =1 ;

           else if ( ch == 'j' ) 
              gamesel_y +=1 ;
           else if ( ch == 'k' ) 
              gamesel_y -=1 ;

           else if ( ch == 'l' ) 
              gamesel_x +=1 ;
           else if ( ch == 'h' ) 
              gamesel_x -=1 ;

           else if ( ch == 'd' ) 
              filepos +=1 ;
           else if ( ch == 'u' ) 
              filepos -=1 ;
           else if ( ch == 'g' ) 
              filepos = 1 ;

           else if ( ch == ':' ) 
           {
               strncpy( gamefilter, "" , PATH_MAX );
               strncat( gamefilter , strninput( "" ) , PATH_MAX - strlen( gamefilter ) -1 );
               strncat( gamefilter , "" , PATH_MAX - strlen( gamefilter ) -1 );
           }

    }


    curs_set( 1 );
    endwin();			/* End curses mode		  */
    return 0;
}






