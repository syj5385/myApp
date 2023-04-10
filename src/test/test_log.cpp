#include <stdio.h>

/* Include user library */
#include "common.h"

int main(int argc, char** argv){
    int ret = YJ_SUCCESS;
    log = new Log();
    log->setLogLevel(LOG_LEVEL_ERROR);

    printf("Current log level : %d\n", log->getLogLevel());
    log->fatal("Test fatal log",0);
    log->error("Test error log",0);
    log->warn("Test warn log", 0);
    log->info("Test info log", 0);
    log->debug("Test debug log", 0);
    log->trace("Test trace log", 0);
    
    return ret;
}