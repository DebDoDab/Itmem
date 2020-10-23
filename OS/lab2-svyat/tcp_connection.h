//
// Created by vadim on 23.10.20.
//

#ifndef LAB2_SVYAT_TCP_CONNECTION_H
#define LAB2_SVYAT_TCP_CONNECTION_H


/* -- Includes ------------------------------------------------------------ */
#include <stdint.h>
#include <netinet/in.h>



/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */
class NbTcpConnection
{
public:
    NbTcpConnection();
    NbTcpConnection(int sock, const struct sockaddr_in * address);

    bool isOpen();

    //returns number of received data bytes; 0 when nothing was received; -1 in case of connection errors
    int recv(uint8_t * buffer, size_t bufferLen);

    //returns number of sent data bytes; -1 in case of connection errors
    int send(const uint8_t * data, size_t dataLen, bool more=false);

    void close();

protected:
    int sock; //file descriptor of socket
    struct sockaddr_in address; //remote connection address
};



class NbTcpServer : public NbTcpConnection
{
public:
    NbTcpServer();

    //open a non blocking tcp server connection, listening to the given port
    //returns positive number on success; -1 in case of errors
    int open(const uint16_t port);

    //call this function cyclically to accept incomming connections
    //returns pointer to accepted connection; NULL otherwise
    NbTcpConnection * serve();

private:
};



class NbTcpClient : public NbTcpConnection
{
    NbTcpClient();

    //open a non blocking tcp client connection
    //returns positive number when connection is establised; -1 in case of errors
    int open(const char * ip, const uint16_t port);

private:
};







/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */

/* -- Implementation ------------------------------------------------------ */




#endif //LAB2_SVYAT_TCP_CONNECTION_H
