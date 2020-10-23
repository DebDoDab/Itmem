#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <list>
#include <vector>
#include "tcp_connection.h"
#include "dynamic_resource.h"
#include "hqsp.h"
#include "processes/logger_wrapper.h"
#include "processes/create_process.h"
#include "processes/system_info.h"

using namespace std;


typedef struct {
    NbTcpConnection * connection;
    DynamicResource * resource;
    uint32_t hash;
} Connection;


static int ctrlC;
static DynamicResource * code200;
static DynamicResource * code404;
static string htmlBasePath;

static int m_serve_requests(Connection& connection, list<DynamicResource *>& dynamicResources);
static int m_reply_dynamic_content(Connection& connection);
static int m_reply_static_content(Connection& connection, const string& uri);
static int m_reply(Connection& connection, const string&);
static string m_get_content_type_by_uri(const string& uri, const string& fallback);


void m_signal_handler(int a) {
    ctrlC = 1;
}


int main(int argc, const char * argv[]) {
    vector<string> logfiles = {"logs/main.log"};
    auto log = Log(logfiles);
    list<DynamicResource *> dynamicResources;
    list<Connection> connections;
    list<Connection>::iterator conIt;
    uint16_t port;
    int status;

    //process command line arguments
    //otherwise: use defaults
    if (argc == 3) {
        htmlBasePath = argv[1];
        port = (uint16_t) atoi(argv[2]);
    } else {
        cout << "Usage: lab2_svyat [HTML-base-path] [TCP-port-number]" << endl;
        htmlBasePath = "."; //"this" directory
        port = 8083; //default port
    }


    //create default resources
    code200 = new DynamicResource("/200", "200 OK");
    code200->setContent("OK");
    code404 = new DynamicResource("/404", "404 Not Found");
    code404->setContent("Not Found");

    //create dynamic resources, as specified in "dynres.txt"
    const string filePath = htmlBasePath + "/dynres.txt";
    ifstream file(filePath, ios::in);
    if (file.is_open()) {
        string uri;
        //read out file, line by line
        while (getline(file, uri)) {
            //only those lines, that starts with a '/'
            if (uri[0] == '/') {
                //add to list of dynamic resources
                dynamicResources.push_back(new DynamicResource(uri));
            }
        }
        file.close();
    }


    //create server
    NbTcpServer * tcpServer = new NbTcpServer();
    status = tcpServer->open(port);
    if (status < 0) {
        cout << "Failed to open server on port " << port << endl;
        return -1;
    }
    cout << "Running webserver on port: " << port << endl;
    cout << "HTML base path: " << htmlBasePath << endl;
    cout << "Use CTRL+C to quit!" << endl;


    //register signal handler, to quit program usin CTRL+C
    signal(SIGINT, &m_signal_handler);

    //enter super-loop
    while (!ctrlC) {
        Connection con;

        //push new tcp connections to "connection list"
        con.connection = tcpServer->serve();
        while (con.connection) {
            //add to this connection to the list of active connections
            con.resource = nullptr;
            con.hash = 0;
            connections.push_back(con);
            con.connection = tcpServer->serve();
        }


        //for each connection ...
        //receive HTTP requests
        conIt = connections.begin();
        while (conIt != connections.end()) {
            status = m_serve_requests(*conIt, dynamicResources);
            //close connection
            if (status != 0) {
                //close that connection
                conIt->connection->close();
                delete conIt->connection;
                //remove from list of active connections
                conIt = connections.erase(conIt);
                continue;
            }
            conIt++;
        }


        //for each connection ...
        //reply dynamic content
//        conIt = connections.begin();
//        while (conIt != connections.end()) {
//            status = m_reply_dynamic_content(*conIt);
//            //close connection
//            if (status != 0) {
//                //close that connection
//                conIt->connection->close();
//                delete conIt->connection;
//                //remove from list of active connections
//                conIt = connections.erase(conIt);
//                continue;
//            }
//            conIt++;
//        }

        //
        usleep(50000); //50ms
    }


    //shutdown server
    tcpServer->close();
    delete tcpServer;

    //delete still open connections
    conIt = connections.begin();
    while (conIt != connections.end()) {
        conIt->connection->close();
        delete conIt->connection;
        conIt++;
    }


    //delete dynamic resources
    list<DynamicResource *>::iterator resIt = dynamicResources.begin();
    //find requested resource
    while (resIt != dynamicResources.end()) {
        DynamicResource * res = *resIt++;
        delete res;
    }
    delete code404;
    delete code200;


    return 0;
}


