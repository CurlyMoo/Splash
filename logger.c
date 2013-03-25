#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#endif

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

 
FILE *fp ;
static int SESSION_TRACKER; //Keeps track of session
extern int g_logging;
extern char g_logfile[255]; 

char* print_time()
{
    time_t t;
    char *buf;
     
    time(&t);
    buf = (char*)malloc(strlen(ctime(&t))+ 1);
     
    snprintf(buf,strlen(ctime(&t)),"%s ", ctime(&t));
    
    return buf;
}
void log_print(char* filename, int line, char *fmt,...)
{
    va_list         list;
    char            *p, *r;
    int             e;

    if(g_logging==0) return;

    if(SESSION_TRACKER > 0)
      fp = fopen (g_logfile, "a+");
    else
      fp = fopen (g_logfile, "w");
     
    fprintf(fp,"%s ",print_time());
    va_start( list, fmt );
 
    for ( p = fmt ; *p ; ++p )
    {
        if ( *p != '%' )//If simple string
        {
            fputc( *p,fp );
        }
        else
        {
            switch ( *++p )
            {
                /* string */
            case 's':
            {
                r = va_arg( list, char * );
 
                fprintf(fp,"%s", r);
                continue;
            }
 
            /* integer */
            case 'd':
            {
                e = va_arg( list, int );
 
                fprintf(fp,"%d", e);
                continue;
            }
 
            default:
                fputc( *p, fp );
            }
        }
    }
    va_end( list );
    fprintf(fp," [%s][line: %d] ",filename,line);
    fputc( '\n', fp );
    SESSION_TRACKER++;
    fclose(fp);
}
