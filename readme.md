# CatLog: a light and basic log system

### Features
1. Cached output;
2. Basic log functions are provided: log level, ANSI, multi-thread,log every , log first
and log if ;
3. Linux/Windows/Mac/RTOS and STM32 are supported;
4. You can define what to do when buffer is overflowed;

### Usage
#### 1. Basic log APIs
```C++
LOG_INFO("this is INFO message: %d", 1);
LOG_DEBUG("this is DEBUG message: %f %.2f", 1.0,2.12);
LOG_WARNING("this is WARNING message: %d", 2);
LOG_ERROR("this is ERROR message: 0x%x", 0xff);
LOG_FETAL("this is FETAL message: %d %d", 2, 4);
```
This will generate:
![img.png](res/img.png)

#### 2. Extend API: LOG_IF LOG_EVERY LOG_FIRST
The following API will output only when ths condition is true
1. `LOG_INFO_IF(condition,fmt,...)` 
2. `LOG_DEBUG_IF(condition,fmt,...)` 
3. `LOG_WARNING_IF(condition,fmt,...)`
4. `LOG_ERROR_IF(condition,fmt,...)`
5. `LOG_FETAL_IF(condition,fmt,...)`

The follow API will output every N times when function is called
1. `LOG_INFO_EVERY(N,fmt,...)`
2. `LOG_DEBUG_EVERY(N,fmt,...)`
3. `LOG_WARNING_EVERY(N,fmt,...)`
4. `LOG_ERROR_EVERY(N,fmt,...)`
5. `LOG_FETAL_EVERY(N,fmt,...)`    

The following API will output only the first N times

1. `LOG_INFO_FIRST(N,fmt,...)`
2. `LOG_DEBUG_FIRST(N,fmt,...)`
3. `LOG_WARNING_FIRST(N,fmt,...)`
4. `LOG_ERROR_FIRST(N,fmt,...)`
5. `LOG_FETAL_FIRST(N,fmt,...)`

### Custom configure

1. `CATLOG_PUSHOUT_LEVEL`    
This macro configures output level. The logs whose level is lower will not push out
2. `CATLOG_CACHED_SUPPORT`   
This macro configures whether to use buffer to cache logs
3. `CATLOG_ANSI_SUPPORT`   
This macro configures whether to support ANSI, which will generate colored logs on terminal
4. `CATLOG_ADD_FUNCTION_NAME`     
This macro configures whether to add function names to log messages
   1. `CATLOG_OUTPUT_MODE`
   This macro configures output mode and can be configured to the following:
   CATLOG_OUTPUT_TO_STDERR: output to stderr    
   CATLOG_OUTPUT_TO_FILE : output to file(windows/linux/FATFS)  
   CATLOG_OUTPUT_TO_DEVICE: output to specific device such as `dev/ttyUSB` or `UART1` 
   The interface is defined in `catlog_port.c`. If the user wants to push log to hardware, implement the three function:
   `catlog_open_device`,`catlog_close_device` and `catlog_write_to_device`

5. `CATLOG_BUFFER_SIZE`
This macro configures the size of the buffer in byte 

#### Bugs
1. `\0` will show at the beginning of some lines unexpectedly
