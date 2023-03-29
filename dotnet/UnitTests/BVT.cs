using ITS.ITU.PSeries;
using Xunit;

namespace UnitTests
{
    public class BVT
    {
        const double EPSILON = 0.1;

        /// <summary>
        /// Tests for Sec 3.1 Height Gain Terminal Correction clutter model
        /// </summary>
        /// <param name="f__ghz">Frequency, in GHz</param>
        /// <param name="h__meter">Antenna height, in meters</param>
        /// <param name="w_s__meter">Street width, in meters</param>
        /// <param name="R__meter">Representative clutter height, in meters</param>
        /// <param name="clutter_type">Clutter type</param>
        /// <param name="rtn">Return code</param>
        /// <param name="A_h__db">Additional loss (clutter loss), in dB</param>
        [Theory]
        [MemberData(nameof(TestData.HeightGainTerminalCorrectionModelTestData), MemberType = typeof(TestData))]
        public void HeightGainTerminalCorrectionModelTest(double f__ghz,
            double h__meter, double w_s__meter, double R__meter,
            P2108.ClutterType clutter_type, int rtn, double A_h__db)
        {
            var r = P2108.HeightGainTerminalCorrectionModel(f__ghz, h__meter, w_s__meter, R__meter, clutter_type, out double A__db);

            Assert.Equal(rtn, r);
            Assert.Equal(A_h__db, A__db, EPSILON);
        }

        /// <summary>
        /// Tests for Sec 3.2 Terrestrial Statistical clutter model
        /// </summary><param name="f__ghz">Frequency, in GHz</param>
        /// <param name="d__km">Path distance, in km</param>
        /// <param name="p">Percentange of locations, in %</param>
        /// <param name="rtn">Return code</param>
        /// <param name="L_ctt__db">Additional loss (clutter loss), in dB</param>
        [Theory]
        [MemberData(nameof(TestData.TerrestrialStatisticalModelTestData), MemberType = typeof(TestData))]
        public void TerrestrialStatisticalModelTest(double f__ghz,
            double d__km, double p, int rtn, double L_ctt__db)
        {
            var r = P2108.TerrestrialStatisticalModel(f__ghz, d__km, p, out double L__db);

            Assert.Equal(rtn, r);
            Assert.Equal(L_ctt__db, L__db, EPSILON);
        }

        /// <summary>
        /// Tests for Sec 3.3 Aeronautical Statistical clutter model
        /// </summary>
        /// <param name="f__ghz">Frequency, in GHz</param>
        /// <param name="theta__deg">Elevation angle, in degrees</param>
        /// <param name="p">Percentange of locations, in %</param>
        /// <param name="rtn">Return code</param>
        /// <param name="L_ces__db">Additional loss (clutter loss), in dB</param>
        [Theory]
        [MemberData(nameof(TestData.AeronauticalStatisticalModelTestData), MemberType = typeof(TestData))]
        public void AeronauticalStatisticalModelTest(double f__ghz,
            double theta__deg, double p, int rtn, double L_ces__db)
        {
            var r = P2108.AeronauticalStatisticalModel(f__ghz, theta__deg, p, out double L__db);

            Assert.Equal(rtn, r);
            Assert.Equal(L_ces__db, L__db, EPSILON);
        }
    }
}
