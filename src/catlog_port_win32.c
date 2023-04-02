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
#include <Windows.h>

#ifdef __MINGW32__
/*mingw 貌似不支持弱函数*/
#define CATLOG_WEAK_DECLARE
#elifdef __GNUC__
/* gcc 支持弱函数 */
#define CATLOG_WEAK_DECLARE __attribute__((weak))
#else
/*其他编译器目前没试过*/
#define CATLOG_WEAK_DECLARE
#endif

CATLOG_WEAK_DECLARE uint32_t catlog_get_sys_time_str(char *buffer){
    uint32_t res = 0;
    SYSTEMTIME t1;
    GetSystemTime(&t1);
    res = sprintf((char *) buffer,
                          "%04d/%02d/%02d %02d:%02d:%02d.%03lu ",
                          t1.wYear,
                          t1.wMonth,
                          t1.wDay,
                          t1.wHour,
                          t1.wMinute,
                          t1.wSecond,
                          t1.wMilliseconds);
    return res;
}



CATLOG_WEAK_DECLARE void  catlog_open_stderr(void *p){} ;
CATLOG_WEAK_DECLARE void catlog_close_stderr(void *p){ fflush(stderr);} ;
CATLOG_WEAK_DECLARE void catlog_write_to_stderr(uint8_t * buffer,uint32_t size) {
    fwrite(buffer,1,size,stderr);
    fflush(stderr);
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


