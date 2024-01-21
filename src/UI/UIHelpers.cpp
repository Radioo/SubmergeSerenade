//
// Created by Radio on 14/01/2024.
//

#include "UIHelpers.hpp"

#include <stdexcept>
#include <string>
#include <vector>
#include <imgui.h>

void UIHelpers::openFileDialog(char* outPath, const std::vector<nfdfilteritem_t> &filters) {
    NFD_Init();

    nfdchar_t* tempOutPath = nullptr;
    const nfdresult_t result = NFD_OpenDialog(&tempOutPath, filters.data(), filters.size(), nullptr);
    if(result != NFD_OKAY && result != NFD_CANCEL) {
        const std::string error = NFD_GetError();
        NFD_Quit();

        throw std::runtime_error(error);
    }

    if(result == NFD_OKAY) {
        strcpy_s(outPath, _MAX_PATH, tempOutPath);
        NFD_FreePath(tempOutPath);
    }

    NFD_Quit();
}

void UIHelpers::HelpMarker(const char *desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip()) {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
