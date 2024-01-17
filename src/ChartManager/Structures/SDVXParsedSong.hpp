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
};

#endif //SDVXPARSEDSONG_HPP
