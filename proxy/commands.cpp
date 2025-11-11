#include "commands.h"
#include "proxy.h"   // Include the proxy class for sending packets
#include <iostream>
#include <sstream>

Commands::Commands(Proxy* proxy)
    : m_proxy(proxy)
{
    // Example built-in commands
    register_command("proxy", [this](const std::vector<std::string>& args) {
        m_proxy->send_client_text("Growtopia Proxy Commands:\n/news\n/gazette\n/discord\n...");
    });

    register_command("news", [this](const std::vector<std::string>& args) {
        m_proxy->send_client_text("Proxy News: Last Update 25.01.2024, join our Discord for more!");
    });

    register_command("gazette", [this](const std::vector<std::string>& args) {
        m_proxy->send_client_text("Growtopia Gazette: Stay tuned for updates.");
    });

    register_command("discord", [this](const std::vector<std::string>& args) {
        m_proxy->send_client_text("Join our Discord: https://discord.gg/X56gwJdxkn");
    });
}

void Commands::register_command(const std::string& name, std::function<void(const std::vector<std::string>& args)> callback) {
    m_commands[name] = callback;
}

std::vector<std::string> Commands::split_args(const std::string& text) {
    std::vector<std::string> tokens;
    std::istringstream iss(text);
    std::string token;
    while (iss >> token)
        tokens.push_back(token);
    return tokens;
}

void Commands::handle_command(const std::string& message) {
    if (message.empty() || message[0] != '/') return; // Only commands starting with '/'
    
    auto args = split_args(message.substr(1)); // Remove the '/' prefix
    if (args.empty()) return;

    auto it = m_commands.find(args[0]);
    if (it != m_commands.end()) {
        it->second(std::vector<std::string>(args.begin() + 1, args.end())); // Pass remaining args
    } else {
        m_proxy->send_client_text("Unknown command: " + args[0]);
    }
}

