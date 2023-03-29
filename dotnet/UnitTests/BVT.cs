﻿using ITS.ITU.PSeries;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xunit;
using static ITS.ITU.PSeries.P2108;

namespace UnitTests
{
    public class BVT
    {
        const double EPSILON = 0.1;

        [Theory]
        [MemberData(nameof(TestData.HeightGainTerminalCorrectionModelTestData), MemberType = typeof(TestData))]
        public void HeightGainTerminalCorrectionModelTest(double f__ghz,
            double h__meter, double w_s__meter, double R__meter,
            ClutterType clutter_type, int rtn, double A_h__db)
        {
            var r = P2108.HeightGainTerminalCorrectionModel(f__ghz, h__meter, w_s__meter, R__meter, clutter_type, out double A__db);

            Assert.Equal(rtn, r);
            Assert.Equal(A_h__db, A__db, EPSILON);
        }
    }
}
