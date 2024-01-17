//
// Created by Radio on 14/01/2024.
//

#ifndef SDVXCHARTMANAGER_HPP
#define SDVXCHARTMANAGER_HPP
#include <cstdlib>
#include <memory>
#include <string>

#include "../ChartManager.hpp"
#include "../Enums/SDVXDifficulty.hpp"

class SDVXChartManager : public ChartManager {
public:
    static SDVXDiff getDiff(int version, const std::string& name);
};



#endif //SDVXCHARTMANAGER_HPP
