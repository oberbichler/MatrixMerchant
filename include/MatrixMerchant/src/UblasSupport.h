#pragma once

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>

#include "MatrixMerchant.h"

namespace MatrixMerchant {

template <typename TScalar>
struct MatrixBuilder<boost::numeric::ublas::matrix<TScalar>>
{
    using MatrixType = boost::numeric::ublas::matrix<TScalar>;

    using ScalarType = TScalar;

    MatrixType& m_matrix;

    MatrixBuilder(
        MatrixType& matrix)
        : m_matrix(matrix)
    {
    }

    void
    BeginCoordinate(
        const std::size_t& rows,
        const std::size_t& cols,
        const std::size_t& nonZeros)
    {
        m_matrix.resize(rows, cols);
    }

    void
    EndCoordinate()
    {
    }

    void
    BeginArray(
        const std::size_t& rows,
        const std::size_t& cols)
    {
        m_matrix.resize(rows, cols);
    }

    void
    EndArray()
    {
    }

    void
    SetValue(
        const std::size_t& row,
        const std::size_t& col,
        const ScalarType& value)
    {
        m_matrix(row, col) = value;
    }

    static inline const ScalarType&
    GetValue(
        const MatrixType& matrix,
        const std::size_t& row,
        const std::size_t& col)
    {
        return matrix(row, col);
    }

    static inline std::size_t
    Rows(
        const MatrixType& matrix)
    {
        return matrix.rows();
    }

    static inline std::size_t
    Cols(
        const MatrixType& matrix)
    {
        return matrix.cols();
    }

    static inline std::size_t
    NonZeros(
        const MatrixType& matrix)
    {
        return matrix.rows() * matrix.cols();
    }
};

template <typename TScalar>
struct MatrixBuilder<boost::numeric::ublas::vector<TScalar>>
{
    using MatrixType = boost::numeric::ublas::vector<TScalar>;

    using ScalarType = TScalar;

    MatrixType& m_matrix;

    MatrixBuilder(
        MatrixType& matrix)
        : m_matrix(matrix)
    {
    }

    void
    BeginCoordinate(
        const std::size_t& rows,
        const std::size_t& cols,
        const std::size_t& nonZeros)
    {
        m_matrix.resize(rows, cols);
        m_matrix.setZero();
    }

    void
    BeginArray(
        const std::size_t& rows,
        const std::size_t& cols)
    {
        if (rows != 1 && cols != 1) {
            // FIXME exception
        }

        std::size_t size = std::max(rows, cols);

        m_matrix.resize(size, 1);
    }

    void
    SetValue(
        const std::size_t& row,
        const std::size_t& col,
        const ScalarType& value)
    {
        if (row != 1 && col != 1) {
            // FIXME exception
        }

        std::size_t index = std::max(row, col);

        m_matrix[index] = value;
    }

    const ScalarType&
    GetValue(
        const std::size_t& row,
        const std::size_t& col)
    {
        if (row != 1 && col != 1) {
            // FIXME exception
        }

        std::size_t index = std::max(row, col);

        return m_matrix[index];
    }
};

template <typename TScalar>
struct MatrixBuilder<boost::numeric::ublas::compressed_matrix<TScalar>>
{
    using MatrixType = boost::numeric::ublas::compressed_matrix<TScalar>;

    using ScalarType = TScalar;

    MatrixType& m_matrix;

    MatrixBuilder(
        MatrixType& matrix)
        : m_matrix(matrix)
    {
    }

    void
    BeginCoordinate(
        const std::size_t& rows,
        const std::size_t& cols,
        const std::size_t& nonZeros)
    {
        m_matrix.resize(rows, cols);
        m_matrix.reserve(nonZeros);
    }

    void
    EndCoordinate()
    {
    }

    void
    BeginArray(
        const std::size_t& rows,
        const std::size_t& cols)
    {
        m_matrix.resize(rows, cols);
    }

    void
    EndArray()
    {
    }

    void
    SetValue(
        const std::size_t& row,
        const std::size_t& col,
        const ScalarType& value)
    {
        m_matrix.insert_element(row, col, value);
    }

    static inline const ScalarType&
    GetValue(
        const MatrixType& matrix,
        const std::size_t& row,
        const std::size_t& col)
    {
        return matrix(row, col);
    }

    static inline std::size_t
    Rows(
        const MatrixType& matrix)
    {
        return matrix.rows();
    }

    static inline std::size_t
    Cols(
        const MatrixType& matrix)
    {
        return matrix.cols();
    }

    static inline std::size_t
    NonZeros(
        const MatrixType& matrix)
    {
        return matrix.rows() * matrix.cols();
    }
};

} // namespace MatrixMerchant