#include <pthread.h>

#include "logger.hpp"
#include "network.hpp"

Log *mlog; 
Network *u_server_net, *u_client_net, *t_server_net, *t_client_net; 

void *udp_server(void *args){
    u_server_net = new Network(UDP);
    u_server_net->Bind(atoi(getenv("UDP_PORT")));

    return NULL;
}

void *udp_client(void* args){

    return NULL;
}

void *tcp_server(void* args){
    int ret; 
    t_server_net = new Network(TCP);
    ret = t_server_net->Bind(atoi(getenv("TCP_PORT")));
    if (ret == YJ_FAILED)
        return NULL;
    
    while(t_server_net->getRunning()){
        t_server_net->Listen();
        usleep(1000);
    }

    t_server_net->Close();
    
    return NULL;
}

void *tcp_client(void* args){
    t_client_net = new Network(TCP);
    t_client_net->Connect("127.0.0.1", atoi(getenv("TCP_PORT")));
    t_client_net->Close();
    return NULL;
}

int main(int argc, char** argv){
    mlog = new Log("test_network");
    pthread_t u_server, u_client, t_server, t_client; 
    int u_server_id, u_client_id, t_server_id, t_client_id; 
    int u_server_status, u_client_status, t_server_status, t_client_status; 

    // u_server_id = pthread_create(&u_server, NULL, udp_server, NULL);
    t_server_id = pthread_create(&t_server, NULL, tcp_server, NULL);
    usleep(1000000);
    t_client_id = pthread_create(&t_client, NULL, tcp_client, NULL);
    usleep(1000000);
    t_server_net->setRunning(false);

    // pthread_join(u_server, (void**)&u_server_status);
    pthread_join(t_client, (void**)&t_client_status);
    pthread_join(t_server, (void**)&t_server_status);

    return 0;
}