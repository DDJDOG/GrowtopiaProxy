#pragma once
#include <string>
#include <unordered_map>

class Config {
public:
    Config(const std::string& filename);

    // Load settings from file
    bool load();

    // Save settings to file
    bool save();

    // Get/Set values
    std::string get(const std::string& key, const std::string& default_value = "") const;
    void set(const std::string& key, const std::string& value);

private:
    std::string m_filename;
    std::unordered_map<std::string, std::string> m_settings;
};
