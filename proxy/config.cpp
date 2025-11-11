#include "config.h"
#include <fstream>
#include <nlohmann/json.hpp>  // Using nlohmann/json library
#include <iostream>

using json = nlohmann::json;

Config::Config(const std::string& filename)
    : m_filename(filename)
{}

bool Config::load() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Could not open config file: " << m_filename << std::endl;
        return false;
    }

    json j;
    try {
        file >> j;
    } catch (...) {
        std::cerr << "Failed to parse config file: " << m_filename << std::endl;
        return false;
    }

    for (auto& el : j.items()) {
        m_settings[el.key()] = el.value().get<std::string>();
    }

    return true;
}

bool Config::save() {
    json j;
    for (auto& pair : m_settings) {
        j[pair.first] = pair.second;
    }

    std::ofstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Could not write config file: " << m_filename << std::endl;
        return false;
    }

    file << j.dump(4); // Pretty print with 4 spaces
    return true;
}

std::string Config::get(const std::string& key, const std::string& default_value) const {
    auto it = m_settings.find(key);
    if (it != m_settings.end()) return it->second;
    return default_value;
}

void Config::set(const std::string& key, const std::string& value) {
    m_settings[key] = value;
}
