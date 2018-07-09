project(run_tests)

add_executable(run_tests main.cc
    TestEigen.cc
)

target_include_directories(run_tests PRIVATE
    "${EIGEN3_ROOT}"
)

install(TARGETS run_tests DESTINATION bin)
