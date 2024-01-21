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

        for(int i = 0; i < 100; i++) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%d", i);
        }

        ImGui::EndTable();
    }
    ImGui::EndChild();
}

void SDVXSection::renderEntriesContent() {
}

void SDVXSection::renderChartsContent() {
}

void SDVXSection::renderDifficultiesConent() {
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
                    // TODO
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
