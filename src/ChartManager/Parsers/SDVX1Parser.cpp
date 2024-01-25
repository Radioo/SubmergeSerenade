//
// Created by Radio on 15/01/2024.
//

#include "SDVX1Parser.hpp"

#include <pugixml.hpp>
#include <fstream>

#include "../XMLHelper.hpp"
#include "../Managers/SDVXChartManager.hpp"

std::vector<SDVXParsedSong> SDVX1Parser::parse(const std::filesystem::path &musicDbXmlPath) {
    loadStaticSongs();

    const pugi::xml_document doc = XMLHelper::loadXmlFile(musicDbXmlPath);
    const pugi::xml_node mdbNode = doc.child("mdb");

    std::vector<SDVXParsedSong> songs;
    for(pugi::xml_node musicNode : mdbNode.children("music")) {
        std::uint32_t internalId = musicNode.attribute("id").as_uint();
        const std::string title = staticSongs[internalId].name;
        const std::string artist = staticSongs[internalId].artist;

        SDVXParsedSong parsedSong = {internalId, title, artist};

        for(pugi::xml_node difficultyNode : musicNode.children("difficulty")) {
            SDVXDiff diff = SDVXChartManager::getDiff(1, difficultyNode.attribute("attr").as_string());
            std::uint8_t level = difficultyNode.child("difnum").text().as_uint();

            parsedSong.difficulties.emplace_back(diff, level, 2);
        }

        songs.push_back(parsedSong);
    }

    return songs;
}

void SDVX1Parser::loadStaticSongs() {
    std::ifstream ifs("./static/SDVX1Songs.json", std::ios::binary);

    nlohmann::json json;
    ifs >> json;

    ifs.close();

    for(const auto songs = json.get<std::vector<SDVX1StaticSong>>(); const auto& song : songs) {
        staticSongs[song.id] = song;
    }
}
