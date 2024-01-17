//
// Created by Radio on 13/01/2024.
//

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <memory>
#include <vector>

#include "GameUISection.hpp"

class MainWindow {
public:
    MainWindow();
    void render();

private:
    bool showDemoWindow = false;

    std::vector<std::unique_ptr<GameUISection>> gameSections;

    static void renderErrorPopup(const char* text);
    void renderGameTabs() const;
};

#endif //MAINWINDOW_HPP
