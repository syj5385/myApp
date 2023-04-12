#ifndef _CLI_HPP_
#define _CLI_HPP_

#include <pthread.h>
#include <iostream>
#include <string.h>
#include <queue>
#include <list>

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

#define MAX_HISTORY_SIZE    100
#define MAX_ARGV_NUM         10

using namespace std; 
static queue<char*> cmd_queue;
static list<char*> his_list;

class CLI{
private:
    char buffer[BUFSIZ];
    pthread_t cli_thread, pro_thread; 
    bool running; 
  
public:
    CLI();
    ~CLI();
    void run_cli();
    void signalHandler();
    void setRunning(bool running);
    bool getRunning();
};

extern CLI *mcli;

#endif /* _CLI_HPP_*/