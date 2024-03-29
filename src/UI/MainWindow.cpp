//
// Created by Radio on 13/01/2024.
//

#include "MainWindow.hpp"

#include <imgui.h>
#include <iostream>
#include <memory>
#include <stacktrace>

#include "SDVX/SdvxSection.hpp"

MainWindow::MainWindow() {
    const ImGuiIO& io = ImGui::GetIO();

    ImVector<ImWchar> ranges;

    constexpr ImWchar additionalRanges[] = {
        0x2200, // Mathematical Operators
        0x2600, // Miscellaneous Symbols
        0x4E00, // CJK Unified Ideographs
    };

    ImFontGlyphRangesBuilder builder;
    builder.AddRanges(additionalRanges);
    builder.AddRanges(io.Fonts->GetGlyphRangesJapanese());
    builder.BuildRanges(&ranges);

    io.Fonts->AddFontFromFileTTF("font/NotoSansCJKjp-Medium.otf", 18.0f, nullptr, ranges.Data);
    io.Fonts->Build();

    gameSections.push_back(std::make_unique<SDVXSection>());
}

void MainWindow::render() {
    try {
        ImGui::Begin("Submerge Serenade", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

        ImGui::Checkbox("Show demo window", &showDemoWindow);
        renderGameTabs();

        ImGui::End();

        if(showDemoWindow) {
            ImGui::ShowDemoWindow(&showDemoWindow);
        }
    }
    catch(std::exception& e) {
#ifdef NDEBUG
        ImGui::End();

        renderErrorPopup(e.what());
#else
        std::cout << e.what() << std::endl;
#endif
    }
    catch(...) {
#ifdef NDEBUG
        ImGui::End();

        renderErrorPopup(std::to_string(std::stacktrace::current()).c_str());
#else
        std::cout << std::to_string(std::stacktrace::current()) << std::endl;
#endif
    }
}

void MainWindow::renderErrorPopup(const char *text) {
    ImGui::OpenPopup("Error");
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if(ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("%s", text);

        if(ImGui::Button("OK")) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void MainWindow::renderGameTabs() const {
    if(ImGui::BeginTabBar("Game Tabs", ImGuiTabBarFlags_None)) {
        for(const auto& gameSection : gameSections) {
            if(ImGui::BeginTabItem(gameSection->getSectionName().c_str())) {
                gameSection->renderMainTabs();
                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
    }
}
