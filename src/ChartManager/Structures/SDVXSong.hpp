//
// Created by Radio on 17/01/2024.
//

#ifndef SDVXSONG_HPP
#define SDVXSONG_HPP

#include <cstdint>

#include "../CsvStructure.hpp"

class SDVXSong final : public CsvStructure {
public:
    std::uint32_t id;
    std::string title;
    std::string artist;

    SDVXSong(const std::uint32_t id, std::string title, std::string artist) : id(id), title(std::move(title)),
                                                                              artist(std::move(artist)) {
    }

    [[nodiscard]] std::string getCsvHeader() const override { return "id,title,artist"; }

    void writeCsvLine(csv::CSVWriter<std::ofstream> &writer) const override {
        writer << std::make_tuple(id, title, artist);
    }

    static SDVXSong deserialize(const csv::CSVRow &row) {
        return {
            row["id"].get<uint32_t>(),
            row["title"].get<std::string>(),
            row["artist"].get<std::string>()
        };
    }
};

#endif //SDVXSONG_HPP
