/**
* @file catlog_conf.h in catlog
* @author linfe
* @comment
* Create on 2023/3/18 18:11
* @version 1.0
**/

#ifndef CATLOG_SRC_CATLOG_CONF_H_
#define CATLOG_SRC_CATLOG_CONF_H_

/**
 * 1: use mutex and lock on multithread program and RTOS
 * 0: disable
 */
#define CATLOG_MUTEX_LOCK_ENABLE 1

/**
 * 5 levels are supported, the log whose level is lower than CATLOG_PUSHOUT_LEVEL will not output.
 * If is defined to CATLOG_LOWEST, All logs will output
 * Suggest set to CATLOG_DISABLE when release.
 * CATLOG_INFO     (0)
 * CATLOG_DEBUG    (1)
 * CATLOG_WARNING  (2)
 * CATLOG_ERROR    (3)
 * CATLOG_FETAL    (4)
 */
#define CATLOG_PUSHOUT_LEVEL (CATLOG_LOWEST)


#define CATLOG_CACHED_SUPPORT  1

#define CATLOG_ANSI_SUPPORT 0

#define CATLOG_ADD_FUNCTION_NAME 1


/**
CATLOG_OUTPUT_TO_STDERR: output to stderr
CATLOG_OUTPUT_TO_FILE: output to file
CATLOG_OUTPUT_TO_DEVICE: output to device,such as /dev/ttyUSB0 on linux
 * */
#define CATLOG_OUTPUT_MODE  CATLOG_OUTPUT_TO_STDERR

/*
 * buffer size for cached log, valid when CATLOG_CACHED_SUPPORT = 1
 * Unit: byte
 * */
#define CATLOG_BUFFER_SIZE (1024*1024*2)


/**
 * maxmium of characters in one line, must be smaller than CATLOG_BUFFER_SIZE
 */
#define CATLOG_MAX_CHARS_ONE_LINE  255


#endif //CATLOG_SRC_CATLOG_CONF_H_
