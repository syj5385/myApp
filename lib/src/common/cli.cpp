#include "cli.hpp"
#include "logger.hpp"

void *process_thread(void *args){
    void** arg = (void**)args; 
    bool running = *(bool*)args;
    mlog->info("CLI process thread started", 0);
    while(running){
        if (!cmd_queue.empty()){
            char* now = cmd_queue.front();
            cmd_queue.pop();
            
            mlog->info("\"%s\" is executed", now);
            free(now);
        }   
    }
    return NULL;
}

void *input_thread(void *args){
    void** arg = (void**)args; 
    bool running = *(bool*)arg[0];
    char *buffer = (char*)arg[1];
    
    mlog->info("CLI input thread started", 0);
    while(running){
        cin.getline(buffer,BUFSIZ);
        char* p; 
        p = strtok(buffer, ";");
        while(p){
            int len = (int)strlen(p);
            if (p[0] == ' ') {
                if (len == 1){
                    p = strtok(NULL, ";");
                    continue;
                }
                else {
                    p++;
                    len--;
                }
            }
            if (p[len-1] == ' '){
                p[len-1] = '\0';
                len--;
            }
            
            char* cmd = (char*)malloc(len+1);
            if (unlikely(cmd == NULL)){
                mlog->warn("\"%s\" command is ignored", p);
            }
            else{
                memcpy(cmd, p, len+1);
                cmd_queue.push(cmd);
                mlog->info("queue size: %d", cmd_queue.size());
            }
            p = strtok(NULL,";");
        }
    }
    return NULL;
}
CLI::CLI(){
    mlog->info("Initialize CLI instance", 0);
    running = true; 
    run_cli();
}

void CLI::run_cli(){
    void* arg[2];
    arg[0] = (void*)&running;
    arg[1] = (void*)buffer;
    pthread_create(&cli_thread, NULL, input_thread, (void*)arg);
    pthread_create(&pro_thread, NULL, process_thread, (void*)&running);
    pthread_join(cli_thread, NULL);
}