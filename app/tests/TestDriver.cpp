/** @file TestDriver.cpp
 * The main entrypoint for the TestDriver executable
 */
#include "TestDriver.h"

int main() {
    // Driver executable needs to be in the same directory as this executable
    std::string executable = std::string(DRIVER_NAME);

#ifdef _WIN32
    executable += ".exe";
#endif

    std::string command;
    int rtn;

    // Input files must exist in the directory of this executable
    std::vector<std::vector<std::string>> argSet = {
        {"-i", "i_hgtcm.txt", "-o", "o_hgtcm.txt", "-model", "HGTCM", "0"},
        {"-i", "i_tsm.txt", "-o", "o_tsm.txt", "-model", "TSM", "0"},
        {"-i", "i_asm.txt", "-o", "o_asm.txt", "-model", "ASM", "0"},
    };

    int expected_rtn;

    for (auto args : argSet) {
        expected_rtn = ParseInteger(args.back());
        args.pop_back();
        command = executable + " " + joinArguments(args);
        std::cout << "Running command: " << command << std::endl;
        rtn = std::system(command.c_str());
        if (rtn != expected_rtn) {
            std::cout << "[FAILURE] Returned " << rtn << ", expected "
                      << expected_rtn << std::endl;
        } else {
            std::cout << "[SUCCESS] Returned " << rtn << std::endl;
        }
        std::cout << std::endl;
    }

    return SUCCESS;
}