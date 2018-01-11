

/////////////////
/// NCONTACTS
/////////////////

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

int usersel = 1;
int userscrolly = 0;
int usermaxlist = 0;
char thefilename[DATAMAX];
char userselline[PATH_MAX];

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



int strcount( char *str , int mychar )
{  
      int return_strcount = 0;
      char ptr[strlen(str)+1];
      int i,j = 0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == mychar ) return_strcount++;
      } 
      return return_strcount;
}






///////////////////////////////
///////////////////////////////
///////////////////////////////
char *strtimestamp()
{
      long t;
      struct tm *ltime;
      time(&t);
      ltime=localtime(&t);
      char charo[50];  int fooi ; 
      fooi = snprintf( charo, 50 , "%04d%02d%02d-%02d%02d%02d",
	1900 + ltime->tm_year, ltime->tm_mon +1 , ltime->tm_mday, 
	ltime->tm_hour, ltime->tm_min, ltime->tm_sec 
	);
    size_t siz = sizeof charo ; 
    char *r = malloc( sizeof charo );
    return r ? memcpy(r, charo, siz ) : NULL;
}






/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
char *strstring2nbr(char *str)
{  
      char ptr[ 5* strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == '1' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '2' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '2' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '3' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '4' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '5' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '6' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '7' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '8' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '9' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '0' ) 
          ptr[j++]=str[i];
        else if ( str[i] == '-' ) 
          ptr[j++]=str[i];
        else if ( str[i] == 'i' ) 
          ptr[j++]=str[i];
        else if ( str[i] == 'd' ) 
          ptr[j++]=str[i];
        else
	{
	}
      } 
      ptr[j]='\0';
      size_t siz = 1 + sizeof ptr ; 
      char *r = malloc( 1 +  sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}



void ncontacts_saveappend( char *mystring )
{
    FILE *fp5;
    fp5 = fopen( thefilename , "ab+");
        fputs( mystring, fp5 );
        fputs( "\n", fp5 );
    fclose( fp5 );
}



///////////////////////////////////////////////////////////////////
void filerawcat(  char *fileout, char *filein )
{
  int fetchi;
  FILE *fp5;
  FILE *fp6;
  char fetchline[PATH_MAX];
  char fetchlinetmp[PATH_MAX];

  /////////////////////////////////////////////////
  if ( fexist( filein ) == 1 )
  {
    fp5 = fopen( fileout , "ab+");
    fp6 = fopen( filein , "rb");
    while( !feof(fp6) ) 
    {
          fgets(fetchlinetmp, PATH_MAX, fp6); 
          strncpy( fetchline, "" , PATH_MAX );
          for( fetchi = 0 ; ( fetchi <= strlen( fetchlinetmp ) ); fetchi++ )
            if ( fetchlinetmp[ fetchi ] != '\n' )
              fetchline[fetchi]=fetchlinetmp[fetchi];

         if ( !feof(fp6) )
         {
 	      fputs( fetchline , fp5 );
  	      fputs( "\n", fp5 );
	 }
     }
     fclose( fp5 );
     fclose( fp6 );
   }
}





