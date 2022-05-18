//
// Created by Jin on 5/14/22.
//

#include "request_handler.h"

#include "request_handler.h"

#include "player_manager.h"
#include "game_instance_manager.h"
#include "game_instance.h"

#include "../common/network/requests/join_game_request.h"
#include "../common/network/requests/start_game_request.h"
#include "../common/network/requests/flip_card_request.h"
#include "../common/network/requests/shuffle_request.h"

request_response *request_handler::handle_request(const client_request *const req) {
    // Prepare variables that are used by every request type
    Player *player;
    std::string err;
    game_instance *game_instance_ptr = nullptr;

    // Get common properties of requests
    RequestType type = req->get_type();
    std::string req_id = req->get_req_id();
    std::string game_id = req->get_game_id();
    std::string player_id = req->get_player_id();

    // Switch behavior according to request type
    switch (type) {
        // ####### JOIN GAME ######## //
        case RequestType::join_game: {
            std::string player_name = ((join_game_request *) req)->get_player_name();

            // Create new player or get existing one with that name
            player_manager::add_or_get_player(player_name, player_id, player);

            if (game_id.empty()) {
                // join any game
                if (game_instance_manager::try_add_player_to_any_game(player, game_instance_ptr, err)) {
                    // game_instance_ptr got updated to the joined game

                    // return response with full game_state attached
                    return new request_response(game_instance_ptr->get_id(), req_id, true,
                                                game_instance_ptr->get_game_state()->to_json(), err);
                } else {
                    // failed to find game to join
                    return new request_response("", req_id, false, nullptr, err);
                }
            } else {
                // join a specific game denoted by req->get_game_id()
                if (game_instance_manager::try_get_game_instance(game_id, game_instance_ptr)) {
                    if (game_instance_manager::try_add_player(player, game_instance_ptr, err)) {
                        // return response with full game_state attached
                        return new request_response(game_id, req_id, true,
                                                    game_instance_ptr->get_game_state()->to_json(), err);
                    } else {
                        // failed to join requested game
                        return new request_response("", req_id, false, nullptr, err);
                    }
                } else {
                    // failed to find requested game
                    return new request_response("", req_id, false, nullptr, "Requested game could not be found.");
                }
            }
        }

        // ####### START GAME ######## //
        case RequestType::start_game : {
            if (game_instance_manager::try_get_player_and_game_instance(player_id, player, game_instance_ptr, err)) {
                if (game_instance_ptr->start_game(player, err)) {
                    return new request_response(game_instance_ptr->get_id(), req_id, true,
                                                game_instance_ptr->get_game_state()->to_json(), err);
                }
            }
            return new request_response("", req_id, false, nullptr, err);
        }

        // ####### flip card ######## //
        case RequestType::flip_card : {
            std::vector<int> pos = ((flip_card_request *) req)->get_position();
            int row = pos[0], col = pos[1];
            if (game_instance_manager::try_get_player_and_game_instance(player_id, player, game_instance_ptr, err)) {
                if (game_instance_ptr->flip_card(player, row, col, err)) {
                    return new request_response(game_instance_ptr->get_id(), req_id, true,
                                                game_instance_ptr->get_game_state()->to_json(), err);
                }
            }
            return new request_response("", req_id, false, nullptr, err);
        }

        // ####### shuffle card ######## //
        case RequestType::shuffle : {
            if (game_instance_manager::try_get_player_and_game_instance(player_id, player, game_instance_ptr, err)) {
                if (game_instance_ptr->shuffle(player, err)) {
                    return new request_response(game_instance_ptr->get_id(), req_id, true,
                                                game_instance_ptr->get_game_state()->to_json(), err);
                }
            }
            return new request_response("", req_id, false, nullptr, err);
        }

            // ##################### UNKNOWN REQUEST ##################### //
        default:
            return new request_response("", req_id, false, nullptr, "Unknown RequestType " + type);
    }
}

