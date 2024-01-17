//
// Created by Radio on 15/01/2024.
//

#ifndef SDVX1PARSER_HPP
#define SDVX1PARSER_HPP
#include <filesystem>
#include <vector>

#include "../Structures/SDVXParsedSong.hpp"


class SDVX1Parser {
public:
    static std::vector<SDVXParsedSong> parse(const std::filesystem::path& musicDbXmlPath);

private:
};



#endif //SDVX1PARSER_HPP
