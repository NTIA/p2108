using ITS.ITU.PSeries;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace UnitTests
{
    public class TestData
    {
        static readonly string[] _heigthGainTestData;
        static readonly string[] _terrestrialStatisticalTestData;
        static readonly string[] _aeronauticalStatisticalTestData;

        public static IEnumerable<object[]> HeightGainTerminalCorrectionModelTestData
        {
            get
            {
                foreach (var line  in _heigthGainTestData)
                {
                    var parts = line.Split(',');

                    // parse data line
                    double f__ghz = Convert.ToDouble(parts[0]);
                    double h__meter = Convert.ToDouble(parts[1]);
                    double w_s__meter = Convert.ToDouble(parts[2]);
                    double R__meter = Convert.ToDouble(parts[3]);
                    P2108.ClutterType clutter_type = (P2108.ClutterType)Convert.ToInt32(parts[4]);
                    int rtn = Convert.ToInt32(parts[5]);
                    double A_h__db = Convert.ToDouble(parts[6]);

                    yield return new object[]
                    {
                        f__ghz,
                        h__meter,
                        w_s__meter,
                        R__meter,
                        clutter_type,
                        rtn,
                        A_h__db
                    };
                }
            }
        }

        public static IEnumerable<object[]> TerrestrialStatisticalModelTestData
        {
            get
            {
                foreach (var line in _terrestrialStatisticalTestData)
                {
                    var parts = line.Split(',');

                    // parse data line
                    double f__ghz = Convert.ToDouble(parts[0]);
                    double d__km = Convert.ToDouble(parts[1]);
                    double p = Convert.ToDouble(parts[2]);
                    int rtn = Convert.ToInt32(parts[3]);
                    double L_ctt__db = Convert.ToDouble(parts[4]);

                    yield return new object[]
                    {
                        f__ghz,
                        d__km,
                        p,
                        rtn,
                        L_ctt__db
                    };
                }
            }
        }

        public static IEnumerable<object[]> AeronauticalStatisticalModelTestData
        {
            get
            {
                foreach (var line in _aeronauticalStatisticalTestData)
                {
                    var parts = line.Split(',');

                    // parse data line
                    double f__ghz = Convert.ToDouble(parts[0]);
                    double theta__deg = Convert.ToDouble(parts[1]);
                    double p = Convert.ToDouble(parts[2]);
                    int rtn = Convert.ToInt32(parts[3]);
                    double L_ces__db = Convert.ToDouble(parts[4]);

                    yield return new object[]
                    {
                        f__ghz,
                        theta__deg,
                        p,
                        rtn,
                        L_ces__db
                    };
                }
            }
        }

        static TestData()
        {
            // load test data from file
            _heigthGainTestData = File.ReadAllLines("HeightGainTerminalCorrectionModelTestData.csv").Skip(1).ToArray();
            _terrestrialStatisticalTestData = File.ReadAllLines("TerrestrialStatisticalModelTestData.csv").Skip(1).ToArray();
            _aeronauticalStatisticalTestData = File.ReadAllLines("AeronauticalStatisticalModelTestData.csv").Skip(1).ToArray();
        }
    }
}
