#include <stdarg.h>
#include "mcc.h"

void mccerr(int code, tokenp tok)
{
 char *text;
 static char *fmt = "ERROR: \"%s\" %d:%d : ";
 if (tok && tok->text)
   text = tok->text;
  else
   text = "";
 MCCWRITE(MCCERRF,fmt, 3, mccsrc->pathname, tok->sourceLoc.line,
                    tok->sourceLoc.column);
 MCCWRITE(MCCERRF,mccerrmsg[code], 1, text);
 if (mccoption[MCCOPTLISTING])
   {
     MCCWRITE(MCCLISTF,fmt, 3, mccsrc->pathname,tok->sourceLoc.line,
                    tok->sourceLoc.column);
     MCCWRITE(MCCLISTF,mccerrmsg[code],1, text);
   }
 mccerrcount++;
}

void mccwarning(int code, tokenp tok)
{
 char *text;
 static char *fmt = "WARNING: \"%s\" %d:%d : ";
 if (tok && tok->text)
   text = tok->text;
  else
   text = "";
 MCCWRITE(MCCERRF,fmt, 3,       
                 (mccsrc) ? mccsrc->pathname : "",
                 tok->sourceLoc.line,tok->sourceLoc.column);
 MCCWRITE(MCCERRF,mccerrmsg[code],1,text);
 if (mccoption[MCCOPTLISTING])
   {
     MCCWRITE(MCCLISTF,fmt, 3,
                 (mccsrc) ? mccsrc->pathname : "",
                 tok->sourceLoc.line,tok->sourceLoc.column);
     MCCWRITE(MCCLISTF,mccerrmsg[code],1,text);
   }
 mccwarningcount++;
}

void mccwrite(FILE *fd, char *fmt, int n, ...)
{
    char *aString = "";
  va_list args;
  va_start(args, n);
    if ( n > 1 )
        printf("mccwrite with more than 1 argument: %d\n",n);
    for ( int x = 0; x < n; x++ )
    {
      aString = va_arg ( args, char* );
    }
    va_end ( args );                  // Cleans up the list
    
  char linebuf[5000];
  sprintf(linebuf,fmt,aString);
  if (fd == MCCLISTF && mcclistInPmode)
    {
     mcclistInPmode = FALSE;
     fputs("\n",fd);
    }
  fputs(linebuf,fd);
}

void mccwriteTypes(FILE *fd, char *fmt, int typePattern, int n, ...)
{
  va_list args;          // incoming arg list
    int   int1,  int2,  int3,  int4;
    int   int5,  int6, int7 , int_8 ;
    long  long1, long2, long3, long4, long5, long6, long7, long8 ;
  char *str1, *str2, *str3, *str4, *str5, *str6;
    double double1, double2, double3, double4, double5, double6, double7, double8 ;
    
  va_start(args, n);
    
  char linebuf[5000];
  switch (typePattern )
  {
      case mccwriteTypesS:
        {
          str1 = va_arg( args, char* );
          sprintf(linebuf,fmt,str1);
          break;
        }
      case mccwriteTypesSS:
        {
          str1 = va_arg( args, char* );
          str2 = va_arg( args, char* );
          sprintf(linebuf,fmt,str1,str2);
        }
          break;
        case mccwriteTypesNN:
          {
            long1 = va_arg( args, long );
            long2 = va_arg( args, long );
            sprintf(linebuf,fmt,long1,long2);
          }
            break;
      case mccwriteTypesSSNS:
      {
          str1 = va_arg( args, char* );
          str2 = va_arg( args, char* );
          long3 = va_arg( args, long );
          str4 = va_arg( args, char* );
          sprintf(linebuf,fmt,str1,str2,long3,str4);
      }
          break;
      case mccwriteTypesNSSN:
      {
          long1 = va_arg( args, long );
          str2 = va_arg( args, char* );
          str3 = va_arg( args, char* );
          long4 = va_arg( args, long );
          sprintf(linebuf,fmt,long1,str2,str3,long4);
      }
          break;
      case mccwriteTypesSSNNNNFN:
          {
              str1 = va_arg( args, char* );
              str2 = va_arg( args, char* );
              long3 = va_arg( args, long );
              long4 = va_arg( args, long );
              long5 = va_arg( args, long );
              long6 = va_arg( args, long );
              double7 = va_arg( args, double );
              long8 = va_arg( args, long );
              sprintf(linebuf,fmt,str1,str2,long3, long4, long5, long6, double7,long8 );
          }
      default:
          sprintf(linebuf,fmt,args);
  }
  va_end ( args );                  // Cleans up the list


  if (fd == MCCLISTF && mcclistInPmode)
    {
     mcclistInPmode = FALSE;
     fputs("\n",fd);
    }
  fputs(linebuf,fd);
}

