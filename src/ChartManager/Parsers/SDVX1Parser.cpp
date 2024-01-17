//
// Created by Radio on 15/01/2024.
//

#include "SDVX1Parser.hpp"

#include <pugixml.hpp>
#include <unordered_map>

#include "../XMLHelper.hpp"
#include "../Managers/SDVXChartManager.hpp"

std::vector<SDVXParsedSong> SDVX1Parser::parse(const std::filesystem::path &musicDbXmlPath) {
    pugi::xml_document doc = XMLHelper::loadXmlFile(musicDbXmlPath);
    pugi::xml_node mdbNode = doc.child("mdb");

    std::vector<SDVXParsedSong> songs;
    for(pugi::xml_node musicNode : mdbNode.children("music")) {
        std::uint32_t internalId = musicNode.attribute("id").as_uint();

        for(pugi::xml_node difficultyNode : musicNode.children("difficulty")) {
            SDVXDiff diff = SDVXChartManager::getDiff(1, difficultyNode.attribute("attr").as_string());
            std::uint8_t level = difficultyNode.child("difnum").text().as_uint();
        }
    }

    return songs;
}
