#pragma once

#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>

enum class Layout
{
    RowMajor,
    ColumnMajor
};

class Matrix
{
public:
    Matrix() = default;

    Matrix(
        std::size_t rows,
        std::size_t cols,
        Layout layout = Layout::RowMajor
    );

    [[nodiscard]] std::size_t rows() const noexcept;
    [[nodiscard]] std::size_t cols() const noexcept;
    [[nodiscard]] Layout layout() const noexcept;

    double& operator()(std::size_t row, std::size_t column);
    const double& operator()(std::size_t row, std::size_t column) const;

    void save(const std::filesystem::path& path) const;
    void load(const std::filesystem::path& path);

private:
    std::vector<double> data_;
    std::size_t rows_{};
    std::size_t cols_{};
    Layout layout_{Layout::RowMajor};
};

struct TransformedDataset
{
    Matrix matrix;
    std::vector<std::string> feature_names;
};
