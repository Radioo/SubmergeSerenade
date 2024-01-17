//
// Created by Radio on 14/01/2024.
//

#ifndef UIHELPERS_HPP
#define UIHELPERS_HPP

#include <complex.h>
#include <nfd.h>
#include <string>

class UIHelpers {
public:
    static void openFileDialog(char *outPath, const std::vector<nfdu8filteritem_t, std::allocator<nfdu8filteritem_t>> &filters);
};



#endif //UIHELPERS_HPP
