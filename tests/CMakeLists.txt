############################################
## CONFIGURE UNIT TESTS
############################################
set(TEST_NAME "Test${LIB_NAME}")

# Add all unit test files here
add_executable(
    ${TEST_NAME}
    "TestAeronauticalStatisticalModel.cpp"
    "TestHeightGainTerminalCorrectionModel.cpp"
    "TestInverseComplementaryCumulativeDistribution.cpp"
    "TestTerrestrialStatisticalModel.cpp"
    "TestUtils.cpp"
    "TestUtils.h"
)

###########################################
## SET UP AND DISCOVER TESTS
###########################################
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(${TEST_NAME} ${LIB_NAME} GTest::gtest_main)
gtest_discover_tests(${TEST_NAME})