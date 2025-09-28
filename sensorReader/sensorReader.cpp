#include "functions.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "bad input, exiting..." << std::endl;
    }

    std::vector<std::string> inputNames = inputFiles(argc, argv)
}