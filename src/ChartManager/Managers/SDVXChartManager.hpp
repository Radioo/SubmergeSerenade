//
// Created by Radio on 14/01/2024.
//

#ifndef SDVXCHARTMANAGER_HPP
#define SDVXCHARTMANAGER_HPP
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <string>

#include "../ChartManager.hpp"
#include "../Enums/SDVXDifficulty.hpp"
#include "../Structures/SDVXParsedSong.hpp"

class SDVXChartManager : public ChartManager {
public:
    static SDVXDiff getDiff(int version, const std::string& name);

    std::string parseMusicDb(int version, const std::filesystem::path& path);

private:
    std::vector<SDVXParsedSong> parsedSongs;
};



#endif //SDVXCHARTMANAGER_HPP
