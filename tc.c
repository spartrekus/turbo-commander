
////////////////////////////
///  TC rocks
///  Turbo Commander
////////////////////////////

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



char searchitem[PATH_MAX];
int  tc_show_hidden = 0; 

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) 
	{
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;


            snprintf( path, sizeof(path), "%s/%s", name, entry->d_name);
            //printf("%*s[%s]\n", indent, "", entry->d_name);

            listdir( path, indent + 2);
        } 
	else 
	{
	    if ( strstr( entry->d_name , searchitem ) != 0 ) 
	    {
              printf("DIR %s\n", name );
              //printf("%*s- %s (Found)\n", indent, "", entry->d_name);
              printf("%*s- %s\n", indent, "", entry->d_name);
	    }
        }
    }
    closedir(dir);
}










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













int rows, cols;  
int nconsole_explorer = 1;
int gameselection = 1;
int gamescrolly = 0;
int gamedirfcheck = 1;
char gamefilter[PATH_MAX];
char fileselection[PATH_MAX];



void selectioninit()
{
    strncpy( fileselection, "" , PATH_MAX );
}







/////////////////// MAIN LIST FILES (MVPRINTW)
void mvlistprint(const char *name, int indent, char *searchitem )
{
    int posy = 1; 
    getmaxyx( stdscr, rows, cols);

    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    int entryselnb = 0;  int dircondition ; 
    unsigned int entrycounter = 0;
    while ((entry = readdir(dir)) != NULL) 
    {
        attroff( A_REVERSE );

        entrycounter++;
        if ( entrycounter <= gamescrolly )
              continue;

        dircondition = 0; 
        if ( entry->d_type == DT_DIR ) 
           dircondition = 1; 
        else if ( entry->d_type == 0 ) 
         if ( gamedirfcheck == 1 )
          if ( posy <= rows-3 )
           if ( fexist( entry->d_name ) == 2 )
               dircondition = 1;

        if ( dircondition == 1 )
	{
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            if ( tc_show_hidden == 0 )
             if ( entry->d_name[0] ==  '.' ) 
                continue;

            snprintf( path, sizeof(path), "%s/%s", name, entry->d_name);

            //listdir( path, indent + 2);
	    if ( strstr( entry->d_name , searchitem ) != 0 ) 
            if ( posy <= rows-3 )
            {
              entryselnb++;
              if ( gameselection == entryselnb ) attron( A_REVERSE );
              color_set( 6, NULL );
              mvprintw( posy++, 0 +1, "[%d] [%s]", entry->d_type, entry->d_name );
              if ( gameselection == entryselnb ) 
                  if ( strcmp( entry->d_name , "" ) != 0 )
                   strncpy( fileselection, entry->d_name , PATH_MAX );
             }

        } 
	else 
	{

            if ( tc_show_hidden == 0 )
              if ( entry->d_name[0] ==  '.' ) 
                continue;

	    if ( strstr( entry->d_name , searchitem ) != 0 ) 
	    {


              //printf("DIR %s\n", name );
              //printf("%*s- %s\n", indent, "", entry->d_name);
              if ( posy <= rows-3 )
              {
                 entryselnb++;
                 if ( gameselection == entryselnb ) attron( A_REVERSE );
                 color_set( 4, NULL );
                 //mvprintw( posy++, 0 +1, "%s", entry->d_name );
                 mvprintw( posy++, 0 +1, "[%d] %s", entry->d_type, entry->d_name );
                 if ( gameselection == entryselnb ) 
                  if ( strcmp( entry->d_name , "" ) != 0 )
                   strncpy( fileselection, entry->d_name , PATH_MAX );
              }
	    }
        }

    }
    closedir(dir);
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



///////////////////////////////
///////////////////////////////
void nappendclip( char *thefile )
{
     char fileinputsrc[PATH_MAX];
     strncpy( fileinputsrc, "", PATH_MAX );
     strncat( fileinputsrc , getenv( "HOME" ) , PATH_MAX - strlen( fileinputsrc ) -1 );
     strncat( fileinputsrc , "/.clipboard" , PATH_MAX - strlen( fileinputsrc ) -1 );

     FILE *fp;  
     fp = fopen( fileinputsrc , "ab+" );
       fputs( "!fig{", fp );
       fputs( thefile , fp );
       fputs( "}" , fp );
       fputs( "\n" , fp );
     fclose( fp );


}


///////////////////////////////
///////////////////////////////
void naddclip( char *thefile )
{
     char fileinputsrc[PATH_MAX];
     strncpy( fileinputsrc, "", PATH_MAX );
     strncat( fileinputsrc , getenv( "HOME" ) , PATH_MAX - strlen( fileinputsrc ) -1 );
     strncat( fileinputsrc , "/.clipboard" , PATH_MAX - strlen( fileinputsrc ) -1 );

     FILE *fp;  
     fp = fopen( fileinputsrc , "wb+" );
       fputs( "!fig{", fp );
       fputs( thefile , fp );
       fputs( "}" , fp );
       fputs( "\n" , fp );
     fclose( fp );


}





     void tc_file_mkdir( char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|Mkdir|");
                    char fooline[PATH_MAX];
                    strncpy( fooline , myfile , PATH_MAX );
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       strncpy( cmdi, " mkdir -p  " , PATH_MAX );
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );
                     }
       }




     void tc_run_sys_command( char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|System Command|");
                    char fooline[PATH_MAX];
                    strncpy( fooline , myfile , PATH_MAX );
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       /*strncpy( cmdi, " mkfile  " , PATH_MAX );
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );*/
                       printf( "Ext. Sys Command: %s\n", fooline );
                       nruncmd( fooline );
                     }
       }










     void tc_file_mkfile( char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|Mkfile|");
                    char fooline[PATH_MAX];
                    strncpy( fooline , myfile , PATH_MAX );
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       strncpy( cmdi, " mkfile  " , PATH_MAX );
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );
                     }
       }




     void tc_file_rename( char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|Rename: %s|", myfile );
                    char fooline[PATH_MAX];
                    strncpy( fooline , strninput( myfile ), PATH_MAX );

                    if ( ( fexist( myfile ) == 2 ) || ( fexist( myfile ) == 1 ) )
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       strncpy( cmdi, " mv  -v " , PATH_MAX );
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi ,  myfile  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );
                     }
       }




     void tc_file_copy( char *dirtarget , char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|Copy: %s|", myfile );
                    char fooline[PATH_MAX];
                    strncpy( fooline , strninput( myfile ), PATH_MAX );

                    if ( ( fexist( myfile ) == 2 ) || ( fexist( myfile ) == 1 ) )
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       strncpy( cmdi, " cp -r   -v " , PATH_MAX );
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi ,  myfile  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );
                     }
       }








