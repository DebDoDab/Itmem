//
// Created by vadim on 6.11.20.
//

#ifndef LAB2_SVYAT_TCPCONNECTION_H
#define LAB2_SVYAT_TCPCONNECTION_H


#include <netinet/in.h>

class TcpConnection {
    TcpConnection();
    TcpConnection(int socket_, const sockaddr_in& address_);
    bool isOpen();
    //returns number of received data bytes; 0 when nothing was received; -1 in case of connection errors
    int recv(uint8_t * buffer, size_t bufferLen);

    //returns number of sent data bytes; -1 in case of connection errors
    int send(const uint8_t * data, size_t dataLen, bool more=false);

    int close();

    int socket;
    sockaddr_in address;
};


#endif //LAB2_SVYAT_TCPCONNECTION_H
