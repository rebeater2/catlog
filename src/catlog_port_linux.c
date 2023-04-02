//
// Created by linfe on 2023/4/2.
//
/**
* @file catlog_port.c in catlog
* @author linfe
* @comment
* Create on 2023/3/16 22:57
* @version 1.0
**/

#include "catlog_port.h"
#include <stdio.h>
#include <sys/time.h>
#include <time.h>


#ifdef __GNUC__
/* gcc 支持弱函数 */
#define CATLOG_WEAK_DECLARE __attribute__((weak))
#else
/*其他编译器目前没试过*/
#define CATLOG_WEAK_DECLARE
#endif

CATLOG_WEAK_DECLARE uint32_t catlog_get_sys_time_str(char *buffer){
    uint32_t res;
    time_t cur = time(NULL);
    struct tm *t = localtime(&cur);
    struct timeval tv;
    gettimeofday(&tv,NULL);
    res = sprintf((char *) buffer,
                  "%04d/%02d/%02d %02d:%02d:%02d.%03lu ",
                  1900 + t->tm_year,
                  t->tm_mon,
                  t->tm_mday,
                  t->tm_hour,
                  t->tm_min,
                  t->tm_sec,
                  tv.tv_usec/1000);
    return res;
}



CATLOG_WEAK_DECLARE void catlog_open_stderr(void *p){} ;
CATLOG_WEAK_DECLARE void catlog_close_stderr(void *p){ fflush(stdout);} ;
CATLOG_WEAK_DECLARE void catlog_write_to_stderr(uint8_t * buffer,uint32_t size) {
    fwrite(buffer,1,size,stdout);
    fflush(stdout);
}


CATLOG_WEAK_DECLARE void catlog_open_device(void *p){
    /*TODO*/
}
CATLOG_WEAK_DECLARE void catlog_close_device(void *p){
    /*TODO*/
}
CATLOG_WEAK_DECLARE void catlog_write_to_device(uint8_t *buffer,uint32_t size){
    /*TODO*/
}


static FILE *fp;
void catlog_open_file(void *p){
    char *filename = (char *)p;
    fp = fopen(filename,"w");
}
void catlog_close_file(void *p){
    fclose(fp);
}
void catlog_write_to_file(uint8_t * buffer,uint32_t size){
    fwrite(buffer,1,size,fp);
}


