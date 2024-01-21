//
// Created by Radio on 18/01/2024.
//

#ifndef SDVXENTRY_HPP
#define SDVXENTRY_HPP

#include <cstdint>
#include <optional>
#include "../../jsonExtended.hpp"

class SDVXEntry {
public:
    std::uint32_t id{};
    std::uint32_t songId{};
    std::uint8_t version{};
    std::uint32_t internalId{};
    std::optional<std::uint8_t> infiniteVersion{};

    NLOHMANN_JSONIFY_ALL_THINGS(SDVXEntry, id, songId, version, internalId, infiniteVersion);
};

#endif //SDVXENTRY_HPP