//return 0 when connection stays open
//return -1 when connection was closed remotely
//return 1 when connection shall be closed
static int m_serve_requests(Connection& connection, list<DynamicResource *>& dynamicResources) {
    uint8_t buffer[4096];
    int status;

    //check for incomming data
    status = connection.connection->recv(buffer, sizeof(buffer) - 1);

    //connection closed ?
    if (status < 0) {
        //connection was closed remotely
        return -1;
    }

    //nothing received
    if (status == 0) {
        return 0;
    }

    //otherwise - data received
    const unsigned requestLen = (unsigned)status;
    const char * resource;
    int resourceLen;
    bool isGET;
    bool isPOST;

    //invalidate earlier requests
    connection.resource = nullptr;
    connection.hash = 0;

    //parse http request
    buffer[requestLen] = 0; //add termination, just to be safe
    resourceLen = hqsp_get_resource((const char *)buffer, &resource);
    string uri(resource, resourceLen); //uri: resource as std::string
    if (uri == "/") uri = "/index.html"; //redirect to default page


    //GET
    isGET = hqsp_is_method_get((const char *)buffer);
    if (isGET) {
        printf("GET\nURI: %s\n", uri.c_str());
        printf("\n%s : /system_info/\n", uri.c_str());
        if (uri == "/system_info" || uri == "/system_info/") {
            printf("?");
            auto * system_info = new System_info();
            printf("?");
            int fd;
            printf("?");
            system_info->run(&fd);
            printf("?");
            char buffer_out[100] = {};
            string out, buff;
            while (read(fd, buffer_out, 100) != 0)
            {
                buff = buffer_out;
                out += buff;
            }
            printf("/system_info\nSTDOUT: %s\n", out.c_str());
            return m_reply(connection, out);
        }
    }


    //POST
//    isPOST = hqsp_is_method_post((const char *)buffer);
//    if (isPOST) {
//        //POST can only deal with dynamic content
//        //find requested res
//        list<DynamicResource *>::iterator resIt = dynamicResources.begin();
//        while (resIt != dynamicResources.end()) {
//            DynamicResource * res = *resIt++;
//            if (res->uri == uri) {
//                const char * header;
//                int headerLen;
//                const char * postContent;
//                int postContentLen;
//
//                //get content type from HTML header -> set
//                headerLen = hqsp_get_header_value((const char *)buffer, "Content-Type", &header);
//                if (headerLen > 0) {
//                    string contentType(header, headerLen);
//                    res->contentType = contentType;
//                }
//
//                //get content that is sent via POST -> set
//                postContentLen = hqsp_get_post_content((const char *)buffer, requestLen, &postContent);
//                string content(postContent, postContentLen);
//                res->setContent(content);
//
//                //link resource "200 OK" to that connection in order to "acknowledge" the POST request
//                connection.resource = code200;
//                connection.hash = 0;
//                return 0;
//            }
//        }
//    }


    //when we come to that point, we havn't found the requested resource. Therfore...
    //link resource "404 Not Found" to that connection in order to "acknowledge" the request
    connection.resource = code404;
    connection.hash = 0;
    return 0;
}


//return 0 when connection stays open
//return 1 when connection shall be closed
static int m_reply(Connection& connection, const string& answer) {
    string header;
    //update client ...
    //send header
    header  = "HTTP/1.1 200\r\n";
    header += "Content-Type: text/plain\r\n";
    header += "Content-Length: " + answer + "\r\n";
    header += "\r\n";
    connection.connection->send((const uint8_t *)header.c_str(), header.length(), true);
    //send content
    connection.connection->send((const uint8_t *)answer.c_str(), answer.length());

    //invalidate request
    connection.resource = nullptr;
    connection.hash = 0;
    return 1; //instruct to close connection
}


//return 1 when connection shall be closed
static int m_reply_dynamic_content(Connection& connection)
{
    DynamicResource * resource = connection.resource;
    if (resource != NULL) {
        //check if client needs to informed about modified content
        if (resource->hash != connection.hash) {
            const string& content = resource->content;
            string header;

            //update client ...
            //send header
            header  = "HTTP/1.1 " + resource->statusCode + "\r\n";
            header += "Content-Type: " + resource->contentType + "\r\n";
            header += "Content-Hash: " + to_string(resource->hash) + "\r\n";
            header += "Content-Length: " + to_string(content.length()) + "\r\n";
            header += "\r\n";
            connection.connection->send((const uint8_t *)header.c_str(), header.length(), true);
            //send content
            connection.connection->send((const uint8_t *)content.c_str(), content.length());

            //invalidate request
            connection.resource = NULL;
            connection.hash = 0;
            return 1; //instruct to close connection
        }
    }

    //leave connectin open
    return 0;
}


//return 0 when connection stays open
//return 1 when connection shall be closed
static int m_reply_static_content(Connection& connection, const string& uri) {
    const string contentType = m_get_content_type_by_uri(uri, "application/octet-stream"); //default: binary data
    const string filePath = htmlBasePath + uri;
    ifstream file(filePath, ios::in | ios::binary);
    if (file.is_open()) {
        //get size of file
        file.seekg(0, ios::end);
        int fileSize = file.tellg();

        //read file content into tbuffer
        uint8_t* buffer = new uint8_t[fileSize];
        file.seekg(0, ios::beg);
        file.read((char *)buffer, fileSize);

        //close file
        file.close();

        //send header
        string header = "HTTP/1.1 200 OK\r\n";
        header += "Content-Type: " + contentType + "\r\n";
        header += "Content-Length: " + to_string(fileSize) + "\r\n";
        header += "\r\n";
        connection.connection->send((const uint8_t *)header.c_str(), header.length(), true);
        //send content
        connection.connection->send(buffer, fileSize);

        //free buffer
        delete[] buffer;
        return 1; //instruct to close connection
    }
    return 0; //not found
}


static string m_get_content_type_by_uri(const string& uri, const string& fallback) {
    //get file extension
    string fileExtension = uri.substr(uri.find_last_of(".") + 1);

    //text files
    if (fileExtension == "txt") {
        return "text/plain";
    } else if ((fileExtension == "htm") || (fileExtension == "html")) {
        return "text/html";
    } else if (fileExtension == "css") {
        return "text/css";
    } else if (fileExtension == "js") {
        return "text/javascript";
    }

    //image files
    if (fileExtension == "gif") {
        return "image/gif";
    } else if (fileExtension == "png") {
        return "image/png";
    } if ((fileExtension == "jpg") || (fileExtension == "jpeg")) {
        return "image/jpeg";
    } if (fileExtension == "bmp") {
        return "image/bmp";
    } if (fileExtension == "ico") {
        return "image/x-icon";
    }

    //fallback
    return fallback;
}
