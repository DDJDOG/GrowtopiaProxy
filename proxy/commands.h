#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

class Proxy; // Forward declaration

class Commands {
public:
    Commands(Proxy* proxy);

    // Registers a command with its callback
    void register_command(const std::string& name, std::function<void(const std::vector<std::string>& args)> callback);

    // Parses a text message and executes a command if it starts with '/'
    void handle_command(const std::string& message);

private:
    Proxy* m_proxy; // Pointer to main proxy to send packets or access server
    std::unordered_map<std::string, std::function<void(const std::vector<std::string>& args)>> m_commands;

    // Helper to split command arguments
    std::vector<std::string> split_args(const std::string& text);
};
