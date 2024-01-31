//
// Created by Radio on 18/01/2024.
//

#ifndef SDVXENTRY_HPP
#define SDVXENTRY_HPP

#include <cstdint>
#include <optional>

#include "../CsvStructure.hpp"

class SDVXEntry final : public CsvStructure {
public:
    std::uint32_t id;
    std::uint32_t songId;
    std::uint8_t version;
    std::uint32_t internalId;
    std::optional<std::uint8_t> infiniteVersion;

    SDVXEntry(const std::uint32_t id, const std::uint32_t songId, const std::uint8_t version,
              const std::uint32_t internalId,
              const std::optional<std::uint8_t> infiniteVersion) : id(id), songId(songId), version(version),
                                                                   internalId(internalId),
                                                                   infiniteVersion(infiniteVersion) {
    }

    [[nodiscard]] std::string getCsvHeader() const override { return "id,songId,version,internalId,infiniteVersion"; }

    void writeCsvLine(csv::CSVWriter<std::ofstream> &writer) const override {
        std::string infiniteVersionStr = infiniteVersion.has_value() ? std::to_string(infiniteVersion.value()) : "";
        writer << std::make_tuple(id, songId, version, internalId, infiniteVersionStr);
    }

    static SDVXEntry deserialize(const csv::CSVRow &row) {
        return {
            row["id"].get<std::uint32_t>(),
            row["songId"].get<std::uint32_t>(),
            row["version"].get<std::uint8_t>(),
            row["internalId"].get<std::uint32_t>(),
            row["infiniteVersion"].is_null() ? std::optional<std::uint8_t>() : std::optional(row["infiniteVersion"].get<std::uint8_t>())
        };
    }

};


#endif //SDVXENTRY_HPP
