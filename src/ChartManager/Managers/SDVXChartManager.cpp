//
// Created by Radio on 14/01/2024.
//

#include "SDVXChartManager.hpp"

#include <stdexcept>

#include "../Parsers/SDVX1Parser.hpp"
#include "../Structures/SDVXDifficulty.hpp"

SDVXChartManager::SDVXChartManager() {
    loadData();
}

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

std::string SDVXChartManager::getDiffText(SDVXDiff diff) {
    switch(diff) {
        case SDVXDiff::NOVICE:
            return "NOV";
        case SDVXDiff::ADVANCED:
            return "ADV";
        case SDVXDiff::EXHAUST:
            return "EXH";
        case SDVXDiff::INFINITE:
            return "INF";
        case SDVXDiff::MAXIMUM:
            return "MXM";
        default:
            throw std::runtime_error("Invalid diff: " + std::to_string(static_cast<int>(diff)));
    }
}

void SDVXChartManager::addNewSong(const SDVXParsedSong &parsedSong, int version) {
    const std::uint32_t newSongId = currentSongs.empty() ? 1 : currentSongs.back().id + 1;
    const std::uint32_t newEntryId = currentEntries.empty() ? 1 : currentEntries.back().id + 1;

    currentSongs.emplace_back(newSongId, parsedSong.title, parsedSong.artist);
    currentEntries.emplace_back(newEntryId, newSongId, static_cast<std::uint8_t>(version), parsedSong.internalId, parsedSong.infiniteVersion);

    for(const auto& difficulty : parsedSong.difficulties) {
        const std::uint32_t newChartId = currentCharts.empty() ? 1 : currentCharts.back().id + 1;
        const std::uint32_t newDifficultyId = currentDifficulties.empty() ? 1 : currentDifficulties.back().id + 1;

        currentCharts.emplace_back(newChartId, newSongId, std::nullopt);
        currentDifficulties.emplace_back(
            newDifficultyId,
            newChartId,
            static_cast<std::uint8_t>(version),
            std::to_underlying<SDVXDiff>(difficulty.diff),
            difficulty.level,
            difficulty.limited,
            std::nullopt
        );
    }

    erase_if(newSongs, [&](const SDVXParsedSong& song) {
        return song.internalId == parsedSong.internalId;
    });
}

std::string SDVXChartManager::parseMusicDb(int version, const std::filesystem::path &path) {
    switch(version) {
        case 1:
            parsedSongs = SDVX1Parser::parse(path);
            break;
        default:
            throw std::runtime_error("Invalid version: " + std::to_string(version));
    }

    for(auto& parsedSong : parsedSongs) {
        if(auto existingSong = findExistingSong(parsedSong.title, parsedSong.artist); existingSong == std::nullopt) {
            newSongs.push_back(parsedSong);
        }
    }

    return SDVXParsedSong::getParsedResultText(parsedSongs);
}

void SDVXChartManager::loadData() {
    CsvStructure::deserialize<SDVXSong>(currentSongs, "sdvx_songs.csv", SDVXSong::deserialize);
    CsvStructure::deserialize<SDVXEntry>(currentEntries, "sdvx_entries.csv", SDVXEntry::deserialize);
    CsvStructure::deserialize<SDVXChart>(currentCharts, "sdvx_charts.csv", SDVXChart::deserialize);
    CsvStructure::deserialize<SDVXDifficulty>(currentDifficulties, "sdvx_difficulties.csv", SDVXDifficulty::deserialize);
}

void SDVXChartManager::commitChanges() const {
    CsvStructure::serialize<SDVXSong>(currentSongs, "sdvx_songs.csv");
    CsvStructure::serialize<SDVXEntry>(currentEntries, "sdvx_entries.csv");
    CsvStructure::serialize<SDVXChart>(currentCharts, "sdvx_charts.csv");
    CsvStructure::serialize<SDVXDifficulty>(currentDifficulties, "sdvx_difficulties.csv");
}

std::optional<SDVXSong> SDVXChartManager::findExistingSong(const std::string &title, const std::string &artist) {
    for(auto& song : currentSongs) {
        if(song.title == title && song.artist == artist) {
            return song;
        }
    }

    return std::nullopt;
}

