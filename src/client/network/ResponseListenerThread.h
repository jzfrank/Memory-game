//
// Created by Jin on 5/14/22.
//

#ifndef MEMORY_GAME_RESPONSELISTENERTHREAD_H
#define MEMORY_GAME_RESPONSELISTENERTHREAD_H

#include <functional>
#include <wx/wx.h>
#include "sockpp/tcp_socket.h"
#include "sockpp/tcp_connector.h"

class ResponseListenerThread : public wxThread {
public:
    ResponseListenerThread(sockpp::tcp_connector* connection);
    ~ResponseListenerThread();

protected:
    virtual ExitCode Entry();

private:
    void outputError(std::string title, std::string message);

    sockpp::tcp_connector* _connection;
};

#endif //MEMORY_GAME_RESPONSELISTENERTHREAD_H
