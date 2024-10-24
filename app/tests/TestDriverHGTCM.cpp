#include "TestDriver.h"

class HGTCMDriverTest: public DriverTest {
    protected:
        void SetUp() override {
            DriverTest::SetUp();
            hgtcm_params.model = P2108Model::HGTCM;
            hgtcm_params.out_file = params.out_file;
        }
        void TestHGTCM(const std::string &inputs, const int expected_rtn) {
            int hgtcm_rtn;
            hgtcm_rtn = RunDriverWithInputFile(inputs, hgtcm_params);
            EXPECT_EQ(hgtcm_rtn, expected_rtn);
        }

        std::string HGTCMInputs;
        DrvrParams hgtcm_params;
};

TEST_F(HGTCMDriverTest, TestSuccess) {
    HGTCMInputs
        = "f__ghz,1.5\nh__meter,2\nw_s__meter,27\nR__meter,15\nclutter_type,4";
    TestHGTCM(HGTCMInputs, SUCCESS);
}

TEST_F(HGTCMDriverTest, TestParseError) {
    HGTCMInputs = "unknown_param,0.0";
    TestHGTCM(HGTCMInputs, DRVRERR__PARSE);
}

TEST_F(HGTCMDriverTest, TestParseFrequencyError) {
    HGTCMInputs = "f__ghz,invalid";
    TestHGTCM(HGTCMInputs, DRVRERR__PARSE_FREQ);
}

TEST_F(HGTCMDriverTest, TestParseHeightError) {
    HGTCMInputs = "h__meter,invalid";
    TestHGTCM(HGTCMInputs, DRVRERR__PARSE_HEIGHT);
}

TEST_F(HGTCMDriverTest, TestParseStreetWidthError) {
    HGTCMInputs = "w_s__meter,invalid";
    TestHGTCM(HGTCMInputs, DRVRERR__PARSE_STREET_WIDTH);
}

TEST_F(HGTCMDriverTest, TestParseReprHeightError) {
    HGTCMInputs = "R__meter,invalid";
    TestHGTCM(HGTCMInputs, DRVRERR__PARSE_REPR_HEIGHT);
}

TEST_F(HGTCMDriverTest, TestParseClutterTypeError) {
    HGTCMInputs = "clutter_type,invalid";
    TestHGTCM(HGTCMInputs, DRVRERR__PARSE_CLUTTER_TYPE);
}