//
// Created by Radio on 15/01/2024.
//

#ifndef XMLHELPER_HPP
#define XMLHELPER_HPP

#include <pugixml.hpp>
#include <filesystem>

class XMLHelper {
public:
    static pugi::xml_document loadXmlFile(const std::filesystem::path& path);

private:
    static std::string getEncodingForIconv(const std::string& encoding);
};



#endif //XMLHELPER_HPP
