#ifndef MYSERVER_HPP
#define MYSERVER_HPP

#include "../server/server.hpp"

class MyServer : public Server {
public:
    MyServer(int port = 5000);
};

#endif