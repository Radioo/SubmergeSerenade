//
// Created by Radio on 13/01/2024.
//

#include "GameUISection.hpp"

void GameUISection::renderMainTabs() {
    if(ImGui::BeginTabBar((getSectionName() + " main tabs").c_str())) {
        if(ImGui::BeginTabItem("Songs")) {
            renderSongsContent();
            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Entries")) {
            renderEntriesContent();
            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Charts")) {
            renderChartsContent();
            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Difficulties")) {
            renderDifficultiesConent();
            ImGui::EndTabItem();
        }

        if(ImGui::BeginTabItem("Import")) {
            renderImportContent();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}
