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
#include "processes/ps.h"

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
    code404 = new DynamicResource("/200", "404 Not Found");
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
    auto * tcpServer = new NbTcpServer();
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
    while (uri.back() == '/') {
        uri.pop_back();
    }

    //GET
    isGET = hqsp_is_method_get((const char *)buffer);
    if (isGET) {
        printf("GET\nURI: %s\n", uri.c_str());
        if (uri == "/system_info") {
            auto * system_info = new System_info();
            int fd;
            system_info->run(fd);
            char buffer_out[100] = {};
            string out, buff;
            while (read(fd, buffer_out, 100) != 0)
            {
                buff = buffer_out;
                out += buff;
            }
            printf("/system_info\nSTDOUT: %s\n", out.c_str());
            delete system_info;
            return m_reply(connection, out);
        } else if (uri == "/ps") {
            auto * ps = new Ps();
            int fd;
            ps->run(fd);
            char buffer_out[100] = {};
            string out, buff;
            while (read(fd, buffer_out, 100) != 0)
            {
                buff = buffer_out;
                out += buff;
            }
            printf("/ps\nSTDOUT: %s\n", out.c_str());
            delete ps;
            return m_reply(connection, out);
        }
    }


    //POST
    isPOST = hqsp_is_method_post((const char *)buffer);
    if (isPOST) {
        printf("POST\nURI: %s\n", uri.c_str());
        const char * postContent;
        int postContentLen;

        postContentLen = hqsp_get_post_content((const char *)buffer, requestLen, &postContent);
        printf("POST BODY\n%d\n %s\n", postContentLen, postContent);

        if (uri == "/create_process") {
            auto * create_process = new CreateProcess();
            int fd, err_fd;
            //command, args, uid, type

            string typestr = "type";
            char* typeStr = new char[typestr.size() + 1];
            strcpy(typeStr, typestr.c_str());
            const char* type;
            int typeLen = hqsp_get_post_value((const char *)buffer, requestLen, typeStr, &type);
            //todo : add check on parse
            string foreground = "foreground";
            bool is_foreground = true;
            for (int i = 0; i < foreground.size(); i++) {
                if (type[i] != foreground[i]) {
                    is_foreground = false;
                    break;
                }
            }
            printf("!\n");

            string uidstr = "uid";
            char* uidStr = new char[uidstr.size() + 1];
            strcpy(uidStr, uidstr.c_str());
            const char* uidchr;
            int uidLen = hqsp_get_post_value((const char *)buffer, requestLen, uidStr, &uidchr);
            //todo add check on parse
            int uid = 0;
            for (int i = 0; i < uidLen; i++) {
                uid *= 10;
                if (uidchr[i] >= '0' && uidchr[i] <= '9') {
                    uid += uidchr[i] - '0';
                }
            }
            printf("!\n");

            string commandstr = "command";
            char* commandStr = new char[commandstr.size() + 1];
            strcpy(commandStr, commandstr.c_str());
            const char* commandchr;
            int commandLen = hqsp_get_post_value((const char *)buffer, requestLen, commandStr, &commandchr);
            string command;
            for (int i = 0; i < commandLen; i++) {
                command.push_back(commandchr[i]);
            }
            printf("!\n");

            string argsstr = "args";
            char* argsStr = new char[argsstr.size() + 1];
            strcpy(argsStr, argsstr.c_str());
            const char* argschr;
            int argsLen = hqsp_get_post_value((const char *)buffer, requestLen, argsStr, &argschr);
            string args;
            for (int i = 0; i < argsLen; i++) {
                args.push_back(argschr[i]);
            }
            printf("!\n");

            printf("is_foreground: %d\nuid: %d\ncommand: %s\nargs: %s\n", is_foreground, uid, command.c_str(), args.c_str());

            int code = create_process->run(is_foreground, uid, command, args, fd, err_fd);
            string out;

            char buffer_out[100] = {};
            while (read(fd, buffer_out, 100) != 0)
            {
                string buff = buffer_out;
                out += buff;
            }

            char buffer_err[100] = {};
            while (read(err_fd, buffer_err, 100) != 0)
            {
                string buff = buffer_err;
                out += buff;
            }
            out += "\nCODE: " + to_string(code) + "\n";

            printf("/create_process\nSTDOUT: %s\n", out.c_str());
            delete create_process;
            code = m_reply(connection, out);
            return code;
        }
    }


    //when we come to that point, we haven't found the requested resource. Therefore...
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
    header += "Content-Length: " + to_string(answer.size()) + "\r\n";
    header += "\r\n";
    connection.connection->send((const uint8_t *)header.c_str(), header.length(), true);
    //send content
    connection.connection->send((const uint8_t *)answer.c_str(), answer.length());

    //invalidate request
    connection.resource = nullptr;
    connection.hash = 0;
    return 1; //instruct to close connection
}

//#include <bits/stdc++.h>
//using namespace std;
//
//int main() {
//    const char* body = R"(asdasd "poop": "kaka" baba)";
//    printf("%s\n", body);
//    const char* poop = "poop";
//    char* poopStart = const_cast<char *>(strstr(body, poop));
//    printf("%s\n", poopStart);
//
//    while (*poopStart != ':') {
//        printf("%s\n", poopStart);
//        poopStart++;
//    }
//    poopStart++;
//    while (*poopStart != '"') {
//        poopStart++;
//    }
//    poopStart++;
//
//    while (*poopStart != '"') {
//        poopStart++;
//    }
//    printf("%s\n", poopStart);
//}