#include "TestDriver.h"

/*******************************************************************************
 * Driver test fixture for the Aeronautical Statistical Model
 ******************************************************************************/
class ASMDriverTest: public DriverTest {
    protected:
        void SetUp() override {
            DriverTest::SetUp();
            asm_params.model = P2108Model::ASM;
            asm_params.out_file = params.out_file;
        }
        void TestASM(const std::string &inputs, const int expected_rtn) {
            int asm_rtn;
            asm_rtn = RunDriverWithInputFile(inputs, asm_params);
            EXPECT_EQ(asm_rtn, expected_rtn);
        }

        std::string ASMInputs; /**< String to hold input file contents */
        DrvrParams asm_params; /**< Default command line arguments */
};

TEST_F(ASMDriverTest, TestSuccess) {
    ASMInputs = "f__ghz,10\ntheta__deg,10.5\np,45";
    TestASM(ASMInputs, SUCCESS);
}

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