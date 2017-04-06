//
// Created by unl on 02.04.17.
//
#include "BasicConnection.h"
#include <string.h>

operator string(vector<byte>){

}


vector<byte> operator+(const vector<byte>& vec, const string& str){
    vector<byte> res(vec.size() + str.length());

    if (vec.size() > 0)
        bcopy( &vec[0], &res[0] , res.size());

    if (str.size() > 0)
        bcopy( &str[0], &res[ vec.size() ] , str.length());

    return res;
}

vector<byte>& operator+=(vector<byte>& vec, const string str){
    vec.resize( vec.size() + str.length() );

    if (str.length() > 0)
        bcopy( &str[0], &vec[ vec.size() - str.length() ] , str.length() );

    return vec;
}

class Client : public BasicConnection {
public:

    Client(uint32_t inPort , string inHostname){
        port = inPort;
        hostname = inHostname;
        //very important to run instantly
        run();
    }

    void run() override {
        hostent *server;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            throw errors::ERonOpeningSocket;
        server = gethostbyname(hostname.c_str());
        if (server == NULL)
            throw Client::errors::ERonFindingHost;
        bzero((char *) &address, sizeof(address));
        address.sin_family = AF_INET;
        bcopy(server->h_addr, (char *) & address.sin_addr.s_addr, server->h_length);
        address.sin_port = htons(port);
        if (connect(sockfd,(struct sockaddr *) &address,sizeof(address)) < 0)
            throw Client::errors::ERonConnecting;

    }

};

