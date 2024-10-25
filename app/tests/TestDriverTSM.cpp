#include "TestDriver.h"

/*******************************************************************************
 * Driver test fixture for the Terrestrial Statistical Model
 ******************************************************************************/
class TSMDriverTest: public DriverTest {
    protected:
        void SetUp() override {
            DriverTest::SetUp();
            tsm_params.model = P2108Model::TSM;
            tsm_params.out_file = params.out_file;
        }
        void TestTSM(const std::string &inputs, const int expected_rtn) {
            int tsm_rtn;
            tsm_rtn = RunDriverWithInputFile(inputs, tsm_params);
            EXPECT_EQ(tsm_rtn, expected_rtn);
        }

        std::string TSMInputs; /**< String to hold input file contents */
        DrvrParams tsm_params; /**< Default command line arguments */
};

TEST_F(TSMDriverTest, TestSuccess) {
    TSMInputs = "f__ghz,26.6\nd__km,15.8\np,45";
    TestTSM(TSMInputs, SUCCESS);
}

TEST_F(TSMDriverTest, TestParseError) {
    TSMInputs = "unknown_param,0.0";
    TestTSM(TSMInputs, DRVRERR__PARSE);
}

TEST_F(TSMDriverTest, TestParseFrequencyError) {
    TSMInputs = "f__ghz,invalid";
    TestTSM(TSMInputs, DRVRERR__PARSE_FREQ);
}

TEST_F(TSMDriverTest, TestParsePercentageError) {
    TSMInputs = "p,invalid";
    TestTSM(TSMInputs, DRVRERR__PARSE_PERCENTAGE);
}

TEST_F(TSMDriverTest, TestParsePathDistanceError) {
    TSMInputs = "d__km,invalid";
    TestTSM(TSMInputs, DRVRERR__PARSE_PATH_DIST);
}