/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
char *strsplit(char *str , int mychar , int myitemfoo )
{  
      char ptr[strlen(str)+1];
      int myitem = myitemfoo +1;
      int i,j=0;
      int fooitem = 0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == mychar ) 
           fooitem++;
        else if ( str[i] != mychar &&  fooitem == myitem-2  ) 
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}
/// customed one
char *strdelimit(char *str , int mychar1, int mychar2,  int mycol )
{ 
      char ptr[strlen(str)+1];
      char ptq[strlen(str)+1];
      strncpy( ptr, strsplit( str, mychar1 , mycol+1 ), strlen(str)+1 );
      strncpy( ptq, strsplit( ptr, mychar2 , 1 ), strlen(str)+1 );
      size_t siz = sizeof ptq ; 
      char *r = malloc( sizeof ptq );
      return r ? memcpy(r, ptq, siz ) : NULL;
}







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







   void gfxhline( int gfxposyy )
   {
      int gfxfoo;
      for( gfxfoo = 0 ; gfxfoo <= cols-1 ; gfxfoo++)   
          mvaddch( gfxposyy , gfxfoo , ' ');
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









///////////////////////
///////////////////////
///////////////////////
///////////////////////
void ncontacts_print()
{
  int fetchi;
  char filein[PATH_MAX]; 
  strncpy( filein, thefilename , PATH_MAX );
  FILE *fp6;
  char fetchline[PATH_MAX];
  char fetchlinetmp[PATH_MAX];
  char fetchlinecut[PATH_MAX];
  int posy = 2;

  attroff( A_REVERSE ); attroff( A_BOLD );
  int filecounter = 0;
  int tobi;
  /////////////////////////////////////////////////
  if ( fexist( filein ) == 1 )
  {
    fp6 = fopen( filein , "rb");
    while( !feof(fp6) ) 
    {
          fgets(fetchlinetmp, PATH_MAX, fp6); 
          filecounter++;
          strncpy( fetchline, "" , PATH_MAX );
          for( fetchi = 0 ; ( fetchi <= strlen( fetchlinetmp ) ); fetchi++ )
            if ( fetchlinetmp[ fetchi ] != '\n' )
              fetchline[fetchi]=fetchlinetmp[fetchi];

          strncpy( fetchlinecut, strcut( fetchline, 1, cols -2 ) , PATH_MAX );
          //strncpy( fetchlinecut, fetchline, PATH_MAX );

         if ( !feof(fp6) )
         if ( posy <= rows-2 )
         if ( filecounter >= userscrolly )
         {
             usermaxlist = filecounter; 
             attroff( A_REVERSE );  
             if ( filecounter == usersel ) {move( posy, 0);  printw( "> " );}
             if ( filecounter == usersel ) attron( A_REVERSE );  
             if ( filecounter == usersel ) strncpy( userselline, fetchline , PATH_MAX );
 
 	     //move( posy, 0); gfxhline( posy );
 	     move( posy, 2);  
             for( tobi = 2; tobi <= strcount( fetchlinecut , ';' ) ; tobi++)
             { 
 	         //mvprintw( posy++, 0, "%s", fetchline );
 	         printw( "%s", strsplit( fetchlinecut , ';', tobi ) );
 	         //printw( " ; " );
 	         printw( "%c", 9  );
             }
             posy++;
	 }
     }
     fclose( fp6 );
   }
}


////////////////////////////////
void nvim( char *thecmd   )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , " vi   " , PATH_MAX );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
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







void ncontacts_checkvar()
{
   if ( usersel <= 0 ) usersel = 1;
   if ( userscrolly <= 0 ) userscrolly = 0;
   if ( usersel >= usermaxlist ) usersel = usermaxlist;
}






void ncontacts_draw()
{
  erase();
  attron( A_REVERSE );
  gfxhline( 0 );
  mvprintw( 0 , 0, "|NCONTACTS|" );
  attroff( A_REVERSE );
  if ( fexist( thefilename )  == 1 ) ncontacts_print();
  attron( A_REVERSE );
  gfxhline( rows-1 );
  mvprintw( rows-1 , 0, "|%s (%d)|%d/%d|", thefilename,  fexist( thefilename ),
  usersel, usermaxlist );
  attroff( A_REVERSE );
}





