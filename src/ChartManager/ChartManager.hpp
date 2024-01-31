//
// Created by Radio on 14/01/2024.
//

#ifndef CHARTMANAGER_HPP
#define CHARTMANAGER_HPP


class ChartManager {
public:
    virtual void commitChanges() const = 0;
    virtual void loadData() = 0;
    virtual ~ChartManager() = default;
};



#endif //CHARTMANAGER_HPP
