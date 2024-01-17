//
// Created by Radio on 15/01/2024.
//

#ifndef SDVX1PARSER_HPP
#define SDVX1PARSER_HPP
#include <filesystem>
#include <unordered_map>
#include <vector>

#include "../Structures/SDVX1StaticSong.hpp"
#include "../Structures/SDVXParsedSong.hpp"


class SDVX1Parser {
public:
    static std::vector<SDVXParsedSong> parse(const std::filesystem::path& musicDbXmlPath);

private:
    static inline std::unordered_map<std::uint32_t, SDVX1StaticSong> staticSongs;

    static void loadStaticSongs();
};



#endif //SDVX1PARSER_HPP
