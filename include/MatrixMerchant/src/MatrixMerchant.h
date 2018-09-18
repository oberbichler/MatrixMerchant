#pragma once

#include <complex>
#include <istream>
#include <iostream>
#include <iomanip>
#include <limits>

namespace MatrixMerchant {

static bool
TryParse(
    const std::string& text,
    std::size_t& value)
{
    char* end;

    const std::size_t parsedValue = std::strtoull(text.c_str(), &end, 10);

    const bool success = (end == &text[text.size()]);

    if (success) {
        value = parsedValue;
    }

    return success;
}

static bool
TryParse(
    const std::string& text,
    int& value)
{
    char* end;

    const int parsedValue = (int)std::strtol(text.c_str(), &end, 10);

    const bool success = (end == &text[text.size()]);

    if (success) {
        value = parsedValue;
    }

    return success;
}

static bool
TryParse(
    const std::string& text,
    float& value)
{
    char* end;

    const float parsedValue = std::strtof(text.c_str(), &end);

    const bool success = (end == &text[text.size()]);

    if (success) {
        value = parsedValue;
    }

    return success;
}

static bool
TryParse(
    const std::string& text,
    double& value)
{
    char* end;

    const double parsedValue = std::strtod(text.c_str(), &end);

    const bool success = (end == &text[text.size()]);

    if (success) {
        value = parsedValue;
    }

    return success;
}

template <typename TScalar>
struct CoordEntry
{
    static bool
    Read(
        const std::vector<std::string>& tokens,
        std::size_t& row,
        std::size_t& col,
        TScalar& value)
    {
        if (tokens.size() != 3 ||
            !TryParse(tokens[0], row) ||
            !TryParse(tokens[1], col) ||
            !TryParse(tokens[2], value)) {
            return false;
        }

        row -= 1;
        col -= 1;

        return true;
    }

    template <typename TStream>
    static void
    Write(
        TStream& stream,
        std::size_t& row,
        std::size_t& col,
        const TScalar& value)
    {
        stream << row << " " << col << " " << value << "\n";
    }
};

template <typename TScalar>
struct CoordEntry<std::complex<TScalar>>
{
    static bool
    Read(
        const std::vector<std::string>& tokens,
        std::size_t& row,
        std::size_t& col,
        std::complex<TScalar>& value)
    {
        TScalar real;
        TScalar imag;

        if (tokens.size() != 4 ||
            !TryParse(tokens[0], row) ||
            !TryParse(tokens[1], col) ||
            !TryParse(tokens[2], real) ||
            !TryParse(tokens[3], imag)) {
            return false;
        }

        row -= 1;
        col -= 1;

        value = {real, imag};

        return true;
    }

    template <typename TStream>
    static void
    Write(
        TStream& stream,
        std::size_t& row,
        std::size_t& col,
        const std::complex<TScalar>& value)
    {
        stream << row << " " << col << " " << value.real() << " " <<
            value.imag() << "\n";
    }
};

template <typename TScalar>
struct ArrayEntry
{
    static bool
    Read(
        const std::vector<std::string>& tokens,
        TScalar& value)
    {
        if (tokens.size() != 1 ||
            !TryParse(tokens[0], value)) {
            return false;
        }

        return true;
    }

    template <typename TStream>
    static void
    Write(
        TStream& stream,
        const TScalar& value)
    {
        stream << value << "\n";
    }
};

template <typename TScalar>
struct ArrayEntry<std::complex<TScalar>>
{
    static bool
    Read(
        const std::vector<std::string>& tokens,
        std::complex<TScalar>& value)
    {
        TScalar real;
        TScalar imag;

        if (tokens.size() != 2 ||
            !TryParse(tokens[0], real) ||
            !TryParse(tokens[1], imag)) {
            return false;
        }

        value = {real, imag};

        return true;
    }

    template <typename TStream>
    static void
    Write(
        TStream& stream,
        const std::complex<TScalar>& value)
    {
        stream << value.real() << " " << value.imag() << "\n";
    }
};


template <typename TScalar>
struct Precision;

template <typename TScalar>
struct Precision<typename std::complex<TScalar>>
{
    static const size_t value = std::numeric_limits<TScalar>::digits10 + 2;
};

template <typename TScalar>
struct Precision
{
    static const size_t value = std::numeric_limits<TScalar>::digits10 + 2;
};

template <typename TMatrix>
struct MatrixBuilder;

class Reader
{
private:
    template <typename TStream>
    static void
    GetDataLine(
        TStream& input,
        std::string& line)
    {
        do {
            std::getline(input, line);
        } while (line[0] == '%');
    }

