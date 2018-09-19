project(run_tests)

add_executable(run_tests main.cc
    TestEigen.cc
    TestAMatrix.cc
    TestUblas.cc
)

add_definitions(
    -DBOOST_ALL_NO_LIB
)

target_include_directories(run_tests PRIVATE
    "${EIGEN3_ROOT}"
    "${AMATRIX_ROOT}/include"
    "${BOOST_ROOT}"
)

install(TARGETS run_tests DESTINATION bin)
