#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdarg.h>

#ifdef LOGGING
#define LOG_ERROR(fmt,...) do\
                           {\
                              fprintf(stderr, "ERROR: "fmt , ##__VA_ARGS__);\
                              fprintf(stderr,"\n");\
                           }while(0)

#define LOG_0(fmt,...) do\
                       {\
                          fprintf(stderr, ": "fmt, ##__VA_ARGS__);\
                          fprintf(stderr,"\n");\
                       }while(0)
#else
#define LOG_ERROR(fmt,...)
#define LOG_0(fmt,...)
#endif /* LOGGIN */
#endif /* _LOG_H */
