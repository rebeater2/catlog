/**
* @file catlog_port.c in catlog
* @author linfe
* @comment
* Create on 2023/3/16 22:57
* @version 1.0
**/


#include "catlog_port.h"
#include <stdio.h>

void catlog_open_stderr(void *p){}
void catlog_close_stderr(void *p){};
void catlog_write_to_stderr(uint8_t * buffer,uint32_t size){
    fprintf(stderr,"%s", buffer);
}


void catlog_open_device(void *p){
    /*TODO*/
}
void catlog_close_device(void *p){
    /*TODO*/
}
void catlog_write_to_device(uint8_t *buffer,uint32_t size){
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
