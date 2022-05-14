//
// Created by Jin on 5/14/22.
//

#ifndef MEMORY_GAME_REQUEST_HANDLER_H
#define MEMORY_GAME_REQUEST_HANDLER_H

#include "../common/network/responses/server_response.h"
#include "../common/network/requests/client_request.h"
#include "../common/network/responses/request_response.h"

class request_handler {
public:
    static request_response* handle_request(const client_request* const req);
};

#endif //MEMORY_GAME_REQUEST_HANDLER_H
