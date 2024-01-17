//
// Created by Radio on 13/01/2024.
//

#ifndef SDVXSECTION_HPP
#define SDVXSECTION_HPP
#include "../GameUISection.hpp"
#include "../../ChartManager/Managers/SDVXChartManager.hpp"

class SDVXSection final : public GameUISection {
public:
    SDVXSection() = default;

    std::string getSectionName() override { return "SDVX"; }

    void renderSongsContent() override;
    void renderEntriesContent() override;
    void renderChartsContent() override;
    void renderDifficultiesConent() override;
    void renderImportContent() override;

private:
    SDVXChartManager chartManager = SDVXChartManager();
    char musicDbXmlPath[_MAX_PATH];
    int selectedVersion = 1;
    std::string parseResultText = "Ready";
};


#endif //SDVXSECTION_HPP
