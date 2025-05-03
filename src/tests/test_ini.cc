#include "common/tt_test.h"
#include "common/tt_ini.h"

TEST(ini, test) {
    IniParse config("../data/test.ini");

    if (!config.UpdateParam()) {
        LOG_ERROR("Failed to load configuration file");
        return ;
    }

    std::string app_name;
    float version;
    bool debug_mode;

    if (config.GetValue("General", "app_name", app_name))       std::cout << "Application Name: " << app_name << std::endl;
    if (config.GetValue("General", "version", version))         std::cout << "Application Version: "<< version << std::endl;
    if (config.GetValue("General", "debug_mode", debug_mode))   std::cout << "Debug Mode: " << (debug_mode ? "Enabled" : "Disabled") << std::endl;

    std::vector<int> coordinates;
    if (config.GetVectorValue("VectorSettings", "coordinates", coordinates)) {
        std::cout << "Coordinates: ";
        for (int coord : coordinates) std::cout << coord << " ";
        std::cout << std::endl;
    }

    config.SetValue("General", "version", 1.1f);
    config.SetValue("Window", "fullscreen", true);
    config.SetValue("VectorSettings", "coordinates", std::vector<int>{1, 2, 3, 4, 5});
    config.SetValue("NewSection", "new_key", "new_value");

    // config.UpdateIni();
}

