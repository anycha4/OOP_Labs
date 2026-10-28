#pragma once

#include <cstddef>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

#include "matrix.h"

struct HistogramBin
{
    double lower_bound{};
    double upper_bound{};
    std::size_t count{};
};

struct NumericColumn
{
    std::vector<std::optional<double>> values;
};

struct CategoricalColumn
{
    std::vector<std::optional<std::string>> values;
};

using Column = std::variant<NumericColumn, CategoricalColumn>;

struct NumericFeatureInfo
{
    std::size_t missing_count{};

    double min{};
    double max{};
    double mean{};
    double variance{};

    double median{};
    double q05{};
    double q25{};
    double q75{};
    double q95{};

    std::vector<HistogramBin> histogram;
};

struct CategoricalFeatureInfo
{
    std::size_t missing_count{};

    std::vector<std::string> categories;
    std::unordered_map<std::string, std::size_t> frequencies;
};

using FeatureInfo = std::variant<NumericFeatureInfo, CategoricalFeatureInfo>;
using DatasetInfo = std::unordered_map<std::string, FeatureInfo>;

class Dataset
{
public:
    void loadFromCSV(
        const std::filesystem::path& path,
        char sep,
        bool has_header,
        std::string_view missing_str
    );

    void automaticTypeDetection(double threshold);

    [[nodiscard]] DatasetInfo analyze() const;

    void impute(const DatasetInfo& info);

    [[nodiscard]] TransformedDataset transform(const DatasetInfo& info) const;

private:
    std::unordered_map<std::string, Column> columns_;
    std::vector<std::string> feature_names_;
};
