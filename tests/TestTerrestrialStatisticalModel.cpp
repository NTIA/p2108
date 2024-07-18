#include "TestUtils.h"

// Test fixture for the unit tests
class TerrestrialStatisticalModelTest: public ::testing::Test {
protected:
    void SetUp() override {
        // Load test data from CSV
        testData = readTerrestrialStatisticalModelTestData(
            "TerrestrialStatisticalModelTestData.csv"
        );
    }

    // Vector to hold test data
    std::vector<TerrestrialStatisticalModelTestData> testData;
};

// Test case to verify the TerrestrialStatisticalModel function
TEST_F(TerrestrialStatisticalModelTest, TestTerrestrialStatisticalModel) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    double L_ctt__db;
    int rtn;
    for (const auto &data : testData) {
        rtn = TerrestrialStatisticalModel(
            data.f__ghz, data.d__km, data.p, L_ctt__db
        );
        EXPECT_EQ(rtn, data.rtn);
        if (rtn == SUCCESS) {
            EXPECT_NEAR(L_ctt__db, data.L_ctt__db, ABSTOL__DB);
        }
    }
}

TEST(Section3p2_InputValidationTest, Section3p2_FrequencyInvalid) {
    EXPECT_EQ(
        Section3p2_InputValidation(0.49, 1, 1), ERROR32__FREQUENCY
    );  // Frequency too low
    EXPECT_EQ(
        Section3p2_InputValidation(67.01, 1, 1), ERROR32__FREQUENCY
    );  // Frequency too high
}

TEST(Section3p2_InputValidationTest, Section3p2_DistanceInvalid) {
    EXPECT_EQ(
        Section3p2_InputValidation(20, 0.249, 1), ERROR32__DISTANCE
    );  // Distance too small
    EXPECT_EQ(
        Section3p2_InputValidation(20, 0, 1), ERROR32__DISTANCE
    );  // Distance is zero
    EXPECT_EQ(
        Section3p2_InputValidation(20, -1, 1), ERROR32__DISTANCE
    );  // Distance is negative
}

TEST(Section3p2_InputValidationTest, Section3p2_PercentageInvalid) {
    EXPECT_EQ(
        Section3p2_InputValidation(20, 1, -1), ERROR32__PERCENTAGE
    );  // p < 0
    EXPECT_EQ(
        Section3p2_InputValidation(20, 1, 0), ERROR32__PERCENTAGE
    );  // p = 0
    EXPECT_EQ(
        Section3p2_InputValidation(20, 1, 100), ERROR32__PERCENTAGE
    );  // p = 100
    EXPECT_EQ(
        Section3p2_InputValidation(20, 1, 101), ERROR32__PERCENTAGE
    );  // p > 100
}

TEST(Section3p2_InputValidationTest, Section3p2_ValidInputs) {
    // Test all edge values plus in-between values
    EXPECT_EQ(Section3p2_InputValidation(0.5, 1, 1), SUCCESS);     // f = 0.5
    EXPECT_EQ(Section3p2_InputValidation(30, 1, 1), SUCCESS);      // f = 30
    EXPECT_EQ(Section3p2_InputValidation(67, 1, 1), SUCCESS);      // f = 67
    EXPECT_EQ(Section3p2_InputValidation(30, 0.25, 1), SUCCESS);   // d = 0.25
    EXPECT_EQ(Section3p2_InputValidation(30, 100, 1), SUCCESS);    // d = 100
    EXPECT_EQ(Section3p2_InputValidation(30, 1, 0.01), SUCCESS);   // p = 0.01
    EXPECT_EQ(Section3p2_InputValidation(30, 1, 50), SUCCESS);     // p = 50
    EXPECT_EQ(Section3p2_InputValidation(30, 1, 99.99), SUCCESS);  // p = 99.99
}