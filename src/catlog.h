/**
* @file catlog.h in catlog
* @author linfe
* @comment
* Create on 2023/3/13 23:10
* @version 1.0
**/

#ifndef CATLOG__CATLOG_H_
#define CATLOG__CATLOG_H_
#include "catlog_conf.h"
#include <stdint.h>

#ifndef CATLOG_MUTEX_LOCK_ENABLE
#define CATLOG_MUTEX_LOCK_ENABLE 1
#endif
#ifndef CATLOG_PUSHOUT_LEVEL
#define CATLOG_PUSHOUT_LEVEL (CATLOG_LOWEST)
#endif

#define CATLOG_LOWEST   (-1)
#define CATLOG_INFO     (0)
#define CATLOG_DEBUG    (1)
#define CATLOG_WARNING  (2)
#define CATLOG_ERROR    (3)
#define CATLOG_FETAL    (4)
#define CATLOG_DISABLE  (5)
typedef uint8_t catlog_level_t;



/*output log*/
#define CATLOG_OUTPUT_TO_STDERR  0
#define CATLOG_OUTPUT_TO_FILE  1
#define CATLOG_OUTPUT_TO_DEVICE  2



void catlog_init();
void log_impl(catlog_level_t level,const char *func_name, const char *fmt, ...);

#if CATLOG_PUSHOUT_LEVEL > (CATLOG_INFO)
#define LOG_INFO(...)
#define LOG_INFO_EVERY(N,...)
#define LOG_INFO_IF(condition, ...)
#define LOG_INFO_FIRST(N, ...)
#else
#define LOG_INFO(...) log_impl(CATLOG_INFO,__FUNCTION__,__VA_ARGS__)
#define LOG_INFO_EVERY(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt >= N)                     \
    {                                     \
    LOG_INFO(__VA_ARGS__);            \
     cnt = 0;                                     \
    }                                 \
    cnt ++;\
    \
}while(0)

#define LOG_INFO_FIRST(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt < N)                     \
    {                                     \
    LOG_INFO(__VA_ARGS__);            \
    }                                 \
    cnt ++;\
    \
}while(0)

#define LOG_INFO_IF(condition, ...)    \
do{                                           \
    if (condition){                   \
    LOG_INFO(__VA_ARGS__) ;        \
    }                 \
}while(0)
#endif

#if CATLOG_PUSHOUT_LEVEL > (CATLOG_DEBUG)
#define LOG_DEBUG(...)
#define LOG_DEBUG_EVERY(N,...)
#define LOG_DEBUG_IF(condition, ...)
#define LOG_DEBUG_FIRST(N, ...)
#else
#define LOG_DEBUG(...) log_impl(CATLOG_DEBUG,__FUNCTION__,__VA_ARGS__)
#define LOG_DEBUG_FIRST(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt < N)                     \
    {                                     \
    LOG_DEBUG(__VA_ARGS__);            \
    }                                 \
    cnt ++;\
    \
}while(0)

#define LOG_DEBUG_EVERY(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt >= N)                     \
    {                                     \
    LOG_DEBUG(__VA_ARGS__);            \
     cnt = 0;                                     \
    }                                 \
    cnt ++;\
    \
}while(0)
#define LOG_DEBUG_IF(condition, ...)    \
do{                                           \
    if (condition){                   \
    LOG_DEBUG(__VA_ARGS__) ;        \
    }                 \
}while(0)

#endif


#if CATLOG_PUSHOUT_LEVEL > (CATLOG_WARNING)
#define LOG_WARNING(...)
#define LOG_WARNING_EVERY(N,...)
#define LOG_WARNING_IF(condition, ...)
#define LOG_WARNING_FIRST(N, ...)
#else
#define LOG_WARNING(...) log_impl(CATLOG_WARNING,__FUNCTION__,__VA_ARGS__)
#define LOG_WARNING_FIRST(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt < N)                     \
    {                                     \
    LOG_WARNING(__VA_ARGS__);            \
    }                                 \
    cnt ++;\
    \
}while(0)

#define LOG_WARNING_EVERY(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt >= N)                     \
    {                                     \
    LOG_WARNING(__VA_ARGS__);            \
     cnt = 0;                                     \
    }                                 \
    cnt ++;\
    \
}while(0)
#define LOG_WARNING_IF(condition, ...)    \
do{                                           \
    if (condition){                   \
    LOG_WARNING(__VA_ARGS__) ;        \
    }                 \
}while(0)

#endif


#if CATLOG_PUSHOUT_LEVEL > (CATLOG_ERROR)
#define LOG_ERROR(...)
#define LOG_ERROR_EVERY(N,...)
#define LOG_ERROR_IF(condition, ...)
#define LOG_ERROR_FIRST(N, ...)
#else
#define LOG_ERROR(...) log_impl(CATLOG_ERROR,__FUNCTION__,__VA_ARGS__)
#define LOG_ERROR_FIRST(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt < N)                     \
    {                                     \
    LOG_ERROR(__VA_ARGS__);            \
    }                                 \
    cnt ++;\
    \
}while(0)

#define LOG_ERROR_EVERY(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt >= N)                     \
    {                                     \
    LOG_ERROR(__VA_ARGS__);            \
     cnt = 0;                                     \
    }                                 \
    cnt ++;\
    \
}while(0)
#define LOG_ERROR_IF(condition, ...)    \
do{                                           \
    if (condition){                   \
    LOG_ERROR(__VA_ARGS__) ;        \
    }                 \
}while(0)
#endif


#if CATLOG_PUSHOUT_LEVEL > (CATLOG_FETAL)
#define LOG_FETAL(...)
#define LOG_FETAL_EVERY(N,...)
#define LOG_FETAL_IF(condition, ...)
#else
#define LOG_FETAL(...) log_impl(CATLOG_FETAL,__FUNCTION__,__VA_ARGS__)
#define LOG_FETAL_FIRST(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt < N)                     \
    {                                     \
    LOG_FETAL(__VA_ARGS__);            \
    }                                 \
    cnt ++;\
    \
}while(0)

#define LOG_FETAL_EVERY(N, ...)         \
do{                                           \
    static uint32_t cnt = 0;                \
    if (cnt >= N)                     \
    {                                     \
    LOG_FETAL(__VA_ARGS__);            \
     cnt = 0;                                     \
    }                                 \
    cnt ++;\
    \
}while(0)
#define LOG_FETAL_IF(condition, ...)    \
do{                                           \
    if (condition){                   \
    LOG_FETAL(__VA_ARGS__) ;        \
    }                 \
}while(0)
#endif



void catlog_deinit();

extern uint32_t catlog_push_out_cnts;

#endif //CATLOG__CATLOG_H_
