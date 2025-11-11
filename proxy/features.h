#pragma once

struct Features {
    // Main toggles
    bool autofarm = false;
    bool autoharvest = false;
    bool autoplant = false;
    bool autopull = false;
    bool autoban = false;
    bool pathfind = false;

    // Player/world manipulation
    bool pullall = false;
    bool kickall = false;
    bool banall = false;

    // Visuals / UI
    bool fps_unlock = false;
    bool antigravity = false;
    bool hideall = false;
    bool skin_custom = false;

    // Shortcuts / auto actions
    bool fastvend = false;
    bool fastdrop = false;
    bool automsg = false;

    // Autohost / path positions
    bool autohost = false;

    // Other misc features
    bool blink_skin = false;
    bool fakeban = false;

    // Add more features as needed
};
