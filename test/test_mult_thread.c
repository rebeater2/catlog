/**
* @file test_mult_thread.c in catlog
* @author linfe
* @comment
* Create on 2023/3/15 21:06
* @version 1.0
**/


#include "../src/catlog.h"
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *i) {
    int num = *(int *) i;
    for (int j = 0; j < 10000; ++j) {
        LOG_INFO("this is thread %2d, %2dth info", num, j);
        if (j % 10 == 1) {
            LOG_DEBUG("this is thread %2d, %2dth debug", num, j);
        }
        if (j % 10 == 2) {
            LOG_WARNING("this is thread %2d, %2dth warning", num, j);
        }
        if (j % 10 == 3) {
            LOG_ERROR("this is thread %2d, %2dth error", num, j);
        }
        if (j % 10 == 4) {
            LOG_INFO_FIRST(2, "this is thread %2d, %2dth (first 2)", num, j);
        }
        if (j % 10 == 5) {
            LOG_WARNING_IF(j > 5, "this is thread %2d, %2dth (if j > 5)", num, j);
        }
        if (j % 10 == 6) {
            LOG_DEBUG_EVERY(2, "this is thread %2d, %2dth (every 2)", num, j);
        }

    }
    return NULL;
}

int main() {
    catlog_init(NULL);

    const int th_n = 20;
    int th_num[th_n];
    pthread_t th[th_n];
    int arg[th_n];
    for (int i = 0; i < th_n; ++i) {
        arg[i] = i;
        th_num[i] = pthread_create(&th[i], NULL, thread_func, &arg[i]);
    }

    for (int i = 0; i < th_n; ++i) {
        pthread_join(th[i], NULL);
    }
    catlog_deinit(NULL);
}