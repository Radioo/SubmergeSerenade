//
// Created by Radio on 17/01/2024.
//

#ifndef SDVX1STATICSONG_HPP
#define SDVX1STATICSONG_HPP

#include <cstdint>
#include <string>

#include "../../jsonExtended.hpp"

class SDVX1StaticSong {
public:
    std::uint32_t id;
    std::string name;
    std::string artist;

    NLOHMANN_JSONIFY_ALL_THINGS(SDVX1StaticSong, id, name, artist);
};

#endif //SDVX1STATICSONG_HPP
