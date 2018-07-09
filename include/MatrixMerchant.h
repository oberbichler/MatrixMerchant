#pragma once

#include <cctype>
#include <complex>
#include <exception>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

namespace MatrixMerchant {

template <typename TMatrix>
struct MatrixBuilder { };

class Reader
{
    static std::vector<std::string>
    split(
        const std::string& str,
        const std::string& delimiters = "\n\r\t "
    )
    {
        std::vector<std::string> tokens;

        std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        std::string::size_type pos = str.find_first_of(delimiters, lastPos);

        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            lastPos = str.find_first_not_of(delimiters, pos);
            pos = str.find_first_of(delimiters, lastPos);
        }

        return tokens;
    }

    template <typename T>
    struct read;

    template <typename T>
    struct read<typename std::complex<T>>
    {
        template <typename TStream>
        static std::complex<T>
        from(
            TStream& input
        )
        {
            using ComplexType = std::complex<T>;
            
            T re(1);
            T im(0);
            
            input >> re;
            input >> im;
            
            return ComplexType(re, im);
        }
    };

    template <typename T>
    struct read
    {
        template <typename TStream>
        static T
        from(
            TStream& input
        )
        {        
            T value(1);

            input >> value;
            
            return value;
        }
    };

    template <typename TIndex = size_t>
    struct readCoordinates
    {
        template <typename TStream>
        static auto
        from(
            TStream& input
        )
        {
            TIndex row;
            TIndex col;
            
            input >> row;
            input >> col;
            
            return std::make_pair(row - 1, col - 1);
        }
    };

    template <typename TStream>
    static void
    getDataLine(
        TStream& input,
        std::string& line
    )
    {
        do {
            std::getline(input, line);
        } while (line[0] == '%');
    }

  public:
    template <typename TMatrix, typename TStream>
    static void readStream(
        TMatrix& matrix,
        TStream& input
    )
    {
        using ScalarType = typename MatrixBuilder<TMatrix>::ScalarType;
        using IndexType = typename MatrixBuilder<TMatrix>::IndexType;

        // --- read banner

        std::string line;
        std::vector<std::string> tokens;

        std::getline(input, line);
        tokens = split(line);

        if (tokens.size() != 5 || tokens[0] != "%%MatrixMarket" || tokens[1] != "matrix") {
            throw std::runtime_error("MatrixMarket banner invalid");
        }

        const auto storage  = tokens[2];
        const auto type = tokens[3];
        const auto symmetry = tokens[4];

        if (storage != "array" && storage != "coordinate") {
            throw std::runtime_error("MatrixMarket storage format '" + storage + "' invalid");
        }

        if (type != "pattern" && type != "integer" && type != "real" && type != "complex") {
            throw std::runtime_error("MatrixMarket data type '" + type + "' invalid");
        }

        if (symmetry != "general" && symmetry != "symmetric" && symmetry != "hermitian" && symmetry != "skew-symmetric") {
            throw std::runtime_error("MatrixMarket symmetry '" + symmetry + "' invalid");
        }


        // --- read matrix size

        getDataLine(input, line);



        // --- read entries

        MatrixBuilder<TMatrix> builder(matrix);
        
        if (storage == "coordinate")
        {
            tokens = split(line);

            if (tokens.size() != 3) {
                throw std::runtime_error("MatrixMarket format invalid");
            }

            IndexType rows, cols, entries;

            std::istringstream(tokens[0]) >> rows;
            std::istringstream(tokens[1]) >> cols;
            std::istringstream(tokens[2]) >> entries;

            builder.beginCoordinate(rows, cols, entries);

            IndexType entries_read = 0;

            while (entries_read < entries && !input.eof()) {
                getDataLine(input, line);
                std::istringstream is(line);

                IndexType row;
                IndexType col;
                
                std::tie(row, col) = readCoordinates<IndexType>::from(is);

                ScalarType value = read<ScalarType>::from(is);

                builder.setValue(row, col, value);

                entries_read += 1;
            }
        } else { // storage == "array"
            tokens = split(line);

            if (tokens.size() != 2) {
                throw std::runtime_error("MatrixMarket format invalid");
            }

            IndexType rows, cols;

            std::istringstream(tokens[0]) >> rows;
            std::istringstream(tokens[1]) >> cols;
            
            builder.beginArray(rows, cols);
            
            for (IndexType col = 0; col < cols && !input.eof(); ++col) {
                for (IndexType row = 0; row < rows && !input.eof(); ++row) {
                    getDataLine(input, line);
                    std::istringstream is(line);

                    ScalarType value = read<ScalarType>::from(is);

                    builder.setValue(row, col, value);
                }
            }
        }
    }

    template <typename TMatrix>
    static void
    readFile(
        TMatrix& matrix,
        const std::string& filename
    )
    {
        std::ifstream file(filename.c_str());

        if (!file) {
            throw std::exception();
        }
        
        readStream(matrix, file);
    }
};

template<class T> struct is_complex : std::false_type {};
template<class T> struct is_complex<std::complex<T>> : std::true_type {};

class Writer
{
private:
    template <typename TScalar, typename TStream>
    static void
    write(
        const std::complex<TScalar>& value,
        TStream& stream
    )
    {
        stream << value.real() << " " << value.imag();
    }

    template <typename TScalar, typename TStream>
    static void
    write(
        const TScalar& value,
        TStream& stream
    )
    {
        stream << value;
    }

    template <typename T>
    struct precision;

    template <typename T>
    struct precision<typename std::complex<T>>
    {
        static const size_t value = std::numeric_limits<T>::digits10 + 1;
    };

    template <typename T>
    struct precision
    {
        static const size_t value = std::numeric_limits<T>::digits10 + 1;
    };

public:

    template <typename TMatrix, typename TStream>
    static void
    writeStream(
        const TMatrix& matrix,
        TStream& stream
    )
    {
        using Scalar = typename MatrixBuilder<TMatrix>::ScalarType;

        auto nbRows = MatrixBuilder<TMatrix>::nbRows(matrix);
        auto nbCols = MatrixBuilder<TMatrix>::nbCols(matrix);

        stream << std::setprecision(precision<Scalar>::value);

        if (!is_complex<Scalar>::value) {
            stream << "%%MatrixMarket matrix array real general\n";
        } else {
            stream << "%%MatrixMarket matrix array complex general\n";
        }

        stream << "%Created by the MatrixMerchant "
                  "https://github.com/oberbichler/MatrixMerchant\n";

        stream << nbRows << " " << nbCols << "\n";

        for (int col = 0; col < nbCols; col++) {
            for (int row = 0; row < nbRows; row++) {
                Scalar value = MatrixBuilder<TMatrix>::value(matrix, row, col);

                stream << "  ";
                write(value, stream);
                stream << "\n";
            }
        }
    }

    template <typename TMatrix>
    static void
    writeFile(
        const TMatrix& matrix,
        const std::string& path
    )
    {
        std::ofstream file(path);

        writeStream(matrix, file);

        file.close();
    }
};

} // namespace MatrixMarket