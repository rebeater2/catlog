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
#include "fatfs.h"

#define CATLOG_WEAK_DECLARE

CATLOG_WEAK_DECLARE uint32_t catlog_get_sys_time_str(char *buffer){
    uint32_t res = 0;
    /* TODO!: add function to  get timestamp in char for RTOS,
     * which can be implemented in user code */
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


static FIL *fp;
void catlog_open_file(void *p){
    char *filename = (char *)p;
    fp = f_open(filename,"w");
}
void catlog_close_file(void *p){
    f_close(fp);
}
void catlog_write_to_file(uint8_t * buffer,uint32_t size){
    f_write(buffer,1,size,fp);
}


