#include "TestDriver.h"

// Test fixture for the unit tests
class ASMDriverTest: public DriverTest {
    protected:
        void
            TestASM(const std::string &inFileContents, const int expected_rtn) {
            int asm_rtn;
            asm_rtn = RunDriverWithInputFile(inFileContents, "ASM");
            EXPECT_EQ(asm_rtn, expected_rtn);
        }

        std::string ASMInputs;
};

TEST_F(ASMDriverTest, TestParseError) {
    ASMInputs = "unknown_param,0.0";
    TestASM(ASMInputs, DRVRERR__PARSE);
}

TEST_F(ASMDriverTest, TestParseFrequencyError) {
    ASMInputs = "f__ghz,invalid";
    TestASM(ASMInputs, DRVRERR__PARSE_FREQ);
}

TEST_F(ASMDriverTest, TestParseThetaError) {
    ASMInputs = "theta__deg,invalid";
    TestASM(ASMInputs, DRVRERR__PARSE_THETA);
}

TEST_F(ASMDriverTest, TestParsePercentageError) {
    ASMInputs = "p,invalid";
    TestASM(ASMInputs, DRVRERR__PARSE_PERCENTAGE);
}