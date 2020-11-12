//
// Created by vadim on 6.11.20.
//

#ifndef LAB2_SVYAT_SERVER_H
#define LAB2_SVYAT_SERVER_H


class Server {
public:
    Server();
    void run();

private:
    list<TcpConnection> connections;
    int reply_content();
    int server_request();
    int serve_get_request();
    int serve_post_request();
};


#endif //LAB2_SVYAT_SERVER_H
