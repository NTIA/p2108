#include "TestDriver.h"

std::string joinArguments(const std::vector<std::string> &args) {
    std::ostringstream oss;
    for (std::string arg : args) {
        oss << arg + " ";
    }
    return oss.str();
}

void appendDirectorySep(std::string &str) {
#ifdef _WIN32
    str += "\\";
#else
    str += "/";
#endif
}

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
        {"-i", "i_hgtcm.txt", "-o", "o_hgtcm.txt", "-model", "HGTCM"},
        {"-i", "i_tsm.txt", "-o", "o_tsm.txt", "-model", "TSM"},
        {"-i", "i_asm.txt", "-o", "o_asm.txt", "-model", "ASM"},
    };

    for (auto args : argSet) {
        command = executable + " " + joinArguments(args);
        std::cout << "Running command: " << command << std::endl;
        rtn = std::system(command.c_str());
        std::cout << "Return code: " << rtn << std::endl;
    }

    return SUCCESS;
}