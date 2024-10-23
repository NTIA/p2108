#include "TestDriver.h"


TEST_F(DriverTest, MissingOptionError1) {
    // Test case: missing option between two provided flags
    std::string cmd = executable + " -i -o out.txt";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__MISSING_OPTION);
}

TEST_F(DriverTest, MissingOptionError2) {
    // Test case: missing option at the end of command
    std::string cmd = executable + " -i";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__MISSING_OPTION);
}

TEST_F(DriverTest, InvalidOptionError) {
    std::string cmd = executable + " -X";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__INVALID_OPTION);
}

TEST_F(DriverTest, OpeningInputFileError) {
    int rtn = RunDriver("/invalid/path/input.xyz", "ASM", "out.txt");
    EXPECT_EQ(rtn, DRVRERR__OPENING_INPUT_FILE);
}

TEST_F(DriverTest, OpeningOutputFileError) {
    // Provide valid inputs but invalid output file path
    std::string inputs = "f__ghz,10\ntheta__deg,10.5\np,45";
    int rtn = RunDriverWithInputFile(inputs, "ASM", "/invalid/path/output.xyz");
    EXPECT_EQ(rtn, DRVRERR__OPENING_OUTPUT_FILE);
}

TEST_F(DriverTest, ValidationInFileError) {
    std::string cmd = executable + " -o out.txt -model ASM";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__VALIDATION_IN_FILE);
}

TEST_F(DriverTest, ValidationOutFileError) {
    // Input file does not need to exist here, just has to be specified
    std::string cmd = executable + " -i in.txt -model ASM";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__VALIDATION_OUT_FILE);
}

TEST_F(DriverTest, ValidationModelError) {
    // Input file does not need to exist here, just has to be specified
    std::string cmd = executable + " -i in.txt -o out.txt";
    SuppressOutputs(cmd);
    int rtn = std::system(cmd.c_str());
    EXPECT_EQ(rtn, DRVRERR__VALIDATION_MODEL);
}
