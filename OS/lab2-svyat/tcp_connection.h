//
// Created by vadim on 23.10.20.
//

#ifndef LAB2_SVYAT_TCP_CONNECTION_H
#define LAB2_SVYAT_TCP_CONNECTION_H


#include <stdint.h>
#include <netinet/in.h>


class TcpConnection {
public:
    TcpConnection();
    bTcpConnection(int sock, const sockaddr_in* address);

    bool isOpen();

    //returns number of received data bytes; 0 when nothing was received; -1 in case of connection errors
    int recv(uint8_t* buffer, size_t bufferLen);

    //returns number of sent data bytes; -1 in case of connection errors
    int send(const uint8_t* data, size_t dataLen, bool more=false);

    void close();

protected:
    int sock; //file descriptor of socket
    sockaddr_in address; //remote connection address
};


class TcpServer : public TcpConnection {
public:
    TcpServer();

    //open a non blocking tcp server connection, listening to the given port
    //returns positive number on success; -1 in case of errors
    int open(const uint16_t port);

    //call this function cyclically to accept incoming connections
    //returns pointer to accepted connection; NULL otherwise
    TcpConnection* serve();
};

#endif //LAB2_SVYAT_TCP_CONNECTION_H
