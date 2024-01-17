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

    }
}
