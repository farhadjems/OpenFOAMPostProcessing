#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

int main(int argc, char *argv[])
{

    int lineCounter = 10;

    std::cout << "number of selected lines is: " << lineCounter << '\n';

    for (int i = 1; i < argc; i++)
    {
        std::ifstream inputFile(argv[i]);

        if (!inputFile.is_open())
        {
            std::cerr << " could not open input file: " << argv[i] << ", exiting" << std::endl;
            return 1;
        }
        else
        {
            std::cout << "input file opened successfully \n";
        }

        std::ofstream outputFile("modified-" + static_cast<std::string>(argv[i]));

        std::string firstLine = "";
        getline(inputFile, firstLine, '\n');
        outputFile << firstLine << '\n';

        int h = 0;
        while (!inputFile.eof())
        {
            std::string line;
            getline(inputFile, line, '\n');
            if (h % lineCounter == 0.0)
            {
                outputFile << line << '\n';
            }
            ++h;
        }

        inputFile.close();
        outputFile.close();
    }

        std::cout << "operation executed successfully!\n";

    return 0;
}