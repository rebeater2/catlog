/**
* @file catlog_port.h in catlog
* @author linfe
* @comment
* Create on 2023/3/16 22:57
* @version 1.0
**/

#ifndef CATLOG__CATLOG_PORT_H_
#define CATLOG__CATLOG_PORT_H_

#include "catlog.h"


void catlog_open_stderr(void *) ;
void catlog_close_stderr(void *);
void catlog_open_file(void *);
void catlog_close_file(void *);

void catlog_open_device(void *);
void catlog_close_device(void *);

void catlog_write_to_stderr(uint8_t * buffer,uint32_t size);

void catlog_write_to_file(uint8_t * buffer,uint32_t size);

void catlog_write_to_device(uint8_t *buffer,uint32_t size);

#endif //CATLOG__CATLOG_PORT_H_
