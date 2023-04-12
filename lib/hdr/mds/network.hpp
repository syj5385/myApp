#ifndef _NETWORK_H_
#define _NETWORK_H_

#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include <string>
#include <queue>
#include <unistd.h>
#include <fcntl.h>
#include <unordered_map>

#include "logger.hpp"

#define TCP             0
#define UDP             1
#define PROTOCOL_END    2

using namespace std; 

typedef struct {
    int sock; 
    struct sockaddr_in c_addr; 
    socklen_t client_len;
} CLIENT;

class Network{
private:
    int protocol;
    int sock; 
    struct sockaddr_in addr;
    socklen_t socklen; 
    queue<CLIENT*> wait_queue;
    bool running; 

public:
    Network (int protocol);
    ~Network();

    int Bind(int port);
    void Close();
    
    /* For TCP */
    int Listen();
    int Connect(const char* remote, int port);
    int Recv();
    int Send();

    /* For UDP */
    int RecvFrom();
    int Sendto();

    inline void setRunning(bool running){
        this -> running = running;
    }

    bool getRunning(){
        return running;
    }

    inline string getProtocol(){
        return protocol == TCP ? "TCP" : "UDP";
    }
};

extern unordered_map<int, Network*> server_list;

#endif /* _NETWORK_H_ */