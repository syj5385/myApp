#include "cli.hpp"
#include "logger.hpp"
#include "network.hpp"
#include "common.h"

#include <unordered_map>

using namespace std; 
CLI *mcli;
unordered_map<int, Network*> server_list;

int execute_exit(int argc, char **argv){
    printf("Exiting the process. Bye~\n");
    mcli->setRunning(false);

    while(his_list.size() != 0)
        his_list.pop_front();
        

    exit(0);    
    /* Stop all of server */

    return YJ_SUCCESS;
}

int execute_tcpserver(int argc, char **argv){    
    int i=0; 
    
    if (argc == 3){
        int port = atoi(argv[2]);
        if (strcmp(argv[1], "open") == 0){
            Network *n = new Network(TCP);
            if (server_list.find(port) == server_list.end()){
                server_list.insert({port, n});
                if (n->Bind(port) == YJ_FAILED){
                    mlog->error("Failed to open tcpserver on %d port\n", port);
                    return YJ_FAILED;
                }
            }
            else{
                mlog->error("Port %d is already binded\n", port);
                return YJ_FAILED;
            }
        }
        else if (strcmp(argv[1], "close") == 0){
            server_list[port]->setRunning(false);
            server_list[port]->Close();
            free(server_list[port]);
            server_list.erase(port);
            return YJ_SUCCESS;
        }
    }
    else{
        printf("Invalid command tcp server\n");
    }
    
    return YJ_SUCCESS;
}

int execute_log(int argc, char **argv){    
    int i=0; 
    int level;
    list<char*>::iterator iter;
    if (argc == 2){
        if (strcmp(argv[1], "help") == 0)
            goto log_usage; 
        level = atoi(argv[1]);
        if(level == 7)
            level = 100;
        else if (level >= 0 && level <= 6)
            level *= 10;
        else {
            printf("Invalid log level\n");
            goto log_usage;
        }
        mlog->setLogLevel(level);
    }
    else{
        goto log_usage;
    }
    
    return YJ_SUCCESS;

log_usage: 
    printf("***********************************************************\n");
    printf("  log Usage:\n");
    printf("    []: essential\t<>: optional\n");
    printf("-----------------------------------------------------------\n");
    printf("  log [level]\t: the recent # of command is printed\n\n");
    printf("  [level]\n");
    printf("    0: LOG_LEVEL_OFF\n");
    printf("    1: LOG_LEVEL_FATAL\n");
    printf("    2: LOG_LEVEL_ERROR\n");
    printf("    3: LOG_LEVEL_WARN\n");
    printf("    4: LOG_LEVEL_INFO\n");
    printf("    5: LOG_LEVEL_DEBUG\n");
    printf("    6: LOG_LEVEL_TRACE\n");
    printf("    7: LOG_LEVEL_ALL\n");
    printf("***********************************************************\n\n");


    return YJ_SUCCESS;
}

int execute_his(int argc, char **argv){    
    int i=0, j=0;
    int count; int end;
    list<char*>::iterator iter;
    if (argc == 2){
        if (strcmp(argv[1], "help") == 0)
            goto his_usage; 
        his_list.pop_back();
        iter = his_list.end();
        end  = his_list.size();
        count = atoi(argv[1]);
        for(i=0; i<count; i++){
            if (iter == his_list.begin()){
                break;
            }
            iter--;
        }
    }
    else if (argc == 1){
        his_list.pop_back();
        end = his_list.size();
        iter = his_list.begin();
        i = end;
    }
    else{
        goto his_usage;
    }
    
     
    printf("***********************************************************\n");
    printf("  Recent %d input command%c\n", i, (i>1?'s':' '));
    printf("***********************************************************\n");
    

    for(;iter != his_list.end(); iter++)
        printf("%3d %s\n", end-(i--)+1, *iter);
    printf("\n");
    
    return YJ_SUCCESS;

his_usage: 
    printf("***********************************************************\n");
    printf("  his Usage:\n");
    printf("    []: essential\t<>: optional\n");
    printf("-----------------------------------------------------------\n");
    printf("  his <number>\t: the recent # of command is printed\n");
    printf("  his help\t: Display the help for his command\n");
    printf("***********************************************************\n\n");
    return YJ_SUCCESS;
}

int process_command(char* cmd){
    int ret = YJ_SUCCESS;
    int argc=0; 
    char *p;
    char* argv[MAX_ARGV_NUM];
    mlog->info("[CMD] %s", cmd);
    p = strtok(cmd, " ");
    while(p){   
        argv[argc] = p; 
        argc++;     
        p = strtok(NULL, " ");
    }

    if (argc > MAX_ARGV_NUM)
        return YJ_FAILED;

    
    if (strcmp(argv[0], "exit") == 0)
            return execute_exit(argc, argv);
    
    if (strcmp(argv[0], "his") == 0)
            return execute_his(argc, argv);

    if (strcmp(argv[0], "log") == 0)
            return execute_log(argc, argv);

    if (strcmp(argv[0], "tcpserver") == 0)
        return execute_tcpserver(argc, argv);


    return ret; 
}

void *process_thread(void *args){
    void** arg = (void**)args; 
    bool *running = (bool*)args;
    mlog->info("CLI process thread started", 0);
    while(*running){
        if (!cmd_queue.empty()){
            char* now = cmd_queue.front();
            cmd_queue.pop();
            
            process_command(now);
            free(now);
        }   
    }
    return NULL;
}

void *input_thread(void *args){
    void** arg = (void**)args; 
    bool *running = (bool*)arg[0];
    char *buffer = (char*)arg[1];
    
    mlog->info("CLI input thread started", 0);
    while(*running){
        usleep(1000);
        printf("cmd(myApp) >> ");
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
            char* cmd_his = (char*)malloc(len+1);
            if (unlikely(cmd == NULL)){
                mlog->warn("\"%s\" command is ignored", p);
            }
            else{
                memcpy(cmd, p, len+1);
                memcpy(cmd_his, p, len+1);
                cmd_queue.push(cmd);
                if(his_list.size() == MAX_HISTORY_SIZE){
                    char* front = his_list.front();
                    his_list.pop_front();
                    free(front);
                }
                his_list.push_back(cmd_his);
            }
            p = strtok(NULL,";");
        }
    }
    return NULL;
}
CLI::CLI(){
    mlog->info("Initialize CLI instance", 0);
    running = true; 
}

CLI::~CLI(){
    running = false;
}

void CLI::setRunning(bool running){
    this -> running = running; 
}

bool CLI::getRunning(){
    return running;
}

void CLI::run_cli(){
    void* arg[2];
    arg[0] = (void*)&running;
    arg[1] = (void*)buffer;
    pthread_create(&cli_thread, NULL, input_thread, (void*)arg);
    pthread_create(&pro_thread, NULL, process_thread, (void*)&running);

    pthread_join(cli_thread, NULL);
    pthread_join(pro_thread, NULL);
}