//
// Created by Radio on 13/01/2024.
//

#ifndef GAMEUISECTION_HPP
#define GAMEUISECTION_HPP

#include <imgui.h>
#include <string>

class GameUISection {
public:
    GameUISection() = default;
    void renderMainTabs();

    virtual std::string getSectionName() = 0;

    virtual void renderSongsContent() = 0;
    virtual void renderEntriesContent() = 0;
    virtual void renderChartsContent() = 0;
    virtual void renderDifficultiesConent() = 0;
    virtual void renderImportContent() = 0;

    virtual ~GameUISection() = default;

protected:
    static constexpr ImGuiTableFlags defaultTableFlags = ImGuiTableFlags_SizingFixedFit;
};

#endif //GAMEUISECTION_HPP
