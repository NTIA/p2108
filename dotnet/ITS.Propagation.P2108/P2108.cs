﻿using System;
using System.Runtime.InteropServices;

namespace ITS.Propagation
{
    /// <summary>
    /// Recommendation ITU-R P.2108-0
    /// </summary>
    public static class P2108
    {
        private const string P2108_x86_DLL_NAME = "p2108_x86.dll";
        private const string P2108_x64_DLL_NAME = "p2108_x64.dll";

        #region 32-Bit P/Invoke Definitions

        [DllImport(P2108_x86_DLL_NAME, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "AeronauticalStatisticalModel")]
        private static extern int AeronauticalStatisticalModel_x86(double f__ghz, double theta__deg, double p, out double L_ces__db);

        [DllImport(P2108_x86_DLL_NAME, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "HeightGainTerminalCorrectionModel")]
        private static extern int HeightGainTerminalCorrectionModel_x86(double f__ghz, double h__meter, double w_s__meter, double R__meter, int clutter_type, out double A_h__db);

        [DllImport(P2108_x86_DLL_NAME, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "TerrestrialStatisticalModel")]
        private static extern int TerrestrialStatisticalModel_x86(double f__ghz, double d__km, double p, out double L_ctt__db);

        #endregion

        #region 64-Bit P/Invoke Definitions

        [DllImport(P2108_x64_DLL_NAME, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "AeronauticalStatisticalModel")]
        private static extern int AeronauticalStatisticalModel_x64(double f__ghz, double theta__deg, double p, out double L_ces__db);

        [DllImport(P2108_x64_DLL_NAME, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "HeightGainTerminalCorrectionModel")]
        private static extern int HeightGainTerminalCorrectionModel_x64(double f__ghz, double h__meter, double w_s__meter, double R__meter, int clutter_type, out double A_h__db);

        [DllImport(P2108_x64_DLL_NAME, CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "TerrestrialStatisticalModel")]
        private static extern int TerrestrialStatisticalModel_x64(double f__ghz, double d__km, double p, out double L_ctt__db);

        #endregion

        private delegate int AeronauticalStatisticalModelDelegate(double f__ghz, double theta__deg, double p, out double L_ces__db);
        private delegate int HeightGainTerminalCorrectionModelDelegate(double f__ghz, double h__meter, double w_s__meter, double R__meter, int clutter_type, out double A_h__db);
        private delegate int TerrestrialStatisticalModelDelegate(double f__ghz, double d__km, double p, out double L_ctt__db);

        private static AeronauticalStatisticalModelDelegate AeronauticalStatisticalModel_Invoke;
        private static HeightGainTerminalCorrectionModelDelegate HeightGainTerminalCorrectionModel_Invoke;
        private static TerrestrialStatisticalModelDelegate TerrestrialStatisticalModel_Invoke;

        static P2108()
        {
            // set the binding to the correct native DLL architecture

            if (Environment.Is64BitProcess)
            {
                AeronauticalStatisticalModel_Invoke = AeronauticalStatisticalModel_x64;
                HeightGainTerminalCorrectionModel_Invoke = HeightGainTerminalCorrectionModel_x64;
                TerrestrialStatisticalModel_Invoke = TerrestrialStatisticalModel_x64;
            }
            else
            {
                AeronauticalStatisticalModel_Invoke = AeronauticalStatisticalModel_x86;
                HeightGainTerminalCorrectionModel_Invoke = HeightGainTerminalCorrectionModel_x86;
                TerrestrialStatisticalModel_Invoke = TerrestrialStatisticalModel_x86;
            }
        }

        /// <summary>
        /// The Earth-space and aeronautical statistical clutter loss model as described in Section 3.3.
        /// </summary>
        /// <param name="f__ghz">Frequency, in GHz</param>
        /// <param name="theta__deg">Elevation angle, in degrees</param>
        /// <param name="p">Percentange of locations, in %</param>
        /// <param name="L_ces__db">Additional loss (clutter loss), in dB</param>
        /// <returns>Error code</returns>
        public static int AeronauticalStatisticalModel(double f__ghz, double theta__deg, double p, out double L_ces__db)
            => AeronauticalStatisticalModel_Invoke(f__ghz, theta__deg, p, out L_ces__db);

        /// <summary>
        /// Height gain terminal correction model as described in Section 3.1.
        /// </summary>
        /// <param name="f__ghz">Frequency, in GHz</param>
        /// <param name="h__meter">Antenna height, in meters</param>
        /// <param name="w_s__meter">Street width, in meters</param>
        /// <param name="R__meter">Representative clutter height, in meters</param>
        /// <param name="clutter_type">Clutter type</param>
        /// <param name="A_h__db">Additional loss (clutter loss), in dB</param>
        /// <returns>Error code</returns>
        public static int HeightGainTerminalCorrectionModel(double f__ghz, double h__meter, double w_s__meter, double R__meter, int clutter_type, out double A_h__db)
            => HeightGainTerminalCorrectionModel_Invoke(f__ghz, h__meter, w_s__meter, R__meter, clutter_type, out A_h__db);

        /// <summary>
        /// Statistical clutter loss model for terrestrial paths as described in Section 3.2.
        /// </summary>
        /// <param name="f__ghz">Frequency, in GHz</param>
        /// <param name="d__km">Path distance, in km</param>
        /// <param name="p">Percentange of locations, in %</param>
        /// <param name="L_ctt__db">Additional loss (clutter loss), in dB</param>
        /// <returns>Error code</returns>
        public static int TerrestrialStatisticalModel(double f__ghz, double d__km, double p, out double L_ctt__db)
            => TerrestrialStatisticalModel_Invoke(f__ghz, d__km, p, out L_ctt__db);
    }
}
