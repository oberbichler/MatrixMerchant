#pragma once

#include "MatrixMerchant.h"

#include <Eigen/Core>

namespace MatrixMerchant {

template <typename TScalar>
struct MatrixBuilder<Eigen::Matrix<TScalar, Eigen::Dynamic, Eigen::Dynamic>>
{
    using MatrixType = Eigen::Matrix<TScalar, Eigen::Dynamic, Eigen::Dynamic>;

    using ScalarType = TScalar;

    using IndexType = typename MatrixType::Index;

    MatrixType& m_matrix;

    MatrixBuilder(
        MatrixType& matrix)
        : m_matrix(matrix)
    {
    }

    void
    beginCoordinate(
        const IndexType& rows,
        const IndexType& cols,
        const IndexType& nnz)
    {
        m_matrix.resize(rows, cols);
    }

    void
    beginArray(
        const IndexType& rows,
        const IndexType& cols)
    {
        m_matrix.resize(rows, cols);
    }

    void
    setValue(
        const IndexType& row,
        const IndexType& col,
        const ScalarType& value)
    {
        m_matrix(row, col) = value;
    }

    static const ScalarType&
    value(
        const MatrixType& matrix,
        const IndexType& row,
        const IndexType& col)
    {
        return matrix(row, col);
    }

    static IndexType
    nbRows(
        const MatrixType& matrix)
    {
        return matrix.rows();
    }

    static IndexType
    nbCols(
        const MatrixType& matrix)
    {
        return matrix.cols();
    }
};

template <typename TScalar>
struct MatrixBuilder<Eigen::Matrix<TScalar, Eigen::Dynamic, 1>>
{
    using MatrixType = Eigen::Matrix<TScalar, Eigen::Dynamic, 1>;

    using ScalarType = TScalar;

    using IndexType = typename MatrixType::Index;

    MatrixType& m_matrix;

    MatrixBuilder(
        MatrixType& matrix)
        : m_matrix(matrix)
    {
    }

    void
    beginCoordinate(
        const IndexType& rows,
        const IndexType& cols,
        const IndexType& nnz)
    {
        m_matrix.resize(rows, cols);
        m_matrix.setZero();
    }

    void
    beginArray(
        const IndexType& rows,
        const IndexType& cols)
    {
        if (rows != 1 && cols != 1) {
            // FIXME exception
        }

        IndexType size = std::max(rows, cols);

        m_matrix.resize(size, 1);
    }

    void
    setValue(
        const IndexType& row,
        const IndexType& col,
        const ScalarType& value)
    {
        if (row != 1 && col != 1) {
            // FIXME exception
        }

        IndexType index = std::max(row, col);

        m_matrix[index] = value;
    }
};

template <typename TScalar>
struct MatrixBuilder<Eigen::Matrix<TScalar, 1, Eigen::Dynamic>>
{
    using MatrixType = Eigen::Matrix<TScalar, 1, Eigen::Dynamic>;

    using ScalarType = TScalar;

    using IndexType = typename MatrixType::Index;

    MatrixType& m_matrix;

    MatrixBuilder(
        MatrixType& matrix)
        : m_matrix(matrix)
    {
    }

    void
    beginCoordinate(
        const IndexType& rows,
        const IndexType& cols,
        const IndexType& nnz)
    {
        m_matrix.resize(rows, cols);
        m_matrix.setZero();
    }

    void
    beginArray(
        const IndexType& rows,
        const IndexType& cols)
    {
        if (rows != 1 && cols != 1) {
            // FIXME exception
        }

        IndexType size = std::max(rows, cols);

        m_matrix.resize(1, size);
    }

    void
    setValue(
        const IndexType& row,
        const IndexType& col,
        const ScalarType& value)
    {
        if (row != 1 && col != 1) {
            // FIXME exception
        }

        IndexType index = std::max(row, col);

        m_matrix[index] = value;
    }
};

} // namespace MatrixMerchant
