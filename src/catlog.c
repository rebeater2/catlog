/**
* @file catlog.c in catlog
* @author linfe
* @comment
* Create on 2023/3/13 23:10
* @version 1.0
**/


#include <stdarg.h>
#include <malloc.h>
#include <stdio.h>
#include "catlog.h"
#include "catlog_port.h"

#include <time.h>

static uint8_t *catlog_buffer = NULL;
static uint32_t catlog_offset = 0;

uint32_t catlog_push_out_cnts = 0;


#if CATLOG_MUTEX_LOCK_ENABLE == 1
#ifdef _MSC_VER
#error "not supported"
#else
#include <pthread.h>
#include <memory.h>
typedef pthread_mutex_t catlog_mutex_t;
#define catlog_mutex_init(mutex)  pthread_mutex_init(mutex,NULL)
#define catlog_mutex_lock(mutex)  pthread_mutex_lock(mutex)
#define catlog_mutex_unlock(mutex)  pthread_mutex_unlock(mutex)
catlog_mutex_t mutex;
#endif
#endif

void catlog_push_out() {
#if CATLOG_OUTPUT_MODE == CATLOG_OUTPUT_TO_STDERR
    catlog_write_to_stderr(catlog_buffer, catlog_offset);
#elif  CATLOG_OUTPUT_MODE == CATLOG_OUTPUT_TO_FILE
    catlog_write_to_file(catlog_buffer,catlog_offset);
#elif CATLOG_OUTPUT_MODE == CATLOG_OUTPUT_TO_DEVICE
    catlog_write_to_device(catlog_buffer,catlog_offset);
#endif
    catlog_buffer[0] = '\0';
    catlog_offset = 0;
    catlog_push_out_cnts++;
}

void catlog_init(catlog_config_t *config) {
#if CATLOG_PUSHOUT_LEVEL != CATLOG_DISABLE
    catlog_buffer = malloc(sizeof(char) * CATLOG_BUFFER_SIZE);
    catlog_offset = 0;
#if CATLOG_OUTPUT_MODE == CATLOG_OUTPUT_TO_STDERR
    catlog_open_stderr(NULL);
#elif  CATLOG_OUTPUT_MODE == CATLOG_OUTPUT_TO_FILE
    const char filename[25];
    time_t cur = time(NULL);
    struct tm *t = localtime(&cur);
    sprintf(filename,"%04d%02d%02d_%02d%02d%02d.log",
            1900 + t->tm_year,
            t->tm_mon,
            t->tm_mday,
            t->tm_hour,
            t->tm_min,
            t->tm_sec
            );
    catlog_open_file(filename);
#elif CATLOG_OUTPUT_MODE == CATLOG_OUTPUT_TO_DEVICE
    catlog_open_device(NULL);
#endif

#if CATLOG_MUTEX_LOCK_ENABLE == 1
    catlog_mutex_init(&mutex);
#endif

#endif
}

#define __PRINTF_MSG_2_BUFF(fmt)   \
{                                  \
    va_list ap;                         \
int retval;                         \
va_start(ap, fmt);                  \
retval = vsprintf((char *) catlog_buffer + catlog_offset, fmt, ap); \
va_end(ap); \
catlog_offset += retval;           \
                                   \
}

static uint32_t add_time_stamp() {
   uint32_t res = catlog_get_sys_time_str(catlog_buffer + catlog_offset);
   catlog_offset += res;
    return 0;
}

static uint32_t add_head_mark(catlog_level_t level) {
    int res = 0;
    switch (level) {
        case CATLOG_INFO:
            /*\033[0m*/
            res = sprintf((char *) catlog_buffer + catlog_offset, "\033[0m");
            break;
        case CATLOG_DEBUG:res = sprintf((char *) catlog_buffer + catlog_offset, "\033[0;32m");
            break;
        case CATLOG_WARNING:res = sprintf((char *) catlog_buffer + catlog_offset, "\033[0;33m");
            break;
        case CATLOG_ERROR:
        case CATLOG_FETAL:res = sprintf((char *) catlog_buffer + catlog_offset, "\033[0;31m");
            break;
        default:break;
    }
    catlog_offset += res;
    return 0;
}
static uint32_t add_end_mark(catlog_level_t level) {
    int res = 0;
    res = sprintf((char *) catlog_buffer + catlog_offset, "\033[0m");
    catlog_offset += res;
    return 0;
}

static uint32_t add_endline() {
#ifndef WIN32
    catlog_buffer[catlog_offset] = '\n';
    catlog_offset += 1;
#else
    catlog_buffer[catlog_offset] = '\r';
    catlog_buffer[catlog_offset+1] = '\n';
    catlog_offset += 2;
#endif
    return 0;
}
static uint32_t add_level(catlog_level_t level) {
    static char *level_table[5] = {
        "<I>", "<D>", "<W>", "<E>", "<F>"
    };
    uint32_t res = sprintf((char *) catlog_buffer + catlog_offset, "%s ", level_table[level]);
    catlog_offset += res;
    return 0;
}

static uint32_t add_function_name(const char *name) {
    uint32_t res = sprintf((char *) catlog_buffer + catlog_offset, "%s: ", name);
    catlog_offset += res;
    return res;
}

void log_impl(catlog_level_t level, const char *func_name, const char *fmt, ...) {
#if CATLOG_MUTEX_LOCK_ENABLE == 1
    catlog_mutex_lock(&mutex);
#endif
#if CATLOG_ANSI_SUPPORT == 1
    add_head_mark(level);
#endif

    add_time_stamp();
    add_level(level);

#if CATLOG_ADD_FUNCTION_NAME == 1
    add_function_name(func_name);
#endif

    __PRINTF_MSG_2_BUFF(fmt)

#if CATLOG_ANSI_SUPPORT == 1
    add_end_mark(level);
#endif
    add_endline();
#if CATLOG_CACHED_SUPPORT == 1
    if (catlog_offset > CATLOG_BUFFER_SIZE / 2) {
        catlog_push_out();
    }
#else
        catlog_buffer[catlog_offset++] = '\0';
        catlog_push_out();
#endif
#if CATLOG_MUTEX_LOCK_ENABLE == 1
    catlog_mutex_unlock(&mutex);
#endif
}

void catlog_deinit(catlog_config_t *config) {
#if CATLOG_PUSHOUT_LEVEL != CATLOG_DISABLE
    if (catlog_offset > 0) {
        catlog_push_out();
    }
#if CATLOG_OUTPUT_MODE == CATLOG_OUTPUT_TO_STDERR
    catlog_close_stderr(NULL);
#elif  CATLOG_OUTPUT_MODE == CATLOG_OUTPUT_TO_FILE
    catlog_close_file(NULL);
#elif CATLOG_OUTPUT_MODE == CATLOG_OUTPUT_TO_DEVICE
    catlog_close_device(NULL);
#endif
    free(catlog_buffer);
    catlog_buffer = NULL;
#endif
}