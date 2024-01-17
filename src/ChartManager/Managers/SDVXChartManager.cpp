//
// Created by Radio on 14/01/2024.
//

#include "SDVXChartManager.hpp"

#include <stdexcept>

#include "../Parsers/SDVX1Parser.hpp"

SDVXDiff SDVXChartManager::getDiff(const int version, const std::string& name) {
    if(version == 1) {
        if(name == "novice") {
            return SDVXDiff::NOVICE;
        }
        if(name == "advanced") {
            return SDVXDiff::ADVANCED;
        }
        if(name == "exhaust") {
            return SDVXDiff::EXHAUST;
        }

        throw std::runtime_error("Invalid difficulty name: " + name);
    }

    throw std::runtime_error("Invalid version: " + std::to_string(version));
}

std::string SDVXChartManager::parseMusicDb(int version, const std::filesystem::path &path) {
    switch(version) {
        case 1:
            parsedSongs = SDVX1Parser::parse(path);
            break;
        default:
            throw std::runtime_error("Invalid version: " + std::to_string(version));
    }

    return SDVXParsedSong::getParsedResultText(parsedSongs);
}
