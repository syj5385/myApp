#include <cstdio>

#include "cli.hpp"
#include "common.h"
#include "logger.hpp"

Log *mlog;
int main(int argc, char** argv){
    mlog = new Log("test_cli");

    mlog->info("test cli start", 0);
    mcli = new CLI();
    mcli->run_cli();
    
    return 0;
}
