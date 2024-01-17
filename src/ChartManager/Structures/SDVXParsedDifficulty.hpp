//
// Created by Radio on 15/01/2024.
//

#ifndef SDVXPARSEDDIFFICULTY_HPP
#define SDVXPARSEDDIFFICULTY_HPP
#include "../Enums/SDVXDifficulty.hpp"

#include <cstdint>
#include <optional>

struct SDVXParsedDifficulty {
    SDVXDiff diff;
    std::uint8_t level;
    std::optional<std::uint8_t> infiniteVersion;
    std::optional<std::uint32_t> maxExScore;
};

#endif //SDVXPARSEDDIFFICULTY_HPP