#include "TestUtils.h"

// Test fixture for the unit tests
class AeronauticalStatisticalModelTest: public ::testing::Test {
    protected:
        void SetUp() override {
            // Load test data from CSV
            testData = readAeronauticalStatisticalModelTestData(
                "AeronauticalStatisticalModelTestData.csv"
            );
        }

        // Vector to hold test data
        std::vector<AeronauticalStatisticalModelTestData> testData;
};

// Test case to verify the AeronauticalStatisticalModel function
TEST_F(AeronauticalStatisticalModelTest, TestAeronauticalStatisticalModel) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    double L_ces__db;
    int rtn;
    for (const auto &data : testData) {
        rtn = AeronauticalStatisticalModel(
            data.f__ghz, data.theta__deg, data.p, L_ces__db
        );
        EXPECT_EQ(rtn, data.rtn);
        if (rtn == SUCCESS) {
            EXPECT_NEAR(L_ces__db, data.L_ces__db, ABSTOL__DB);
        }
    }
}

TEST(Section3p3_InputValidationTest, Section3p3_FrequencyInvalid) {
    EXPECT_EQ(
        Section3p3_InputValidation(9, 1, 1), ERROR33__FREQUENCY
    );  // Frequency too low
    EXPECT_EQ(
        Section3p3_InputValidation(101, 1, 1), ERROR33__FREQUENCY
    );  // Frequency too high
}

TEST(Section3p3_InputValidationTest, Section3p3_ThetaInvalid) {
    EXPECT_EQ(
        Section3p3_InputValidation(20, -1, 1), ERROR33__THETA
    );  // Theta negative
    EXPECT_EQ(
        Section3p3_InputValidation(20, 91, 1), ERROR33__THETA
    );  // Theta too large
}

TEST(Section3p3_InputValidationTest, Section3p3_PercentageInvalid) {
    EXPECT_EQ(
        Section3p3_InputValidation(20, 1, -1), ERROR33__PERCENTAGE
    );  // p < 0
    EXPECT_EQ(
        Section3p3_InputValidation(20, 1, 0), ERROR33__PERCENTAGE
    );  // p = 0
    EXPECT_EQ(
        Section3p3_InputValidation(20, 1, 100), ERROR33__PERCENTAGE
    );  // p = 100
    EXPECT_EQ(
        Section3p3_InputValidation(20, 1, 101), ERROR33__PERCENTAGE
    );  // p > 100
}

TEST(Section3p3_InputValidationTest, Section3p3_ValidInputs) {
    // Test all edge values plus in-between values
    EXPECT_EQ(Section3p3_InputValidation(10, 45, 50), SUCCESS);
    EXPECT_EQ(Section3p3_InputValidation(50, 45, 50), SUCCESS);
    EXPECT_EQ(Section3p3_InputValidation(100, 45, 50), SUCCESS);
    EXPECT_EQ(Section3p3_InputValidation(50, 0, 50), SUCCESS);
    EXPECT_EQ(Section3p3_InputValidation(50, 45, 50), SUCCESS);
    EXPECT_EQ(Section3p3_InputValidation(50, 90, 50), SUCCESS);
    EXPECT_EQ(Section3p3_InputValidation(50, 45, 0.1), SUCCESS);
    EXPECT_EQ(Section3p3_InputValidation(50, 45, 50), SUCCESS);
    EXPECT_EQ(Section3p3_InputValidation(50, 45, 99.9), SUCCESS);
}

TEST(Section3p3_Cot, Section3p3_TestCot) {
    EXPECT_DOUBLE_EQ(cot(0), std::numeric_limits<double>::infinity());
    EXPECT_NEAR(cot(PI / 2), 0.0, 1e-15);
    EXPECT_NEAR(cot(PI / 4), 1.0, 1e-15);
}