int main( int argc, char *argv[])
{
    int i ;  
    if ( argc >= 2)
    {
          for( i = 1 ; i < argc ; i++) 
          {
	    printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i ] );
          }
    }



    int toxi;
    printf( "NCONTACTS \n" );
    ////////////////////////////////////////////////////////
    if ( argc == 1)
    {
        printf( "File Source Missing\n" );
        return 0;
    }

    strncpy( thefilename, "ncontacts.csv" , PATH_MAX );

    if ( argc >= 2)
    if ( fexist( argv[1] ) == 1 )
    {
       strncpy( thefilename, argv[ 1 ] , PATH_MAX );
    }

  printf( "File Source: %s\n", thefilename );

  initscr();			
  char foostring[PATH_MAX];
  keypad(stdscr, true);
  noecho();
  curs_set( 0 );
  int ch = 0 ; 
  char foocmd[PATH_MAX];

  int gameover = 0;
  strncpy( userselline, "", PATH_MAX );
  while ( gameover == 0 )
  {
    getmaxyx( stdscr, rows, cols );
    attroff( A_REVERSE );
    ncontacts_checkvar();
    ncontacts_draw();
    attroff( A_REVERSE );
    ch = getch();
    switch( ch )
    {
         case 'q':
         gameover = 1;
         break;

         case 'j':
         usersel += 1;
         break;
         case 'k':
         usersel -= 1;
         break;

         case 'g':
         usersel = 1;
         userscrolly = 0;
         break;

         case 'd':
         usersel += 4;
         userscrolly += 4;
         break;

         case 'u':
         usersel -= 4;
         userscrolly -= 4;
         break;

         case '$':
         nruncmd( "bash" );
         break;

         case 't':
         nvim( thefilename );
         break;

         case 'r':
         strncpy( foostring, strsplit( userselline ,  ';' ,  1 ) , PATH_MAX );
         if ( strcmp( foostring, "" ) != 0 )
         {
           nruncmd( " mkdir data  ");
           strncpy( foocmd , "data/" , PATH_MAX );
           strncat( foocmd , strstring2nbr( foostring ) , PATH_MAX - strlen( foocmd ) -1 );
           strncat( foocmd , "-data.txt" , PATH_MAX - strlen( foocmd ) -1 );
           if ( fexist( foocmd ) == 1 ) nrunwith( " tcview ", foocmd );
         }
         break;

         case 'e':
         case 'v':
         strncpy( foostring, strsplit( userselline ,  ';' ,  1 ) , PATH_MAX );
         if ( strcmp( foostring, "" ) != 0 )
         {
           nruncmd( " mkdir data  ");
           strncpy( foocmd , "data/" , PATH_MAX );
           strncat( foocmd , strstring2nbr( foostring ) , PATH_MAX - strlen( foocmd ) -1 );
           strncat( foocmd , "-data.txt" , PATH_MAX - strlen( foocmd ) -1 );
           nvim( foocmd );
         }
         break;

         case 'a':
         attroff( A_REVERSE ); gfxhline( 0 ); mvprintw( 0, 0, "ADD?" );
         strncpy( foocmd , "" , PATH_MAX );
         strncat( foocmd , "id-" , PATH_MAX - strlen( foocmd ) -1 );
         strncat( foocmd , strtimestamp() , PATH_MAX - strlen( foocmd ) -1 );
         strncat( foocmd , ";" , PATH_MAX - strlen( foocmd ) -1 );
         for( toxi = 1 ; toxi <= 4 ; toxi++) 
         {
           strncat( foocmd , strninput( "" ) , PATH_MAX - strlen( foocmd ) -1 );
           strncat( foocmd , ";" , PATH_MAX - strlen( foocmd ) -1 );
         }
         attroff( A_REVERSE ); gfxhline( rows-1 ); 
         attron( A_REVERSE ); gfxhline( 2 );
         gfxhline( 3 );
         mvprintw( 2, 0, "Confirm [Y/N]?" );
         mvprintw( 3, 0, "Add item: %s" , foocmd );
         ch = getch();
         if ( ( ch == '1' ) || ( ch == 'y' )) 
         {
             ncontacts_saveappend(  foocmd  );
         }
         break;


         case ':':
         strncpy( foostring, strninput( "" ) , PATH_MAX );
         break;

         case 'I':
         erase();
         strncpy( foostring, strsplit( userselline ,  ';' ,  1 ) , PATH_MAX );
         mvprintw( 1, 0, "%s", foostring ); 
         mvprintw( 4, 0, "items: %s", strcount( userselline, ';' ) ); 
         mvprintw( 5, 0, "Length: %s", strlen( userselline ) ); 
         getch();
         break;
    }
  }

  curs_set( 1 );
  endwin();			/* End curses mode		  */
  return(0);
}





