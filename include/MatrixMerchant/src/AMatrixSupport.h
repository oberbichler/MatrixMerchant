#pragma once

#include <amatrix.h>

#include "MatrixMerchant.h"

namespace MatrixMerchant {

template <typename TScalar>
struct MatrixBuilder<AMatrix::Matrix<TScalar, AMatrix::dynamic, AMatrix::dynamic>>
{
    using MatrixType = AMatrix::Matrix<TScalar, AMatrix::dynamic, AMatrix::dynamic>;

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
        return matrix.size1();
    }

    static inline std::size_t
    Cols(
        const MatrixType& matrix)
    {
        return matrix.size2();
    }

    static inline std::size_t
    NonZeros(
        const MatrixType& matrix)
    {
        return matrix.size1() * matrix.size2();
    }
};

template <typename TScalar>
struct MatrixBuilder<AMatrix::Vector<TScalar, AMatrix::dynamic>>
{
    using MatrixType = AMatrix::Matrix<TScalar, AMatrix::dynamic, 1>;

    using ScalarType = TScalar;

    MatrixType& m_matrix;

    bool is_rowvector = false;

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
        if (rows == 1) {
            is_rowvector = true;
        } else if (cols == 1) {
            is_rowvector = false;
        } else {
            throw new std::runtime_error("Not a vector");
        }

        m_matrix.resize(rows);
        m_matrix = AMatrix::ZeroMatrix<TScalar>(rows, cols);
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
        if (rows == 1) {
            is_rowvector = true;
            m_matrix.resize(cols);
        } else if (cols == 1) {
            is_rowvector = false;
            m_matrix.resize(rows);
        } else {
            throw std::runtime_error("Not a vector");
        }
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
        if (is_rowvector) {
            m_matrix[col] = value;
        } else {
            m_matrix[row] = value;
        }
    }

    const ScalarType&
    GetValue(
        const std::size_t& row,
        const std::size_t& col)
    {
        if (is_rowvector) {
            return m_matrix[col];
        } else {
            return m_matrix[row];
        }
    }

    static inline std::size_t
    Rows(
        const MatrixType& matrix)
    {
        return matrix.size1();
    }

    static inline std::size_t
    Cols(
        const MatrixType& matrix)
    {
        return matrix.size2();
    }

    static inline std::size_t
    NonZeros(
        const MatrixType& matrix)
    {
        return matrix.size1() * matrix.size2();
    }
};

} // namespace MatrixMerchant
