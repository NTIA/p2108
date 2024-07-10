#include "TestUtils.h"

#include <stdexcept>

TEST(InverseCCDFTest, TestInverseCCDF) {
    EXPECT_DOUBLE_EQ(
        InverseComplementaryCumulativeDistribution(0.01), 2.3267853325589658
    );
    EXPECT_DOUBLE_EQ(
        InverseComplementaryCumulativeDistribution(0.49), 0.024998347218995187
    );
    EXPECT_DOUBLE_EQ(
        InverseComplementaryCumulativeDistribution(0.51), -0.024998347218995187
    );
    EXPECT_DOUBLE_EQ(
        InverseComplementaryCumulativeDistribution(0.99), -2.3267853325589658
    );
}

TEST(InverseCCDFTest, TestInverseCCDFInputInvalid) {
    EXPECT_THROW(
        InverseComplementaryCumulativeDistribution(-1.0), std::out_of_range
    );
    EXPECT_THROW(
        InverseComplementaryCumulativeDistribution(0.0), std::out_of_range
    );
    EXPECT_THROW(
        InverseComplementaryCumulativeDistribution(1.0), std::out_of_range
    );
    EXPECT_THROW(
        InverseComplementaryCumulativeDistribution(1.1), std::out_of_range
    );
}