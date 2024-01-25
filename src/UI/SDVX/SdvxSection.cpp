//
// Created by Radio on 13/01/2024.
//

#include "SdvxSection.hpp"

#include <imgui.h>
#include <stdexcept>
#include <nfd.h>
#include <vector>

#include "../UIHelpers.hpp"

void SDVXSection::renderSongsContent() {
    ImGui::BeginChild("SDVX songs table wrapper");
    if(ImGui::BeginTable("SDVX songs table", 3, defaultTableFlags)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Title");
        ImGui::TableSetupColumn("Artist");
        ImGui::TableHeadersRow();

        for(const auto& song : chartManager.currentSongs) {
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("%d", song.id);

            ImGui::TableNextColumn();
            ImGui::Text("%s", song.title.c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%s", song.artist.c_str());
        }

        ImGui::EndTable();
    }
    ImGui::EndChild();
}

void SDVXSection::renderEntriesContent() {
    ImGui::BeginChild("SDVX entries table wrapper");
    if(ImGui::BeginTable("SDVX entries table", 5, defaultTableFlags)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Song ID");
        ImGui::TableSetupColumn("Version");
        ImGui::TableSetupColumn("Internal ID");
        ImGui::TableSetupColumn("Infinite Version");
        ImGui::TableHeadersRow();

        for(const auto& entry : chartManager.currentEntries) {
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("%d", entry.id);

            ImGui::TableNextColumn();
            ImGui::Text("%d", entry.songId);

            ImGui::TableNextColumn();
            ImGui::Text("%d", entry.version);

            ImGui::TableNextColumn();
            ImGui::Text("%d", entry.internalId);

            ImGui::TableNextColumn();
            if(entry.infiniteVersion != std::nullopt) {
                ImGui::Text("%d", entry.infiniteVersion.value());
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndChild();
}

void SDVXSection::renderChartsContent() {
    ImGui::BeginChild("SDVX charts table wrapper");
    if(ImGui::BeginTable("SDVX charts table", 3, defaultTableFlags)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Song ID");
        ImGui::TableSetupColumn("Max EX Score");
        ImGui::TableHeadersRow();

        for(const auto& chart : chartManager.currentCharts) {
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("%d", chart.id);

            ImGui::TableNextColumn();
            ImGui::Text("%d", chart.songId);

            ImGui::TableNextColumn();
            if(chart.maxExScore != std::nullopt) {
                ImGui::Text("%d", chart.maxExScore.value());
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndChild();
}

void SDVXSection::renderDifficultiesConent() {
    ImGui::BeginChild("SDVX difficulties table wrapper");
    if(ImGui::BeginTable("SDVX difficulties table", 7, defaultTableFlags)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Chart ID");
        ImGui::TableSetupColumn("Version");
        ImGui::TableSetupColumn("Difficulty");
        ImGui::TableSetupColumn("Level");
        ImGui::TableSetupColumn("Limited");
        ImGui::TableSetupColumn("Distribution Date");
        ImGui::TableHeadersRow();

        for(const auto& difficulty : chartManager.currentDifficulties) {
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::Text("%d", difficulty.id);

            ImGui::TableNextColumn();
            ImGui::Text("%d", difficulty.chartId);

            ImGui::TableNextColumn();
            ImGui::Text("%d", difficulty.version);

            ImGui::TableNextColumn();
            ImGui::Text("%s", SDVXChartManager::getDiffText(static_cast<SDVXDiff>(difficulty.difficulty)).c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%d", difficulty.level);

            ImGui::TableNextColumn();
            ImGui::Text("%d", difficulty.limited);

            ImGui::TableNextColumn();
            if(difficulty.distributionDate != std::nullopt) {
                ImGui::Text("%d", difficulty.distributionDate.value());
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndChild();
}

void SDVXSection::renderImportContent() {
    if(ImGui::Button("Browse...")) {
        UIHelpers::openFileDialog(musicDbXmlPath, {{"Music DB file", "xml"}});
    }

    ImGui::SameLine();
    ImGui::InputText("music_db.xml path", musicDbXmlPath, _MAX_PATH);

    ImGui::InputInt("Version", &selectedVersion);

    if(ImGui::Button("Load")) {
        parseResultText = chartManager.parseMusicDb(selectedVersion, musicDbXmlPath);
    }

    ImGui::SameLine();
    ImGui::Text(parseResultText.c_str());

    ImGui::BeginChild("Tables wrapper");

    if(!chartManager.newSongs.empty()) {
        ImGui::SeparatorText("New songs");

        if(ImGui::BeginTable("SDVX New songs table", 5, defaultTableFlags)) {
            ImGui::TableSetupColumn("");
            ImGui::TableSetupColumn("Internal ID");
            ImGui::TableSetupColumn("Title");
            ImGui::TableSetupColumn("Artist");
            ImGui::TableSetupColumn("Charts");
            ImGui::TableHeadersRow();

            for(auto& newSong : chartManager.newSongs) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();

                ImGui::PushID(std::to_string(newSong.internalId).c_str());
                if(ImGui::Button("Add")) {
                    chartManager.addNewSong(newSong, selectedVersion);
                }
                ImGui::PopID();

                ImGui::TableNextColumn();
                ImGui::Text("%d", newSong.internalId);

                ImGui::TableNextColumn();
                ImGui::Text("%s", newSong.title.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%s", newSong.artist.c_str());

                ImGui::TableNextColumn();
                for(const auto& difficulty : newSong.difficulties) {
                    ImGui::Text("%s %d", SDVXChartManager::getDiffText(difficulty.diff).c_str(), difficulty.level);
                }
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndChild();
}
