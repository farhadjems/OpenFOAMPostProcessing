#include "functions.h"

int main(int argc, char *argv[])
{
    std::cout << "Concat CSV Program\n";

    std::vector<std::ifstream> inputFiles{};
    for (size_t i = 2; i < argc; i++)
    {
        inputFiles.push_back(std::ifstream(argv[i]));
        if (!inputFiles[i - 2].is_open())
        {
            std::cerr << "could not open file: " << argv[i] << ", exiting..." << std::endl;
            return 1;
        }
    }

    std::string line{};
    std::ofstream outputFile(argv[1]);

    for (auto &iFile : inputFiles)
    {
        while (getline(iFile, line, '\n'))
        {
            outputFile << line << std::endl;
        }
        outputFile << std::endl;
    }

    std::cout << "Concat CSV Program Executed Completely\n";
    return 0;
}