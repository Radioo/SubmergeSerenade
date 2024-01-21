//
// Created by Radio on 20/01/2024.
//

#ifndef SDVXCHART_HPP
#define SDVXCHART_HPP

#include <cstdint>
#include <optional>

#include "../../jsonExtended.hpp"

class SDVXChart {
public:
    std::uint32_t id{};
    std::uint32_t songId{};
    std::optional<std::uint32_t> maxExScore{};

    NLOHMANN_JSONIFY_ALL_THINGS(SDVXChart, id, songId, maxExScore);
};

#endif //SDVXCHART_HPP
