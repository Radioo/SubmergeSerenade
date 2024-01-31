//
// Created by Radio on 20/01/2024.
//

#ifndef SDVXDIFFICULTY_HPP
#define SDVXDIFFICULTY_HPP

#include <cstdint>
#include <optional>

#undef INFINITE

class SDVXDifficulty final : public CsvStructure {
public:
    std::uint32_t id;
    std::uint32_t chartId;
    std::uint8_t version;
    std::uint8_t difficulty;
    std::uint8_t level;
    std::uint8_t limited;
    std::optional<std::uint32_t> distributionDate;

    SDVXDifficulty(const std::uint32_t id, const std::uint32_t chartId, const std::uint8_t version,
                   const std::uint8_t difficulty, const std::uint8_t level, const std::uint8_t limited,
                   const std::optional<std::uint32_t> distributionDate) : id(id), chartId(chartId), version(version),
                                                                          difficulty(difficulty), level(level),
                                                                          limited(limited),
                                                                          distributionDate(distributionDate) {
    }

    [[nodiscard]] std::string getCsvHeader() const override {
        return "id,chartId,version,difficulty,level,limited,distributionDate";
    }

    void writeCsvLine(csv::CSVWriter<std::ofstream> &writer) const override {
        std::string distributionDateStr = distributionDate.has_value() ? std::to_string(distributionDate.value()) : "";
        writer << std::make_tuple(id, chartId, version, difficulty, level, limited, distributionDateStr);
    }

    static SDVXDifficulty deserialize(const csv::CSVRow &row) {
        return {
            row["id"].get<std::uint32_t>(),
            row["chartId"].get<std::uint32_t>(),
            row["version"].get<std::uint8_t>(),
            row["difficulty"].get<std::uint8_t>(),
            row["level"].get<std::uint8_t>(),
            row["limited"].get<std::uint8_t>(),
            row["distributionDate"].is_null() ? std::optional<std::uint32_t>() : std::optional(row["distributionDate"].get<std::uint32_t>())
        };
    }
};

#endif //SDVXDIFFICULTY_HPP
