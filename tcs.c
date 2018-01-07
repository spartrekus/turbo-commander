
////////////////////////////////
////////////////////////////////
////////////////////////////////
////////////////////////////////


//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
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





static int compare_fun( const void *p, const void *q)
{
  const char *l = p ; 
  const char *r = q ; 
  int cmp; 
  cmp = strcmp( l, r );
  return cmp; 
}


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




////////////////////////////////
void nruncmd( char *theprg )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , "   " , PATH_MAX );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , theprg , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
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






void nstartncurses_color_2(  )
{
    initscr();	
    curs_set( 0 );
//      init_pair(1, COLOR_RED, COLOR_BLACK);
//      init_pair(2, COLOR_GREEN, COLOR_BLACK);
//      init_pair(3, COLOR_BLUE, COLOR_BLACK);
//      init_pair(4, COLOR_CYAN, COLOR_BLACK);
  //getmaxyx( stdscr, rows, cols);
  noecho();            
  keypad( stdscr, TRUE ); 
  start_color();
  init_pair(0,  COLOR_WHITE,     COLOR_BLACK);
  init_pair(1,  COLOR_RED,     COLOR_BLACK);
  init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
  init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
  init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
  init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
  init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
  init_pair(8,  COLOR_WHITE,   COLOR_RED);
  init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
  init_pair(10, COLOR_BLUE,  COLOR_YELLOW   );
  init_pair(11, COLOR_WHITE,   COLOR_BLUE);
  init_pair(12, COLOR_YELLOW,   COLOR_BLUE);
  init_pair(13, COLOR_BLACK,   COLOR_CYAN);
  init_pair(14, COLOR_BLUE,   COLOR_GREEN);
  init_pair(15, COLOR_BLUE, COLOR_CYAN );
  init_pair(16, COLOR_CYAN, COLOR_WHITE );
  init_pair(17, COLOR_CYAN, COLOR_YELLOW );
  init_pair(18, COLOR_CYAN, COLOR_BLUE);
  init_pair( 19, COLOR_MAGENTA , COLOR_BLUE);
  init_pair( 20 , COLOR_RED , COLOR_BLUE);
  init_pair( 21 , COLOR_BLUE , COLOR_YELLOW);
  init_pair( 22, COLOR_YELLOW,   COLOR_CYAN);
  init_pair( 23, COLOR_WHITE, COLOR_BLUE);
}








    int showhiddenfiles = 0;
    unsigned filemax = 0;
    unsigned n=0;
    char idata[1240][250];
    DIR *dirp;
    struct dirent *dp;

    int selection = 0 ; 
    int selectionmax = 0 ; 
    int scrolly=0; 


void loadlist()
{
    char filedata[250];
    int  filedatalen = 0;
    n = 0 ; 
    filemax = 0; 
    dirp = opendir( "." );
    strncpy( idata[ n++ ] , ".." , 250 );
    while  ((dp = readdir( dirp )) != NULL  &&  
           n < sizeof idata / sizeof idata[ 0 ]) 
	   {
            strncpy( filedata , dp->d_name , 250 );
	    filedatalen = strlen( filedata ) -1;
            if ( strcmp( dp->d_name , "." ) != 0 )
            if ( dp->d_name[0] != '.' ) 
            {
              strncpy( idata[ n++ ] , dp->d_name , 250 );
            }
    }
    filemax = n-1 ; 
    closedir( dirp );

    if ( n > 1 )
      qsort( idata, n , sizeof idata[0], compare_fun );

    selectionmax = filemax ;
    if ( selection >= selectionmax ) selection = 0;
   }



   void checkvars(){
      if ( selection <= 0 ) selection = 0;
      if ( scrolly <= 0 ) scrolly = 0;
      if ( selection >= selectionmax ) selection = selectionmax; 
   }


   void drawit(){
    // clear();
    erase();
    color_set( 0, NULL );
    int posy=2;
    for( n = 0 ; n <= filemax ; n++)
    {
        if ( n >= scrolly )  
        if ( posy <= rows-3 )  
        {
          color_set( 0, NULL );
          if ( strstr( idata[n], "freemario" ) != 0 ) color_set( 6, NULL );   //cyan
          if ( selection == n ) mvprintw( posy , 0, ">" );
          if ( selection == n ) attron(  A_REVERSE );
          if ( fexist( idata[ n ] ) == 2 )
            mvprintw( posy , 1, "[%s]", idata[ n ] );
          else
            mvprintw( posy , 1, "%s", idata[ n ] );
          posy++;
          attroff(  A_REVERSE );
          color_set( 0, NULL );
        }
    }
   }






   void gfxhline( int posyy )
   {
      int foo;
      for( foo = 0 ; foo <= cols-1 ; foo++)   
          mvaddch( posyy , foo , ' ');
   }





   void mvfulllinereverse( int posyy ){
    attron(  A_REVERSE ); 
     int foo;
    for( foo = 0 ; foo <= cols-1 ; foo++) mvaddch( posyy , foo , ' ');
    attroff( A_REVERSE );
   }

   void displaystatus(){
    char cwd[PATH_MAX];
    mvfulllinereverse( 0 ); 
    attron(  A_REVERSE ); 
    mvaddch( 0 , 1,  ' ' );
    printw( "TCS (TINY) %d/%d", selection, selectionmax );
    addch(  ACS_DARROW);
    printw( ":j  ");
    addch(  ACS_UARROW);
    printw( ":k  ");
    addch(  ACS_ULCORNER );
    printw( ":g  ");
    addch(  ACS_DIAMOND);
    printw( ":o  ");
    attroff( A_REVERSE );
    mvfulllinereverse( rows-2 ); 
    mvfulllinereverse( rows-1 ); 
    attron( A_REVERSE );
    mvprintw(rows-2 , 0, "PATH: %s", getcwd( cwd, PATH_MAX ) );
    mvprintw(rows-1 , 0, "User:%s, Selection #%d/%d, P:%d, PD:%s" , getenv( "USER" ) ,  selection+1, selectionmax+1, scrolly, idata[ selection ] );
    attroff( A_REVERSE );
   }


