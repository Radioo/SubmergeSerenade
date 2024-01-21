//
// Created by Radio on 14/01/2024.
//

#ifndef SDVXCHARTMANAGER_HPP
#define SDVXCHARTMANAGER_HPP
#include <filesystem>
#include <string>

#include "../ChartManager.hpp"
#include "../Enums/SDVXDiff.hpp"
#include "../Structures/SDVXParsedSong.hpp"
#include "../Structures/SDVXSong.hpp"

class SDVXChartManager : public ChartManager {
public:
    std::vector<SDVXSong> currentSongs;

    std::vector<SDVXParsedSong> newSongs;

    static SDVXDiff getDiff(int version, const std::string& name);
    static std::string getDiffText(SDVXDiff diff);

    std::string parseMusicDb(int version, const std::filesystem::path& path);

private:
    std::vector<SDVXParsedSong> parsedSongs;

    std::optional<SDVXSong> findExistingSong(const std::string& title, const std::string& artist);
};



#endif //SDVXCHARTMANAGER_HPP
