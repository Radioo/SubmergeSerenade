//
// Created by Radio on 17/01/2024.
//

#ifndef SDVXSONG_HPP
#define SDVXSONG_HPP

#include <cstdint>
#include "../../jsonExtended.hpp"

class SDVXSong {
public:
    std::uint32_t id;
    std::string title;
    std::string artist;

    NLOHMANN_JSONIFY_ALL_THINGS(SDVXSong, id, title, artist);
};

#endif //SDVXSONG_HPP
