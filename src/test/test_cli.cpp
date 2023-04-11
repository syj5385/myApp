#include <cstdio>

#include "cli.hpp"
#include "logger.hpp"

Log *mlog;
int main(int argc, char** argv){
    mlog = new Log("test_cli");

    mlog->info("test cli start", 0);
    CLI *cli = new CLI();
    return 0;
}
