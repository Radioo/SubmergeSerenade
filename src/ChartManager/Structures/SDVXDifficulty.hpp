//
// Created by Radio on 20/01/2024.
//

#ifndef SDVXDIFFICULTY_HPP
#define SDVXDIFFICULTY_HPP

#include <cstdint>
#include <optional>

#include "../../jsonExtended.hpp"

class SDVXDifficulty {
public:
    std::uint32_t id{};
    std::uint32_t chartId{};
    std::uint8_t version{};
    std::uint8_t difficulty{};
    std::uint8_t level{};
    std::uint8_t limited{};
    std::optional<std::uint32_t> distributionDate;

    NLOHMANN_JSONIFY_ALL_THINGS(SDVXDifficulty, id, chartId, version, difficulty, level, limited, distributionDate);
};

#endif //SDVXDIFFICULTY_HPP
