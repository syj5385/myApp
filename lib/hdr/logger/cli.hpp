#ifndef _CLI_HPP_
#define _CLI_HPP_

#include <pthread.h>
#include <iostream>
#include <string.h>
#include <queue>

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

using namespace std; 
static queue<char*> cmd_queue;

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

};
#endif /* _CLI_HPP_*/