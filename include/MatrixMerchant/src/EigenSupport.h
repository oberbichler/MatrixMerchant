#pragma once

#include <Eigen/Core>
#include <Eigen/Sparse>

#include "MatrixMerchant.h"

namespace MatrixMerchant {

template <typename TScalar>
struct MatrixBuilder<Eigen::Matrix<TScalar, Eigen::Dynamic, Eigen::Dynamic>>
{
    using MatrixType = Eigen::Matrix<TScalar, Eigen::Dynamic, Eigen::Dynamic>;

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
struct MatrixBuilder<Eigen::Matrix<TScalar, Eigen::Dynamic, 1>>
{
    using MatrixType = Eigen::Matrix<TScalar, Eigen::Dynamic, 1>;

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
            m_matrix.resize(cols);
        } else if (cols == 1) {
            is_rowvector = false;
            m_matrix.resize(rows);
        } else {
            throw new std::runtime_error("Not a vector");
        }

        m_matrix.setZero();
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
    EndCoordinate()
    {
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
struct MatrixBuilder<Eigen::Matrix<TScalar, 1, Eigen::Dynamic>>
{
    using MatrixType = Eigen::Matrix<TScalar, 1, Eigen::Dynamic>;

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
            m_matrix.resize(cols);
        } else if (cols == 1) {
            is_rowvector = false;
            m_matrix.resize(rows);
        } else {
            throw new std::runtime_error("Not a vector");
        }

        m_matrix.setZero();
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
    EndCoordinate()
    {
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
struct MatrixBuilder<Eigen::SparseMatrix<TScalar>>
{
    using MatrixType = Eigen::SparseMatrix<TScalar>;

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
        m_matrix.insert(row, col) = value;
    }

    static inline const ScalarType&
    GetValue(
        const MatrixType& matrix,
        const std::size_t& row,
        const std::size_t& col)
    {
        return matrix.coeff(row, col);
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