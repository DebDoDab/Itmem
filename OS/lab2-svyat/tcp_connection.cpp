//
// Created by vadim on 23.10.20.
//
#include <iostream>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netdb.h>
#include <fcntl.h>
#include "tcp_connection.h"

using namespace std;


TcpConnection::TcpConnection() {
    this->sock = -1;
    memset(&this->address, 0, sizeof(this->address));
}


TcpConnection::TcpConnection(int sock, const sockaddr_in* address) {
    this->sock = sock;
    this->address = *address;
}


bool TcpConnection::isOpen() {
    return sock >= 0;
}


int TcpConnection::recv(uint8_t* buffer, size_t bufferLen) {
    int status;

    //check
    if (!isOpen()) {
        cout << "Closed connection!" << endl;
        return -1;
    }

    //Receive a reply from the server
    status = ::recv(this->sock, buffer, bufferLen, 0);

    //noting received
    if ((status == -1) && (errno == EWOULDBLOCK)) {
        return 0;
    }

    //receiving 0 on a non blocking socket means, the socket was closed remotely
    //receiving a negative value (other than EWOULDBLOCK indicates an error)
    if (status <= 0) {
        this->close();
        return -1;
    }

    //otherwise - N bytes of data has been received
    return status;
}


int TcpConnection::send(const uint8_t* data, size_t dataLen) {
    int flags = 0;
    int status;

    //check
    if (!isOpen()) {
        cout << "Closed connection!" << endl;
        return -1;
    }

    //Send some data
    status = ::send(this->sock, data, dataLen, flags);
    if (status < 0) {
        cout << "Failed to send data to server!" << endl;
        return -1;
    }
    return status;
}


void TcpConnection::close() {
    if (isOpen()) {
        ::shutdown(this->sock, SHUT_RD); //block until all queued bytes are sent!!!
        ::close(this->sock);
        this->sock = -1;
        memset(&this->address, 0, sizeof(this->address));
    }
}



TcpServer::TcpServer() {
    //nothing special to do here
}


int TcpServer::open(const uint16_t port) {
    sockaddr_in address = { 0 };
    int status;
    int sock;

    //create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock >= 0) {
        //bind socket to given port
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = INADDR_ANY;
        status = ::bind(sock, (sockaddr *)&address, sizeof(address));
        if (status >= 0) {
            //start to listen
            status = ::listen(sock, 3); //backlog of 3
            if (status >= 0) {
                //make socket non-blocking
                fcntl(sock, F_SETFL, O_NONBLOCK);

                this->sock = sock;
                this->address = address;
                return sock;
            }
        }

        //something went wrong ...
        ::close(sock);
    }
    return -1;
}


TcpConnection* TcpServer::serve() {
    struct sockaddr_in address = { 0 };
    socklen_t addressSize = sizeof(address);
    int connection;

    //check
    if (this->sock < 0) {
        cout << "Failed to serve on closed connection!" << endl;
        return nullptr;
    }

    //test for incomming connections
    connection = ::accept(this->sock, (struct sockaddr *)&address, &addressSize);
    if (connection >= 0) {
        //make socket non-blocking
        fcntl(connection, F_SETFL, O_NONBLOCK);
        //return connection instance
        return new TcpConnection(connection, &address);
    }
    return nullptr;
}