void chdirhome()
{
                  selection = 0;  
                  scrolly=0;
                  chdir( getenv( "HOME" ));
}


///////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{
    ////////////////////////////////////////////////////////
    if ( argc == 2)
      if ( strcmp( argv[1] , "" ) !=  0 )
       {
          chdir( argv[ 1 ] );
       }

	
    char line[250];
    char cmdi[PATH_MAX];
    char gametype[PATH_MAX];
    int  i;
    strncpy( gametype , " tcstart " , PATH_MAX );
    char filetarget[250];
    char cwd[PATH_MAX];
    char pathbefore[PATH_MAX];
    strncpy( pathbefore , getcwd( cwd, PATH_MAX ) , PATH_MAX );
    int foo ;
    char pathmem[12][PATH_MAX];
    for( foo = 0 ; foo <= 10 ; foo++)
    {
      strncpy( pathmem[foo] , getcwd( cwd, PATH_MAX ) , PATH_MAX );
    }

    /////////////
    loadlist();

   // initscr();			/* Start curses mode 		  */
   // curs_set( 0 );
   nstartncurses_color_2(  ); 

    int ch ; 
    getmaxyx( stdscr, rows, cols);



   selection = 1 ;
   selection = 0;  scrolly=0; 
   getmaxyx( stdscr, rows, cols);


   int menu_gameover = 0;
   while ( menu_gameover == 0 ){ 
        checkvars();
        drawit();
        displaystatus();
	ch = getch();			/* Wait for user input */
        switch( ch ){

               case 'q':
               case 'Q':
               case KEY_F(10):
                  menu_gameover = 1;
                  break;

               case 't':
                  nrunwith( " tim " , idata[ selection ]  ); 
                  break;

               case 'v':
                  nrunwith( " vim " , idata[ selection ]  ); 
                  break;

               case 'r':
                  nrunwith( " tcview " , idata[ selection ]  ); 
                  break;

               case 'c':
                  attroff( A_REVERSE ); gfxhline( 0 ); attron( A_REVERSE );
                  mvprintw( 0, 0 , "CHDIR" );
                  selection = 0;  
                  scrolly=0;
                  chdir(  strninput( "" ));
                  loadlist();
                  break;

               case '!':
                  nrunwith(  strninput( "" ) , idata[ selection ]  ); 
                  loadlist();
                  break;

               case 'L':
               case '#':
                  getmaxyx( stdscr, rows, cols);
                  loadlist();
                  break;

               case 27:
                  selection = 1 ;
                  selection = 0;  scrolly=0; 
                  getmaxyx( stdscr, rows, cols);
                  loadlist();
                  break;

               case 'G':
                  selection = selectionmax ;
                  break;



	       case 10:
                 if ( fexist( idata[ selection ] ) == 1 )
                 {
                   strncpy( cmdi, " " , PATH_MAX );
                   strncat( cmdi , gametype , PATH_MAX - strlen(cmdi) - 1);
                   strncat( cmdi ,  " \"" , PATH_MAX - strlen(cmdi) - 1);
                   strncat( cmdi ,   idata[ selection ] , PATH_MAX - strlen(cmdi) - 1);
                   strncat( cmdi ,  "\"  " , PATH_MAX - strlen(cmdi) - 1);
                   strncat( cmdi , " " , PATH_MAX - strlen(cmdi) - 1);
                 }
                 break;

               case 'g':
                  mvprintw(0,0,"[g]");
                  attroff( A_REVERSE ); gfxhline( 0 ); attron( A_REVERSE );
                  mvprintw( 0, 0 , "|g|" );
                  ch = getch();
                  if      ( ch == 'g' ) { selection = 0;  scrolly=0; }
                  else if ( ch == 'G' ) { selection = selectionmax ; }
                  else if ( ch == 'c' ) {  nrunwith( " bash " , ""  );  }
                  else if ( ch == 'l' ) {  nrunwith( " demoscr " , ""  );  }
                  else if ( ch == ' ' ) {  chdirhome(); }
                  loadlist();
                  break;

               case '"':
               case 'p':
                  mvprintw( 0, 0, "[STO MEM (PILE #1-9)?]" ) ;
                  refresh();
                  ch = getch();
                  foo = ch - 48 ;
                  if ( foo >= 1 )
                  if ( foo <= 9 )
                  { // chdir( pathmem[foo] );
                     mvprintw( 0, 0, "[STO MEM #%d]" , foo ) ;
                     strncpy( pathmem[foo] , getcwd( cwd, PATH_MAX ) , PATH_MAX );
                     loadlist();
                  }
                 break;

               case '1':
               case '2':
               case '3':
               case '4':
               case '5':
               case '6':
               case '7':
               case '8':
               case '9':
                  foo = ch - 48 ;
                  mvprintw( 0, 0, "[REC MEM #%d]" , foo ) ;
                  if ( foo >= 1 )
                  if ( foo <= 9 )
                  {  chdir( pathmem[foo] );
                     selection = 0;
                     loadlist();
                  }
                  break;

               case 'b':
                  mvprintw(0,0,"[b]");
                  ch = getch();
                  if      ( ch == 'g' ) {  chdir( pathbefore );
                                           loadlist();
                                        }
                  break;


               case 'j':
                  selection++;
                  break;
               case 'k':
                  selection--;
                  break;


               case 'd':
               case 'n':
                  selection+= 4;
                  scrolly+= 4;
                  break;
               case 'u':
                  selection-= 4;
                  scrolly-= 4;
                  break;



               case '<':
                   chdir( ".." );
                   selection = 0; 
                   selection = 0;  scrolly=0; 
                   loadlist();
                   break;
               case '>':
                  if ( fexist( idata[ selection ] ) == 2 )
                  {
                    chdir( idata[ selection ] ); 
                    selection = 0;  scrolly=0; 
                    loadlist();
                  }
                  break;



               case 'h':
                   chdir( ".." );
                   selection = 0; 
                   selection = 0;  scrolly=0; 
                   loadlist();
                   break;



               case 'l':
                  if ( fexist( idata[ selection ] ) == 2 )
                  {
                    chdir( idata[ selection ] ); 
                    selection = 0;  scrolly=0; 
                    loadlist();
                  }
                  break;




               case 'm':
                  mvprintw(0,0,"[m]");
                  attroff( A_REVERSE ); gfxhline( 0 ); attron( A_REVERSE );
                  mvprintw( 0, 0 , "|m|" );
                  ch = getch();

                  if ( ch == '~' ) 
                  { 
	               chdir( getenv( "HOME" ));
	               loadlist();
                  }


                  else if ( ch == 't' ) 
                  { 
		         chdir( "/tmp/" );
                         selection = 0;  scrolly=0; 
			 loadlist();
                  }

                  else if ( ch == 's' ) 
                  { 
                      loadlist();
                  }
                  else if ( ch == 'b' ) 
                  { 
                      loadlist();
                  }
                  else if ( ch == 'c' ) 
                  { 
                      nruncmd( " bash  " );
                      loadlist();
                  }
                  else if ( ch == 'n' ) 
                  { 
                      loadlist();
                  }
                  break;


        }
       }

      curs_set( 1 );
      endwin();			/* End curses mode		  */
      return 0;
}


