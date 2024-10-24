/** @file TestDriver.h
 * Primary header for command line driver tests.
 */
#pragma once

#include "Driver.h"
#include "TempTextFile.h"

#include <algorithm>      // for std::replace
#include <cstdio>         // for std::remove
#include <cstdlib>        // for std::system
#include <gtest/gtest.h>  // GoogleTest
#include <iostream>       // for std::cout, std::endl
#include <string>         // for std::string

class DriverTest: public ::testing::Test {
    protected:
        void SetUp() override {
            // Get the name of the executable to test
            executable = std::string(DRIVER_LOCATION);
            executable += "/" + std::string(DRIVER_NAME);
#ifdef _WIN32
            std::replace(executable.begin(), executable.end(), '/', '\\');
            executable += ".exe";
#else
            executable = "./" + executable;
#endif
        }

        void SuppressOutputs(std::string &cmd) {
#ifdef _WIN32
            cmd += " > nul";
#else
            cmd += " > /dev/null";
#endif
            cmd += " 2>&1";
        }

        std::string BuildCommand(
            const std::string &inFile,
            const std::string &model,
            const std::string &outFile,
            const bool suppressOutputs = true
        ) {
            // Construct command from parameters
            std::string command = executable;
            command += " -i " + inFile;
            command += " -model " + model;
            command += " -o " + outFile;
            if (suppressOutputs) {
                // Suppress outputs (cross-platform)
                SuppressOutputs(command);
            }
            // Return the full command string
            return command;
        }

        int RunDriver(
            const std::string &inFile,
            const std::string &model,
            const std::string &outFile
        ) {
            std::string cmd = BuildCommand(inFile, model, outFile);
            int rtn = std::system(cmd.c_str());
            return rtn;
        }

        int RunDriverWithInputFile(
            const std::string &inFileContents,
            const std::string &model,
            const std::string &outFile = "tmp_out.txt"
        ) {
            TempTextFile tempFile(inFileContents);
            std::string inFile = tempFile.getFileName();
            int rtn = RunDriver(inFile, model, outFile);
            // Cleanup: delete output file if it was created
            DeleteOutputFile(outFile);
            return rtn;
        }

        void DeleteOutputFile(const std::string &fileName) {
            bool fileExists = false;
#ifdef _WIN32
            fileExists = _access(fileName.c_str(), 0) == 0;
#else
            fileExists = access(fileName.c_str(), F_OK) == 0;
#endif
            if (fileExists) {
                if (std::remove(fileName.c_str()) != 0) {
                    std::perror("Error deleting output file");
                }
            }
        }

        // Holds the platform-dependent string to call the executable
        std::string executable;
};
