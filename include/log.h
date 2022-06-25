#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdarg.h>

#define LOG_ERROR(fmt,...) do\
                           {\
                              fprintf(stderr, "%s:%s():<%d>:ERROR:",__FILE__,__func__,__LINE__);\
                              fprintf(stderr,(fmt),__VA_ARGS__);\
                              fprintf(stderr,"\n");\
                           }while(0)

#define LOG_0(fmt,...) do\
                       {\
                          fprintf(stderr, "%s:%s():<%d>:",__FILE__,__func__,__LINE__);\
                          fprintf(stderr,(fmt),__VA_ARGS__);\
                          fprintf(stderr,"\n");\
                       }while(0)

#endif /* _LOG_H */
