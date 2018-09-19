#include "catch.hpp"

#include <MatrixMerchant/AMatrix>

#include <amatrix.h>

#include <complex>
#include <fstream>
#include <sstream>
#include <streambuf>

TEST_CASE("AMatrix: Array real General as MatrixXd",
    "[AMatrix][Reader][Array][Real][General][Double]")
{
    using Matrix = AMatrix::Matrix<double, AMatrix::dynamic, AMatrix::dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix(0, 0);

    Reader::ReadFromFile(matrix, "./data/array_real_general_3_4.mtx");

    REQUIRE(matrix.size1() == 3);
    REQUIRE(matrix.size2() == 4);

    REQUIRE(matrix(0, 0) == -1.7874030527951525);
    REQUIRE(matrix(1, 0) == 2.8017662727841071);
    REQUIRE(matrix(2, 0) == -7.3458785314655870);
    REQUIRE(matrix(0, 1) == -2.4010370783465085);
    REQUIRE(matrix(1, 1) == 9.1842295135688801);
    REQUIRE(matrix(2, 1) == 4.4479713459839871);
    REQUIRE(matrix(0, 2) == 9.0628790375549286);
    REQUIRE(matrix(1, 2) == -3.7799237041860287);
    REQUIRE(matrix(2, 2) == 5.5080306442042399);
    REQUIRE(matrix(0, 3) == -7.3354743327476690);
    REQUIRE(matrix(1, 3) == -3.3000793596121447);
    REQUIRE(matrix(2, 3) == 5.7081113423916179);
}

TEST_CASE("AMatrix: Array real General as MatrixXf",
    "[AMatrix][Reader][Array][Real][General][Float]")
{
    using Matrix = AMatrix::Matrix<float, AMatrix::dynamic, AMatrix::dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix(0, 0);

    Reader::ReadFromFile(matrix, "./data/array_real_general_3_4.mtx");

    REQUIRE( matrix.size1() == 3 );
    REQUIRE( matrix.size2() == 4 );

    REQUIRE( matrix(0, 0) == -1.7874030527951525f );
    REQUIRE( matrix(1, 0) ==  2.8017662727841071f );
    REQUIRE( matrix(2, 0) == -7.3458785314655870f );
    REQUIRE( matrix(0, 1) == -2.4010370783465085f );
    REQUIRE( matrix(1, 1) ==  9.1842295135688801f );
    REQUIRE( matrix(2, 1) ==  4.4479713459839871f );
    REQUIRE( matrix(0, 2) ==  9.0628790375549286f );
    REQUIRE( matrix(1, 2) == -3.7799237041860287f );
    REQUIRE( matrix(2, 2) ==  5.5080306442042399f );
    REQUIRE( matrix(0, 3) == -7.3354743327476690f );
    REQUIRE( matrix(1, 3) == -3.3000793596121447f );
    REQUIRE( matrix(2, 3) ==  5.7081113423916179f );
}

TEST_CASE("AMatrix: Array real General as MatrixXi",
    "[AMatrix][Reader][Array][Real][General][Integer]")
{
    using Matrix = AMatrix::Matrix<int, AMatrix::dynamic, AMatrix::dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix(0, 0);

    Reader::ReadFromFile(matrix, "./data/array_integer_general_3_4.mtx");

    REQUIRE( matrix.size1() == 3 );
    REQUIRE( matrix.size2() == 4 );

    REQUIRE( matrix(0, 0) == -9 );
    REQUIRE( matrix(1, 0) == -5 );
    REQUIRE( matrix(2, 0) == -8 );
    REQUIRE( matrix(0, 1) == -1 );
    REQUIRE( matrix(1, 1) ==  5 );
    REQUIRE( matrix(2, 1) ==  1 );
    REQUIRE( matrix(0, 2) == -6 );
    REQUIRE( matrix(1, 2) ==  7 );
    REQUIRE( matrix(2, 2) == -8 );
    REQUIRE( matrix(0, 3) ==  9 );
    REQUIRE( matrix(1, 3) ==  3 );
    REQUIRE( matrix(2, 3) ==  3 );
}

TEST_CASE("AMatrix: Array complex General as MatrixXcd",
    "[AMatrix][Reader][Array][Complex][General]")
{
    using Scalar = double;
    using Complex = std::complex<Scalar>;
    using Matrix = AMatrix::Matrix<Complex, AMatrix::dynamic, AMatrix::dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix(0, 0);

    Reader::ReadFromFile(matrix, "./data/array_complex_general_3_4.mtx");

    REQUIRE(matrix.size1() == 3);
    REQUIRE(matrix.size2() == 4);

    REQUIRE(matrix(0, 0).real() == 6.3475699384495456);
    REQUIRE(matrix(0, 0).imag() == 7.2543707383778369);
    REQUIRE(matrix(1, 0).real() == -8.6063311685072641);
    REQUIRE(matrix(1, 0).imag() == 2.5072858827017797);
    REQUIRE(matrix(2, 0).real() == -8.0315916320117786);
    REQUIRE(matrix(2, 0).imag() == -1.8991193467271117);
    REQUIRE(matrix(0, 1).real() == 8.2479279251527657);
    REQUIRE(matrix(0, 1).imag() == 0.9826791458003789);
    REQUIRE(matrix(1, 1).real() == -7.7922395613298150);
    REQUIRE(matrix(1, 1).imag() == -1.4988090472583906);
    REQUIRE(matrix(2, 1).real() == -4.7440298331251043);
    REQUIRE(matrix(2, 1).imag() == 2.7754100562267894);
    REQUIRE(matrix(0, 2).real() == 4.2339856131784046);
    REQUIRE(matrix(0, 2).imag() == 7.5881483892900476);
    REQUIRE(matrix(1, 2).real() == -0.6683207826546286);
    REQUIRE(matrix(1, 2).imag() == 0.90539482502031063);
    REQUIRE(matrix(2, 2).real() == 7.0539735089809170);
    REQUIRE(matrix(2, 2).imag() == 3.3949272347743857);
    REQUIRE(matrix(0, 3).real() == 0.50032872310356353);
    REQUIRE(matrix(0, 3).imag() == -5.6527470259273542);
    REQUIRE(matrix(1, 3).real() == 8.2913524063734627);
    REQUIRE(matrix(1, 3).imag() == -7.3097830459045490);
    REQUIRE(matrix(2, 3).real() == -9.8304020948925732);
    REQUIRE(matrix(2, 3).imag() == 4.5726971397846796);
}
