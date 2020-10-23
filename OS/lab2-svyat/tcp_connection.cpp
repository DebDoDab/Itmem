//
// Created by vadim on 23.10.20.
//

//-----------------------------------------------------------------------------
/*!
   \file
   \brief Non blocking TCP connection class
*/
//-----------------------------------------------------------------------------

/* -- Includes ------------------------------------------------------------ */
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


/* -- Defines ------------------------------------------------------------- */

using namespace std;


/* -- Types --------------------------------------------------------------- */

/* -- (Module) Global Variables ------------------------------------------- */

/* -- Module Global Function Prototypes ----------------------------------- */


/* -- Implementation ------------------------------------------------------ */

NbTcpConnection::NbTcpConnection()
{
    this->sock = -1;
    memset(&this->address, 0, sizeof(this->address));
}


NbTcpConnection::NbTcpConnection(int sock, const struct sockaddr_in * address)
{
    this->sock = sock;
    this->address = *address;
}


bool NbTcpConnection::isOpen()
{
    return (this->sock >= 0);
}


int NbTcpConnection::recv(uint8_t * buffer, size_t bufferLen)
{
    int status;

    //check
    if (this->sock < 0)
    {
        cout << "Failed to receive from closed connection!" << endl;
        return -1;
    }

    //Receive a reply from the server
    status = ::recv(this->sock, buffer, bufferLen, 0);
    if ((status == -1) && (errno == EWOULDBLOCK)) //noting received
    {
        return 0;
    }

    //receiving 0 on a non blocking socket means, the socket was closed remotely
    //receiveing a negative value (other than EWOULDBLOCK indicates an error)
    if (status <= 0)
    {
        this->close();
        return -1;
    }

    //otherwise - N bytes of data has been received
    return status;
}


int NbTcpConnection::send(const uint8_t * data, size_t dataLen, bool more)
{
//    int flags = (more ? MSG_MORE : 0);
    int flags = 0;
    int status;

    //check
    if (this->sock < 0)
    {
        cout << "Failed to send to closed connection!" << endl;
        return -1;
    }

    //Send some data
    status = ::send(this->sock, data, dataLen, flags);
    if (status < 0)
    {
        cout << "Failed to send data to server!" << endl;
        return -1;
    }
    return status;
}


void NbTcpConnection::close()
{
    if (this->sock >= 0)
    {
        ::shutdown(this->sock, SHUT_RD); //block until all queued bytes are sent!!!
        ::close(this->sock);
        this->sock = -1;
        memset(&this->address, 0, sizeof(this->address));
    }
}





//-----------------------------------------------------------------------------------




NbTcpServer::NbTcpServer()
{
    //nothing special todo here
}


int NbTcpServer::open(const uint16_t port)
{
    struct sockaddr_in address = { 0 };
    int status;
    int sock;

    //create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock >= 0)
    {
        //bind socket to given port
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = INADDR_ANY;
        status = ::bind(sock, (struct sockaddr *)&address, sizeof(address));
        if (status >= 0)
        {
            //start to listen
            status = ::listen(sock, 3); //backlog of 3
            if (status >= 0)
            {
                //make socket non-blocking
                fcntl(sock, F_SETFL, O_NONBLOCK);

                //
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



NbTcpConnection * NbTcpServer::serve()
{
    struct sockaddr_in address = { 0 };
    socklen_t addressSize = sizeof(address);
    int connection;

    //check
    if (this->sock < 0)
    {
        cout << "Failed to serve on closed connection!" << endl;
        return NULL;
    }

    //test for incomming connections
    connection = ::accept(this->sock, (struct sockaddr *)&address, &addressSize);
    if (connection >= 0)
    {
        //make socket non-blocking
        fcntl(connection, F_SETFL, O_NONBLOCK);
        //return connection instance
        return new NbTcpConnection(connection, &address);
    }
    return NULL;
}



//-----------------------------------------------------------------------------------




NbTcpClient::NbTcpClient()
{
    //nothing special todo here
}


int NbTcpClient::open(const char * ip, const uint16_t port)
{
    struct sockaddr_in address = { 0 };
    int status;
    int sock;

    //create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock >= 0)
    {
        //connect to remote host
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = inet_addr(ip);
        status = ::connect(sock , (struct sockaddr *)&address , sizeof(address));
        if (status >= 0)
        {
            //make socket non-blocking
            fcntl(sock, F_SETFL, O_NONBLOCK);

            //
            this->sock = sock;
            this->address = address;
            return sock;
        }

        //something went wrong ...
        ::close(sock);
    }
    return -1;
}