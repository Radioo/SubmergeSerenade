//
// Created by Radio on 14/01/2024.
//

#ifndef UIHELPERS_HPP
#define UIHELPERS_HPP

#include <vector>
#include <nfd.h>
#include <string>

class UIHelpers {
public:
    static void openFileDialog(char *outPath, const std::vector<nfdu8filteritem_t, std::allocator<nfdu8filteritem_t>> &filters);
    static void HelpMarker(const char* desc);
};



#endif //UIHELPERS_HPP
