//
// Created by Radio on 15/01/2024.
//

#ifndef SDVXPARSEDSONG_HPP
#define SDVXPARSEDSONG_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "SDVXParsedDifficulty.hpp"

struct SDVXParsedSong {
    std::uint32_t internalId;
    std::string title;
    std::string artist;
    std::vector<SDVXParsedDifficulty> difficulties;

    static std::string getParsedResultText(const std::vector<SDVXParsedSong>& parsedSongs) {
        std::size_t chartCount = 0;

        for(const auto& song : parsedSongs) {
            chartCount += song.difficulties.size();
        }

        return "Parsed " + std::to_string(parsedSongs.size()) + " songs with " + std::to_string(chartCount) + " charts.";
    }
};

#endif //SDVXPARSEDSONG_HPP
