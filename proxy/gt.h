#pragma once
#include <string>
#include <vector>
#include "state.h"

class GT {
public:
    GT();

    // Logging and sending messages to client
    void send_log(const std::string& text);
    void send_text_packet(const std::string& text);

    // Commands & automation
    void solve_captcha(const std::string& text);
    void autofarm_tick(); // Called repeatedly when autofarm is enabled
    void autopull_tick(); // Pull players automatically
    void pathfind_tick(); // Pathfinding actions

    // Player / account info
    void resolve_uid_to_name(const std::string& uid);

    // Settings
    std::string version;
    std::string flag;
    bool connecting;
    bool in_game;
    bool ghost;
    bool aapbypass;

    // MAC address (fake / for proxy)
    std::string macaddr;

    // Pointer to current world state
    State* world_state;
};