    static std::vector<std::string>
    GetTokens(
        const std::string& line)
    {
        const std::string& delimiters = "\n\r\t ";

        std::vector<std::string> tokens;

        std::string::size_type lastPos = line.find_first_not_of(delimiters, 0);
        std::string::size_type pos = line.find_first_of(delimiters, lastPos);

        while (std::string::npos != pos || std::string::npos != lastPos) {
            const std::string token = line.substr(lastPos, pos - lastPos);

            tokens.push_back(token);

            lastPos = line.find_first_not_of(delimiters, pos);
            pos = line.find_first_of(delimiters, lastPos);
        }

        return tokens;
    }

public:
    template <typename TMatrix, typename TStream>
    static void
    ReadFromStream(
        TMatrix& matrix,
        TStream& input)
    {
        std::string line;
        std::vector<std::string> tokens;

        // --- read banner

        std::getline(input, line);

        tokens = GetTokens(line);

        if (tokens.size() != 5 || tokens[0] != "%%MatrixMarket" || tokens[1] != "matrix") {
            throw std::runtime_error("MatrixMarket banner invalid");
        }

        const std::string storage = tokens[2];
        const std::string type = tokens[3];
        const std::string symmetry = tokens[4];

        if (storage != "array" && storage != "coordinate") {
            throw std::runtime_error("MatrixMarket storage format '" + storage
                + "' invalid");
        }

        if (type != "pattern" && type != "integer" && type != "real"
            && type != "complex") {
            throw std::runtime_error("MatrixMarket data type '" + type +
                "' invalid");
        }

        if (symmetry != "general" && symmetry != "symmetric"
            && symmetry != "hermitian" && symmetry != "skew-symmetric") {
            throw std::runtime_error("MatrixMarket symmetry '" + symmetry
                + "' invalid");
        }

        std::cout << "storage:  " << storage << std::endl;
        std::cout << "type:     " << type << std::endl;
        std::cout << "symmetry: " << symmetry << std::endl;

        // --- read matrix size

        GetDataLine(input, line);

        tokens = GetTokens(line);

        std::size_t rows;
        std::size_t cols;
        std::size_t nonZeros = 0;

        if (storage == "array" && tokens.size() != 2) {
            throw std::runtime_error("MatrixMarket matrix size invalid");
        }

        if (storage == "coordinate" && tokens.size() != 3) {
            throw std::runtime_error("MatrixMarket matrix size invalid");
        }

        if (!TryParse(tokens[0], rows)) {
            throw std::runtime_error("MatrixMarket matrix size invalid");
        }

        if (!TryParse(tokens[1], cols)) {
            throw std::runtime_error("MatrixMarket matrix size invalid");
        }

        if (storage == "coordinate" && !TryParse(tokens[2], nonZeros)) {
            throw std::runtime_error("MatrixMarket matrix size invalid");
        }

        std::cout << "rows:     " << rows << std::endl;
        std::cout << "cols:     " << cols << std::endl;
        std::cout << "nonZeros: " << nonZeros << std::endl;

        // --- read entries

        MatrixBuilder<TMatrix> builder(matrix);

        using ScalarType = typename MatrixBuilder<TMatrix>::ScalarType;

        if (storage == "coordinate") {
            builder.BeginCoordinate(rows, cols, nonZeros);

            std::size_t entries_read = 0;

            while (entries_read < nonZeros && !input.eof()) {
                GetDataLine(input, line);

                tokens = GetTokens(line);

                std::size_t row;
                std::size_t col;
                ScalarType value;

                if (!CoordEntry<ScalarType>::Read(tokens, row, col, value)) {
                    throw std::runtime_error("MatrixMarket invalid value");
                }

                builder.SetValue(row, col, value);

                entries_read += 1;
            }

            builder.EndCoordinate();
        } else { // storage == "array"
            builder.BeginArray(rows, cols);

            for (std::size_t col = 0; col < cols && !input.eof(); col++) {
                for (std::size_t row = 0; row < rows && !input.eof(); row++) {
                    GetDataLine(input, line);

                    tokens = GetTokens(line);

                    ScalarType value;

                    if (!ArrayEntry<ScalarType>::Read(tokens, value)) {
                        throw std::runtime_error("MatrixMarket invalid value");
                    }

                    builder.SetValue(row, col, value);
                }
            }

            builder.EndArray();
        }
    }

    template <typename TMatrix>
    static void
    ReadFromFile(
        TMatrix& matrix,
        const std::string& filename)
    {
        std::ifstream file(filename.c_str());

        if (!file) {
            throw std::exception("Invalid file");
        }

        ReadFromStream(matrix, file);
    }
};

template <class T>
struct is_complex : public std::false_type { };

template <class T>
struct is_complex<std::complex<T>> : public std::true_type { };

class Writer
{
public:
    template <typename TMatrix, typename TStream>
    static void
    WriteToStream(
        const TMatrix& matrix,
        const bool coordinate,
        TStream& stream)
    {
        using ScalarType = typename MatrixBuilder<TMatrix>::ScalarType;

        std::size_t rows = MatrixBuilder<TMatrix>::Rows(matrix);
        std::size_t cols = MatrixBuilder<TMatrix>::Cols(matrix);
        std::size_t nonZeros = MatrixBuilder<TMatrix>::NonZeros(matrix);

        stream << std::setprecision(Precision<ScalarType>::value);

        stream << "%%MatrixMarket matrix";

        if (coordinate) {
            stream << " coordinate";
        } else {
            stream << " array";
        }

        if (!is_complex<ScalarType>::value) {
            stream << " real";
        } else {
            stream << " complex";
        }

        stream << " general\n";

        stream << "%Created by the MatrixMerchant "
                  "https://github.com/oberbichler/MatrixMerchant\n";

        if (coordinate) {
            stream << rows << " " << cols << " " << nonZeros << "\n";

            for (std::size_t col = 0; col < cols; col++) {
                for (std::size_t row = 0; row < rows; row++) {
                    ScalarType value = MatrixBuilder<TMatrix>::GetValue(matrix, row, col);

                    CoordEntry<ScalarType>::Write(stream, row, col, value);
                }
            }
        } else {
            stream << rows << " " << cols << "\n";

            for (std::size_t col = 0; col < cols; col++) {
                for (std::size_t row = 0; row < rows; row++) {
                    ScalarType value = MatrixBuilder<TMatrix>::GetValue(matrix, row, col);

                    ArrayEntry<ScalarType>::Write(stream, value);
                }
            }
        }
    }

    template <typename TMatrix>
    static void
    WriteToFile(
        const TMatrix& matrix,
        const std::string& path)
    {
        std::ofstream file(path);

        WriteToStream(matrix, file);

        file.close();
    }
};

} // namespace MatrixMerchant