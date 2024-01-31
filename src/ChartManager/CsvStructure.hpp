//
// Created by Radio on 30/01/2024.
//

#ifndef CSVSTRUCTURE_HPP
#define CSVSTRUCTURE_HPP

#include <string>
#include <csv.hpp>
#include <filesystem>


class CsvStructure {
public:
    [[nodiscard]] virtual std::string getCsvHeader() const = 0;

    virtual void writeCsvLine(csv::CSVWriter<std::ofstream> &writer) const = 0;

    template<class T>
    static void serialize(const std::vector<T> &structures, const std::string &fileName);

    template<class T>
    static void deserialize(std::vector<T> &structures, const std::string &fileName,
                            std::function<T(const csv::CSVRow &)> structureDeserializeFunction);

    virtual ~CsvStructure() = default;
};

template<class T>
void CsvStructure::serialize(const std::vector<T> &structures, const std::string &fileName) {
    if (structures.empty()) {
        return;
    }

    std::ofstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + fileName);
    }

    file << structures[0].getCsvHeader() << std::endl;

    auto writer = csv::make_csv_writer(file);

    for (const auto &structure: structures) {
        structure.writeCsvLine(writer);
    }

    file.close();
}

template<class T>
void CsvStructure::deserialize(std::vector<T> &structures, const std::string &fileName,
                               std::function<T(const csv::CSVRow &)> structureDeserializeFunction) {
    for (csv::CSVReader reader(fileName); const auto &row: reader) {
        structures.emplace_back(structureDeserializeFunction(row));
    }
}

#endif //CSVSTRUCTURE_HPP
