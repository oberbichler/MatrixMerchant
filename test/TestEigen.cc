#include "catch.hpp"

#include <MatrixMerchant/Eigen>

#include <Eigen/Core>

#include <complex>
#include <fstream>
#include <sstream>
#include <streambuf>

TEST_CASE("Eigen: Array real General as MatrixXd", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/array_real_general.mtx");

    REQUIRE(matrix.rows() == 3);
    REQUIRE(matrix.cols() == 4);

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

TEST_CASE("Eigen: Array real General as MatrixXf", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/array_real_general.mtx");

    REQUIRE(matrix.rows() == 3);
    REQUIRE(matrix.cols() == 4);

    REQUIRE(matrix(0, 0) == -1.7874030527951525f);
    REQUIRE(matrix(1, 0) == 2.8017662727841071f);
    REQUIRE(matrix(2, 0) == -7.3458785314655870f);
    REQUIRE(matrix(0, 1) == -2.4010370783465085f);
    REQUIRE(matrix(1, 1) == 9.1842295135688801f);
    REQUIRE(matrix(2, 1) == 4.4479713459839871f);
    REQUIRE(matrix(0, 2) == 9.0628790375549286f);
    REQUIRE(matrix(1, 2) == -3.7799237041860287f);
    REQUIRE(matrix(2, 2) == 5.5080306442042399f);
    REQUIRE(matrix(0, 3) == -7.3354743327476690f);
    REQUIRE(matrix(1, 3) == -3.3000793596121447f);
    REQUIRE(matrix(2, 3) == 5.7081113423916179f);
}

TEST_CASE("Eigen: Array real General as MatrixXi", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/array_real_general.mtx");

    REQUIRE(matrix.rows() == 3);
    REQUIRE(matrix.cols() == 4);

    REQUIRE(matrix(0, 0) == -1);
    REQUIRE(matrix(1, 0) == 2);
    REQUIRE(matrix(2, 0) == -7);
    REQUIRE(matrix(0, 1) == -2);
    REQUIRE(matrix(1, 1) == 9);
    REQUIRE(matrix(2, 1) == 4);
    REQUIRE(matrix(0, 2) == 9);
    REQUIRE(matrix(1, 2) == -3);
    REQUIRE(matrix(2, 2) == 5);
    REQUIRE(matrix(0, 3) == -7);
    REQUIRE(matrix(1, 3) == -3);
    REQUIRE(matrix(2, 3) == 5);
}

TEST_CASE("Eigen: Array Integer General as MatrixXd", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/array_integer_general.mtx");

    REQUIRE(matrix.rows() == 3);
    REQUIRE(matrix.cols() == 4);

    REQUIRE(matrix(0, 0) == -9.0);
    REQUIRE(matrix(1, 0) == -5.0);
    REQUIRE(matrix(2, 0) == -8.0);
    REQUIRE(matrix(0, 1) == -1.0);
    REQUIRE(matrix(1, 1) == 5.0);
    REQUIRE(matrix(2, 1) == 1.0);
    REQUIRE(matrix(0, 2) == -6.0);
    REQUIRE(matrix(1, 2) == 7.0);
    REQUIRE(matrix(2, 2) == -8.0);
    REQUIRE(matrix(0, 3) == 9.0);
    REQUIRE(matrix(1, 3) == 3.0);
    REQUIRE(matrix(2, 3) == 3.0);
}

TEST_CASE("Eigen: Array Integer General as MatrixXf", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/array_integer_general.mtx");

    REQUIRE(matrix.rows() == 3);
    REQUIRE(matrix.cols() == 4);

    REQUIRE(matrix(0, 0) == -9.f);
    REQUIRE(matrix(1, 0) == -5.f);
    REQUIRE(matrix(2, 0) == -8.f);
    REQUIRE(matrix(0, 1) == -1.f);
    REQUIRE(matrix(1, 1) == 5.f);
    REQUIRE(matrix(2, 1) == 1.f);
    REQUIRE(matrix(0, 2) == -6.f);
    REQUIRE(matrix(1, 2) == 7.f);
    REQUIRE(matrix(2, 2) == -8.f);
    REQUIRE(matrix(0, 3) == 9.f);
    REQUIRE(matrix(1, 3) == 3.f);
    REQUIRE(matrix(2, 3) == 3.f);
}

TEST_CASE("Eigen: Array Integer General as MatrixXi", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/array_integer_general.mtx");

    REQUIRE(matrix.rows() == 3);
    REQUIRE(matrix.cols() == 4);

    REQUIRE(matrix(0, 0) == -9);
    REQUIRE(matrix(1, 0) == -5);
    REQUIRE(matrix(2, 0) == -8);
    REQUIRE(matrix(0, 1) == -1);
    REQUIRE(matrix(1, 1) == 5);
    REQUIRE(matrix(2, 1) == 1);
    REQUIRE(matrix(0, 2) == -6);
    REQUIRE(matrix(1, 2) == 7);
    REQUIRE(matrix(2, 2) == -8);
    REQUIRE(matrix(0, 3) == 9);
    REQUIRE(matrix(1, 3) == 3);
    REQUIRE(matrix(2, 3) == 3);
}

TEST_CASE("Eigen: Array Complex General as MatrixXcd", "[Reader][Eigen]")
{
    using Scalar = double;
    using Complex = std::complex<Scalar>;
    using Matrix = Eigen::Matrix<Complex, Eigen::Dynamic, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/array_complex_general.mtx");

    REQUIRE(matrix.rows() == 3);
    REQUIRE(matrix.cols() == 4);

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

TEST_CASE("Eigen: Array Complex General as MatrixXcf", "[Reader][Eigen]")
{
    using Scalar = std::complex<float>;
    using Complex = std::complex<Scalar>;
    using Matrix = Eigen::Matrix<Complex, Eigen::Dynamic, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/array_complex_general.mtx");

    REQUIRE(matrix.rows() == 3);
    REQUIRE(matrix.cols() == 4);

    REQUIRE(matrix(0, 0).real() == 6.3475699384495456f);
    REQUIRE(matrix(0, 0).imag() == 7.2543707383778369f);
    REQUIRE(matrix(1, 0).real() == -8.6063311685072641f);
    REQUIRE(matrix(1, 0).imag() == 2.5072858827017797f);
    REQUIRE(matrix(2, 0).real() == -8.0315916320117786f);
    REQUIRE(matrix(2, 0).imag() == -1.8991193467271117f);
    REQUIRE(matrix(0, 1).real() == 8.2479279251527657f);
    REQUIRE(matrix(0, 1).imag() == 0.9826791458003789f);
    REQUIRE(matrix(1, 1).real() == -7.7922395613298150f);
    REQUIRE(matrix(1, 1).imag() == -1.4988090472583906f);
    REQUIRE(matrix(2, 1).real() == -4.7440298331251043f);
    REQUIRE(matrix(2, 1).imag() == 2.7754100562267894f);
    REQUIRE(matrix(0, 2).real() == 4.2339856131784046f);
    REQUIRE(matrix(0, 2).imag() == 7.5881483892900476f);
    REQUIRE(matrix(1, 2).real() == -0.6683207826546286f);
    REQUIRE(matrix(1, 2).imag() == 0.90539482502031063f);
    REQUIRE(matrix(2, 2).real() == 7.0539735089809170f);
    REQUIRE(matrix(2, 2).imag() == 3.3949272347743857f);
    REQUIRE(matrix(0, 3).real() == 0.50032872310356353f);
    REQUIRE(matrix(0, 3).imag() == -5.6527470259273542f);
    REQUIRE(matrix(1, 3).real() == 8.2913524063734627f);
    REQUIRE(matrix(1, 3).imag() == -7.3097830459045490f);
    REQUIRE(matrix(2, 3).real() == -9.8304020948925732f);
    REQUIRE(matrix(2, 3).imag() == 4.5726971397846796f);
}

TEST_CASE("Eigen: Vector real column as column VectorXd", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<double, Eigen::Dynamic, 1>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/vector_real_column.mtx");

    REQUIRE(matrix.rows() == 3);
    REQUIRE(matrix.cols() == 1);

    REQUIRE(matrix[0] == -1.7874030527951525);
    REQUIRE(matrix[1] == 2.8017662727841071);
    REQUIRE(matrix[2] == -7.3458785314655870);
}

TEST_CASE("Eigen: Vector real column as row VectorXd", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<double, 1, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/vector_real_column.mtx");

    REQUIRE(matrix.rows() == 1);
    REQUIRE(matrix.cols() == 3);

    REQUIRE(matrix[0] == -1.7874030527951525);
    REQUIRE(matrix[1] == 2.8017662727841071);
    REQUIRE(matrix[2] == -7.3458785314655870);
}

TEST_CASE("Eigen: Vector real row as column VectorXd", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<double, Eigen::Dynamic, 1>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/vector_real_row.mtx");

    REQUIRE(matrix.rows() == 4);
    REQUIRE(matrix.cols() == 1);

    REQUIRE(matrix[0] == -1.7874030527951525);
    REQUIRE(matrix[1] == -2.4010370783465085);
    REQUIRE(matrix[2] == 9.0628790375549286);
    REQUIRE(matrix[3] == -7.3354743327476690);
}

TEST_CASE("Eigen: Vector real row as row VectorXd", "[Reader][Eigen]")
{
    using Matrix = Eigen::Matrix<double, 1, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;

    Matrix matrix;

    Reader::readFile(matrix, "./data/vector_real_row.mtx");

    REQUIRE(matrix.rows() == 1);
    REQUIRE(matrix.cols() == 4);

    REQUIRE(matrix[0] == -1.7874030527951525);
    REQUIRE(matrix[1] == -2.4010370783465085);
    REQUIRE(matrix[2] == 9.0628790375549286);
    REQUIRE(matrix[3] == -7.3354743327476690);
}

TEST_CASE( "Eigen: Write MatrixXd", "[Writer][Eigen]" ) {
    using Scalar = double;
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    using Reader = MatrixMerchant::Reader;
    using Writer = MatrixMerchant::Writer;
    
    Matrix matrix(3, 4);

    matrix(0, 0) = -1.7874030527951525;
    matrix(1, 0) = 2.8017662727841071;
    matrix(2, 0) = -7.3458785314655870;
    matrix(0, 1) = -2.4010370783465085;
    matrix(1, 1) = 9.1842295135688801;
    matrix(2, 1) = 4.4479713459839871;
    matrix(0, 2) = 9.0628790375549286;
    matrix(1, 2) = -3.7799237041860287;
    matrix(2, 2) = 5.5080306442042399;
    matrix(0, 3) = -7.3354743327476690;
    matrix(1, 3) = -3.3000793596121447;
    matrix(2, 3) = 5.7081113423916179;

    std::stringstream act_stream;
    Writer::writeStream(matrix, act_stream);
    std::string act = act_stream.str();


    std::ifstream exp_stream("./data/array_real_general.mtx");
    std::string exp((std::istreambuf_iterator<char>(exp_stream)),
        std::istreambuf_iterator<char>());

    CHECK(act == exp);
}
