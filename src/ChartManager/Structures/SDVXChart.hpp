//
// Created by Radio on 20/01/2024.
//

#ifndef SDVXCHART_HPP
#define SDVXCHART_HPP

#include <cstdint>
#include <optional>

#include "../CsvStructure.hpp"
#include "../../jsonExtended.hpp"

class SDVXChart final : public CsvStructure {
public:
    std::uint32_t id;
    std::uint32_t songId;
    std::optional<std::uint32_t> maxExScore;

    SDVXChart(const std::uint32_t id, const std::uint32_t songId,
              const std::optional<std::uint32_t> maxExScore) : id(id), songId(songId), maxExScore(maxExScore) {
    }

    [[nodiscard]] std::string getCsvHeader() const override { return "id,songId,maxExScore"; }

    void writeCsvLine(csv::CSVWriter<std::ofstream> &writer) const override {
        std::string maxExScoreStr = maxExScore.has_value() ? std::to_string(maxExScore.value()) : "";
        writer << std::make_tuple(id, songId, maxExScoreStr);
    }

    static SDVXChart deserialize(const csv::CSVRow &row) {
        return {
            row["id"].get<std::uint32_t>(),
            row["songId"].get<std::uint32_t>(),
            row["maxExScore"].is_null() ? std::optional<std::uint32_t>() : std::optional(row["maxExScore"].get<std::uint32_t>())
        };
    }
};

#endif //SDVXCHART_HPP
