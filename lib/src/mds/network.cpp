#include "network.hpp"
#include "logger.hpp"
#include "common.h"

// Log *mlog; 

Network::Network (int protocol){
    if (protocol >= PROTOCOL_END){
        mlog->error("Invalid protocol range",0);
        return;
    }
    this->protocol = protocol;
    running = true;
    mlog->info("Initialize %s network", protocol == TCP ? "TCP" : "UDP", 0);
}

Network::~Network(){}
    
int Network::Bind(int port){
    int success = YJ_SUCCESS;
    if (protocol == TCP){
        sock = socket(PF_INET, SOCK_STREAM, 0);
        if (sock < 0){ 
            mlog->error("Failed to create server TCP socker", 0);
            return YJ_FAILED;
        }
    }
    else{
        sock = socket(PF_INET,SOCK_DGRAM, 0);
        if (sock < 0){ 
            mlog->error("Failed to create server UDP socker", 0);
            return YJ_FAILED;
        }
    }
    mlog->info("Create server socket", 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    socklen = sizeof(addr);
    success = bind(sock, (struct sockaddr*)&addr, socklen);
    if (success == -1){
        mlog->error("Failed to bind server socket",0);
        return YJ_FAILED;
    }
    mlog -> info("Success to bind server socket on port %d", port);
    if(protocol == TCP){
        success = listen(sock, 5);
        if(success == -1){
            mlog->error("Failed to listen server socket", 0);
            return YJ_FAILED;
        }
    }
    return success;
}

void Network::Close(){
    close(sock);
}

    
/* For TCP */
int Network::Listen(){

    if (protocol != TCP){
        mlog->error("Only TCP is valid in Accept function",0);
        return YJ_FAILED;
    }
    CLIENT *cli = (CLIENT*)malloc(sizeof(CLIENT));
    if (cli == NULL){
        mlog->error("Failed to create client structure",0);
        return YJ_FAILED;
    }
  
    // mlog->info("Wait for remote client",0);
    u_long nonBlockingMode = 1; 
    int flag = fcntl(sock, F_GETFL,0);
    fcntl(sock, F_SETFL, flag | O_NONBLOCK);
    cli->sock = accept(sock, (struct sockaddr*)&cli->c_addr, &cli->client_len);
    if (cli->sock != -1){
        wait_queue.push(cli);
        mlog->info("New remote client is accepted -> remain: %d", wait_queue.size());
        return YJ_SUCCESS;
    }
    else
        free(cli);

    return YJ_FAILED;
}

int Network::Connect(const char* remote, int port){
    int success = YJ_SUCCESS;
    if (protocol != TCP){
        mlog->error("Only TCP is valid in Connect function",0);
        return YJ_FAILED;
    }

    sock = socket(PF_INET,SOCK_STREAM, 0);
    if (sock == -1){
        mlog->error("Failed to create client socket", 0);
        return YJ_FAILED;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(remote);
    addr.sin_port = htons(port);
    mlog->info("Try to connect remote server: %s:%d", remote ,port);
    socklen = sizeof(addr);
    if (connect(sock, (struct sockaddr*)&addr,socklen) == -1){
        mlog->error("Failed to connect remote server",0);
        return YJ_FAILED;
    }
    mlog->info("Connect to remote server %s:%d", remote, port);
    return success;
}
int Network::Recv(){
    int success = YJ_SUCCESS;
    
    return success;
}
int Network::Send(){
    int success = YJ_SUCCESS;

    return success;
}

    /* For UDP */
int Network::RecvFrom(){
    int success = YJ_SUCCESS;

    return success;
}
int Network::Sendto(){
    int success = YJ_SUCCESS;

    return success;
}