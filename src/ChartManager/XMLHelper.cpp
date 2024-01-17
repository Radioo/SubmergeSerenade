//
// Created by Radio on 15/01/2024.
//

#include "XMLHelper.hpp"

#include <fstream>
#include <regex>
#include <iconv.h>

pugi::xml_document XMLHelper::loadXmlFile(const std::filesystem::path &path) {
    std::string raw_xml;

    std::ifstream file_stream(path);
    if(!file_stream.is_open()) {
        throw std::runtime_error("Failed to open file " + path.string());
    }

    std::streamsize file_size;
    file_stream.seekg(0, std::ios::end);
    file_size = file_stream.tellg();
    file_stream.seekg(0, std::ios::beg);

    raw_xml.resize(file_size);

    file_stream.read(raw_xml.data(), file_size);
    file_stream.close();

    std::regex encoding_pattern(R"((encoding=")(.+?)("\?>))");
    std::smatch matches;

    // Get encoding from raw_xml
    std::regex_search(raw_xml, matches, encoding_pattern);

    std::string current_encoding = matches[2].str();

    // Set UTF-8 encoding in raw_xml
    raw_xml = std::regex_replace(raw_xml, encoding_pattern, "encoding=\"UTF-8\"?>");

    // Convert raw_xml to UTF-8
    iconv_t conversion_descriptor = iconv_open("UTF-8", getEncodingForIconv(current_encoding).c_str());
    if(conversion_descriptor == reinterpret_cast<libiconv_t>(-1)) {
        throw std::runtime_error("Failed to open iconv descriptor");
    }

    char* raw_xml_ptr = raw_xml.data();
    size_t raw_xml_size = raw_xml.size();
    size_t converted_size = raw_xml_size * 4;

    std::string converted_xml;
    converted_xml.resize(converted_size);

    char* converted_xml_ptr = converted_xml.data();

    if(size_t result = iconv(conversion_descriptor, &raw_xml_ptr, &raw_xml_size,&converted_xml_ptr, &converted_size); result == static_cast<size_t>(-1)) {
        throw std::runtime_error("Failed to convert XML file " + path.string());
    }

    iconv_close(conversion_descriptor);

    pugi::xml_document document;

    if(pugi::xml_parse_result parse_result = document.load_string(converted_xml.c_str()); parse_result.status != pugi::status_ok) {
        throw std::runtime_error("Failed to parse XML file " + path.string() + ": " + parse_result.description());
    }

    return document;
}

std::string XMLHelper::getEncodingForIconv(const std::string &encoding) {
    if(encoding == "shift-jis") {
        return "CP932";
    }

    throw std::runtime_error("Unsupported encoding " + encoding);
}
