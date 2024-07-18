#include "TestUtils.h"

#include <limits>  // For std::numeric_limits<T>::max()

// Test fixture for the unit tests
class HeightGainTerminalCorrectionModelTest: public ::testing::Test {
protected:
    void SetUp() override {
        // Load test data from CSV
        testData = readHeightGainTerminalCorrectionModelTestData(
            "HeightGainTerminalCorrectionModelTestData.csv"
        );
    }

    // Vector to hold test data
    std::vector<HeightGainTerminalCorrectionModelTestData> testData;
};

// Test case to verify the HeightGainTerminalCorrectionModel function
TEST_F(
    HeightGainTerminalCorrectionModelTest, TestHeightGainTerminalCorrectionModel
) {
    // Ensure test data was loaded
    EXPECT_NE(static_cast<int>(testData.size()), 0);
    double A_h__db;
    int rtn;
    for (const auto &data : testData) {
        rtn = HeightGainTerminalCorrectionModel(
            data.f__ghz,
            data.h__meter,
            data.w_s__meter,
            data.R__meter,
            data.clutter_type,
            A_h__db
        );
        EXPECT_EQ(rtn, data.rtn);
        if (rtn == SUCCESS) {
            EXPECT_NEAR(A_h__db, data.A_h__db, ABSTOL__DB);
        }
    }
}

TEST(Section3p1_InputValidationTest, Section3p1_FrequencyInvalid) {
    EXPECT_EQ(
        Section3p1_InputValidation(0.02, 1, 1, 1), ERROR31__FREQUENCY
    );  // Frequency too low
    EXPECT_EQ(
        Section3p1_InputValidation(3.01, 1, 1, 1), ERROR31__FREQUENCY
    );  // Frequency too high
}

TEST(Section3p1_InputValidationTest, Section3p1_AntennaHeightInvalid) {
    EXPECT_EQ(
        Section3p1_InputValidation(1, -1, 1, 1), ERROR31__ANTENNA_HEIGHT
    );  // Antenna height negative
    EXPECT_EQ(
        Section3p1_InputValidation(1, 0, 1, 1), ERROR31__ANTENNA_HEIGHT
    );  // Antenna height == 0
}

TEST(Section3p1_InputValidationTest, Section3p1_StreetWidthInvalid) {
    EXPECT_EQ(
        Section3p1_InputValidation(1, 1, -1, 1), ERROR31__STREET_WIDTH
    );  // Street width negative
    EXPECT_EQ(
        Section3p1_InputValidation(1, 1, 0, 1), ERROR31__STREET_WIDTH
    );  // Street width == 0
}

TEST(Section3p1_InputValidationTest, Section3p1_ClutterHeightInvalid) {
    EXPECT_EQ(
        Section3p1_InputValidation(1, 1, 1, -1), ERROR31__CLUTTER_HEIGHT
    );  // Clutter height negative
    EXPECT_EQ(
        Section3p1_InputValidation(1, 1, 1, 0), ERROR31__CLUTTER_HEIGHT
    );  // Clutter height == 0
}

TEST(Section3p1_InputValidationTest, Section3p1_ValidInputs) {
    // Test edge values plus in-between value for frequency
    EXPECT_EQ(Section3p1_InputValidation(0.03, 1, 1, 1), SUCCESS);
    EXPECT_EQ(Section3p1_InputValidation(1, 1, 1, 1), SUCCESS);
    EXPECT_EQ(Section3p1_InputValidation(3, 1, 1, 1), SUCCESS);
    // Test large positive values for other parameters
    EXPECT_EQ(
        Section3p1_InputValidation(1, std::numeric_limits<double>::max(), 1, 1),
        SUCCESS
    );
    EXPECT_EQ(
        Section3p1_InputValidation(1, 1, std::numeric_limits<double>::max(), 1),
        SUCCESS
    );
    EXPECT_EQ(
        Section3p1_InputValidation(1, 1, 1, std::numeric_limits<double>::max()),
        SUCCESS
    );
}

TEST(Section3p1_Equation_2aTest, Section3p1_NuLessThanLimit) {
    // Eq. 2a should return -6.03 for nu <= -0.78.
    // In practice, the parameter nu is never negative.
    EXPECT_EQ(Equation_2a(-0.78), -6.03);
    EXPECT_EQ(Equation_2a(-1), -6.03);
}

TEST(Section3p1_Equation_2aTest, Section3p1_NuAboveLimit) {
    // Test a few values with separately-computed expected results for this
    // equation
    EXPECT_NEAR(Equation_2a(-0.77), -5.96059383728336638563, 1e-13);
    EXPECT_NEAR(Equation_2a(0), 0.00285220856360571492, 1e-13);
    EXPECT_NEAR(Equation_2a(1.5), 10.75438646420360661479, 1e-13);
}

TEST(Section3p1_Equation_2bTest, TestSection3p1_Equation_2b) {
    // Test a few values with separately-computed expected results for this
    // equation
    EXPECT_DOUBLE_EQ(Equation_2b(1, 10, 5), -log10(2));
    EXPECT_DOUBLE_EQ(Equation_2b(5, 1, 2), -5 * log10(0.5));
    EXPECT_DOUBLE_EQ(Equation_2b(0, 100, 100), 0);
    EXPECT_DOUBLE_EQ(Equation_2b(-1, 10, 1), 1);
}
