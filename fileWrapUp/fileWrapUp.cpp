#include "functions.h"

int main(int argc, char *argv[])
{
    std::cout << "File Wrap Up Program\n";

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
    std::clog << "All entered files are open" << std::endl;

    std::string line{};
    std::ofstream outputFile(argv[1]);
    outputFile << clearOutputFileName(argv[1]) << std::endl;

    for (size_t i = 0; i < inputFiles.size(); i++)
    {
        if (i == 0) // creating header
        {
            getline(inputFiles[i], line, '\n');
            outputFile << "Sensor"
                       << "," << line << std::endl;
            line.erase();
        }
        else
        {
            getline(inputFiles[i], line, '\n');
            line.erase();
        }

        getline(inputFiles[i], line, '\n');
        outputFile << argv[i + 2] << "," << line << std::endl;
        line.erase();
    }

    // closing files
    for (auto &iFile : inputFiles)
    {
        iFile.close();
    }

    outputFile.close();

    std::cout << "File Wrap Up Program Executed Completely\n";
    return 0;
}