//
// Created by Radio on 14/01/2024.
//

#include "SDVXChartManager.hpp"

#include <stdexcept>

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
