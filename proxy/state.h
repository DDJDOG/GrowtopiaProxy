#include "gt.h"
#include "proxy.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>

GT::GT() {
    version = "3.91";
    flag = "tr";
    connecting = false;
    in_game = false;
    ghost = false;
    aapbypass = false;
    macaddr = "16:69:f9:t6:ga:6b";
    world_state = nullptr; // Assigned when state is initialized
}

void GT::send_log(const std::string& text) {
    if (!world_state) return;
    world_state->proxy->send_client_text("Log: " + text);
}

void GT::send_text_packet(const std::string& text) {
    if (!world_state) return;
    world_state->proxy->send_client_text(text);
}

void GT::solve_captcha(const std::string& text) {
    // Extract numbers and calculate sum
    std::string t = text;
    utils::replace(t, "set_default_color|`o\nadd_label_with_icon|big|`wAre you Human?``|left|206|\nadd_spacer|small|\nadd_textbox|What will be the sum of the following numbers|left|\nadd_textbox|", "");
    utils::replace(t, "|left|\nadd_text_input|captcha_answer|Answer:||32|\nend_dialog|captcha_submit||Submit|", "");

    auto number1 = t.substr(0, t.find(" +"));
    auto number2 = t.substr(number1.length() + 3, t.length());
    int result = atoi(number1.c_str()) + atoi(number2.c_str());

    send_log("Solved captcha as `2" + std::to_string(result) + "``");
    world_state->proxy->send_action_packet("action|dialog_return\ndialog_name|captcha_submit\ncaptcha_answer|" + std::to_string(result));
}

void GT::autofarm_tick() {
    if (!world_state) return;
    // Loop over all tiles in world_state and send punch action
    for (auto& tile : world_state->tiles) {
        if (tile.needs_harvest) {
            world_state->proxy->send_action_packet("action|punch\ntile|" + std::to_string(tile.id));
        }
    }
}

void GT::autopull_tick() {
    if (!world_state) return;
    for (auto& player : world_state->players) {
        if (player.autopull) {
            world_state->proxy->send_action_packet("action|pull\nplayer|" + player.uid);
        }
    }
}

void GT::pathfind_tick() {
    if (!world_state) return;
    // Example: move towards target item
    // Implementation later
}

void GT::resolve_uid_to_name(const std::string& uid) {
    if (!world_state) return;
    world_state->proxy->send_action_packet("action|friends");
    world_state->proxy->send_action_packet("action|dialog_return\ndialog_name|friends_guilds\nbuttonClicked|show_apprentices");
    world_state->proxy->send_action_packet("action|dialog_return\ndialog_name|show_mentees\nbuttonClicked|" + uid);
}
