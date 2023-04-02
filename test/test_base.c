
#include "../src/catlog.h"

#include <time.h>
#include <stdio.h>

/*
 * #include <stdio.h>
void catlog_write_to_stderr(uint8_t * buffer,uint32_t size) {
    fprintf(stderr,"%s", buffer);
}*/

int main() {

    catlog_init();
    LOG_INFO("<---------------------  time used  ---------------------------->");
#if 1
    clock_t start,stop;
    start = clock();
    for(int i = 0; i < 10000; ++i){
        LOG_INFO("this is %d,%s",i,"hello world");
    }
    stop = clock();
    LOG_INFO("MAX push out cnts %d",catlog_push_out_cnts);
    LOG_INFO("time used %d ms",(int)(1e3f * (stop-start)/CLOCKS_PER_SEC));
#endif
    LOG_INFO("<---------------------  base function test  ---------------------------->");
    LOG_INFO("this is INFO message: %d", 1);
    LOG_DEBUG("this is DEBUG message: %f %.2f", 1.0,2.12);
    LOG_WARNING("this is WARNING message: %d", 2);
    LOG_ERROR("this is ERROR message: 0x%x", 0xff);
    LOG_FETAL("this is FETAL message: %d %d", 2, 4);

    for (int i = 0; i <= 2000; i++) {
        LOG_INFO_EVERY(5, "this will log info every 5 times(current i = %d)", i);
        LOG_DEBUG_FIRST(3, "this will log debug only the first 3 times(current i = %d)", i);
    }
    int k = 3;
    LOG_INFO_IF(k++ < 4, "this tells: k>5? k=%d", k);


    catlog_deinit();
    printf("output counts:%d\n",catlog_push_out_cnts);

    return 0;
}