void drawit()
{
        if ( gameselection <= 0 ) gameselection = 0;
        if ( gamescrolly <= 0 )   gamescrolly = 0;
        int fooj; 
        char foocwd[PATH_MAX];
        getmaxyx( stdscr, rows, cols);
        color_set( 2 , NULL );
        attroff( A_REVERSE );
        erase();  


        mvprintw( 0, 0, "|CONSOLE|" );
        color_set( 2 , NULL );
        attroff( A_REVERSE );

        if ( nconsole_explorer == 1 )
        {
           selectioninit();
           mvlistprint( ".", 0 , gamefilter ) ;
        }


        // bottom bar
        color_set( 15 , NULL );
        attron( A_REVERSE );
        for ( fooj = 0 ; fooj <= cols-1;  fooj++)
        {
            mvaddch( rows-2, fooj , ' ' );
            mvaddch( 0, fooj , ' ' );
        }
        mvprintw( rows-2, 0 , "|%s|", fileselection );
        if ( strcmp( gamefilter, "" ) != 0 ) 
          printw( "Filter|" );
        else
          printw( "*|" );
        printw( "%d|", gameselection );
        printw( "%d|", gamescrolly );

        // top bar
        color_set( 15 , NULL );
        attron( A_REVERSE );
        mvprintw( 0, 0 , "|%s|", " TC " );

        move( rows-1, 0 );
        color_set( 0 , NULL );
        attroff( A_REVERSE );
        mvprintw( rows-1, 0, "%s", getcwd( foocwd, PATH_MAX ) );

        move( rows-1, 0 );
        color_set( 2 , NULL );
        attroff( A_REVERSE );
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



    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( strcmp( argv[1] , "--find" ) ==  0 ) 
     {
         strncpy( searchitem, argv[ 2 ], PATH_MAX );          
         listdir( ".", 0 ) ;
         return 0;
     }




   //initscr();			
   //curs_set( 0 );
   //start_color();

   initscr();
   //raw();  //ctrl+c is with raw() disabled.
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
   strncpy( gamefilter, "", PATH_MAX );

   while ( gameover_nsc == 0)
   {
           drawit();
	   refresh();			/* Print it on to the real screen */
           ch = getch();

           if ( ch == 'q' ) gameover_nsc =1 ;

    else if ( ch ==  KEY_UP )
        gameselection--;

    else if ( ch == KEY_DOWN )
        gameselection++;

    else if ( ch ==  KEY_LEFT )
        gameselection--;

    else if ( ch ==  KEY_RIGHT )
        gameselection++;

           else if ( ch == '~' ) { chdir( getenv( "HOME" ) ); gameselection = 1;  }

           else if ( ch == '2' ) tc_file_rename( fileselection );
           else if ( ch == '5' ) tc_file_copy( "."  , fileselection );

           else if ( ch == '$' ) 
           {
                    mvprintw( 0,0, "|Run Bash System Command|");
                    tc_run_sys_command( strninput( "" ) );
           }

           else if ( ch == '7' ) 
           {
                    mvprintw( 0,0, "|Mkfile|");
                    tc_file_mkfile( strninput( "" ) );
           }
           else if ( ch == '8' ) 
           {
                    mvprintw( 0,0, "|Mkdir|");
                    tc_file_mkdir( strninput( "" ) );
           }


           else if ( ch == 'o' ) { nrunwith( " mupdf " , fileselection  ); }
           else if ( ch == 'c' ) { mvprintw(0,0,"chdir"); chdir( strninput( "" ) ); }

           else if ( ch == 's' ) { nrunwith( " feh  " , fileselection  ); }

           else if ( ch == 'p' ) { nrunwith( " tcview " , fileselection  ); }
           else if ( ch == 'r' ) { nrunwith( " tcview " , fileselection  ); }
           else if ( ch == 'R' ) { nrunwith( " ncview " , fileselection  ); }
           else if ( ch == 'P' ) { nrunwith( " mupdf " , fileselection  ); }
           else if ( ch == 'v' ) { nrunwith( " vim  " , fileselection  ); }
           else if ( ch == 't' ) { nrunwith( " tim  " , fileselection  ); }
           else if ( ch == 'x' ) { nrunwith( " xpaint " , fileselection  ); }

          //////////////////////////////
          //////////////////////////////
          //////////////////////////////
          else if ( ch ==  'm' ) 
          {
              mvprintw( 0,0, "[m]" );
              ch = getch();
              if ( ch ==  '$' )      nruncmd( " bash " );
              else if ( ch ==  'c' ) nruncmd( " bash " );
              else if ( ch ==  'b' ) nruncmd( " bash " );
              else if ( ch ==  'v' ) { nrunwith( " vim  " , fileselection  ); }
          }

          else if  ( ( ch == 'a' ) )
          // || ( ch == 'm' ) )
          {
           mvprintw( 0, 0, "|APPS: (f)eh; (l)ess; less (a); (n)ano; (b)ash; (v)im;|");
           mvprintw( 1, 0, "|APPS: m(p)layer; (m)pg123;|");
           mvprintw( 2, 0, "|APPS: (o) open with mupdf;(t) pdftotext;|");
           mvprintw( 3, 0, "|APPS: (e)xplorer ROX; |");
           ch = getch(); 
           if ( ch == 'f' ) { nrunwith( " feh  " , fileselection  ); }
           else if ( ch == 32 )  { chdir( getenv( "HOME" ) ); gameselection = 1;  }
           else if ( ch == 'e' ) { nruncmd( " screen -d -m rox " ); }
           else if ( ch == 'o' ) { nrunwith( " screen -d -m mupdf " , fileselection  ); }
           else if ( ch == 'a' ) { nrunwith( " less " , fileselection  ); }
           else if ( ch == 't' ) { nrunwith( " pdftotext " , fileselection  ); }
           else if ( ch == 'l' ) { nrunwith( " less " , fileselection  ); }
           else if ( ch == 'n' ) { nrunwith( " nano  " , fileselection  ); }
           else if ( ch == 'p' ) { nrunwith( " mplayer ", fileselection  ); }
           else if ( ch == 'm' ) { nrunwith( " mpg123 " , fileselection ); }
           else if ( ch == 'v' ) nvim( fileselection );
           else if ( ch == 'b' ) { nruncmd( " bash "  ); }
           else if ( ch == 'e' ) { nruncmd( " rox "  ); }
          }

          else if ( ch == '!' ) { nrunwith( strninput( "" ) , fileselection  ); }

           else if ( ch == 'g' ) 
           {  mvprintw( rows-1, cols-1, "g" );
              ch = getch(); 
              if ( ch == 'o' ) { chdir( strninput( "" ) ); gameselection = 1;  }
              else if ( ch == 'g' ) { gameselection = 1; gamescrolly = 0 ; }
           }


           else if ( ch == 'm' ) 
           {  mvprintw( rows-1, cols-1, "m" );
              ch = getch(); 
              if ( ch == 'o' ) { chdir( strninput( "" ) ); gameselection = 1;  }
           }

           else if ( ch == 'h' ) { chdir( ".." ); 
             strncpy( gamefilter,  "" , PATH_MAX );
             gameselection = 1;  gamescrolly = 0 ;  }

           else if ( ch == 'l' )
            { chdir( fileselection ); 
             strncpy( gamefilter,  "" , PATH_MAX );
             gameselection=1;   gamescrolly = 0;   }

           else if ( ch == 'k' ) 
               gameselection--;
           else if ( ch == 'j' ) 
               gameselection++; 

         else if ( ch == '?' )
         {
             erase();
             mvprintw( 1, 0 , "|TC| " );
             getch();
         }

           else if ( ch == KEY_PPAGE )   gamescrolly-=4;  
           else if ( ch == KEY_NPAGE )   gamescrolly+=4; 
           else if ( ch == 'u' )   gamescrolly-=4;  
           else if ( ch == 'd' )   gamescrolly+=4; 
           else if ( ch == 'n' )   gamescrolly+=4; 

           //else if ( ch == 'u' ) gameselection-=4;  
           //else if ( ch == 'd' ) gameselection+=4; 

           else if ( ch == 'f' ) 
           {
             strncpy( gamefilter, strninput( "" ), PATH_MAX );
             gameselection=1; 
           }

           else if ( ch ==  32 )  strncpy( gamefilter, "" , PATH_MAX );
           // else if ( ch ==  'c' ) nruncmd( " bash " );
           // else if ( ch ==  'b' ) nruncmd( " echo build ; make " );

           else if ( ch ==  'y' ) naddclip( fileselection );
           else if ( ch ==  'Y' ) nappendclip( fileselection );

           else if ( ch ==  '%' ) 
           {
               if ( gamedirfcheck == 0 )
                   gamedirfcheck = 1; 
               else
                   gamedirfcheck = 0;
           }

           else if ( ch ==  '&' ) 
           {
               if ( tc_show_hidden == 0 )
                   tc_show_hidden = 1; 
               else
                   tc_show_hidden = 0;
           }


 
    }

    curs_set( 1 );
    endwin();			/* End curses mode		  */
    return 0;
}



