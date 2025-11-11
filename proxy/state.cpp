#include "state.h"
#include <algorithm>

State::State(Proxy* p) {
    proxy = p;
    last_world = "";
}

void State::add_player(const Player& player) {
    players.push_back(player);
}

void State::remove_player(const std::string& uid) {
    players.erase(std::remove_if(players.begin(), players.end(),
        [&uid](const Player& p) { return p.uid == uid; }), players.end());
}

Player* State::get_player(const std::string& uid) {
    for (auto& player : players) {
        if (player.uid == uid)
            return &player;
    }
    return nullptr;
}
