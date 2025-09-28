#include "functions.h"

#define Version 1.0

int main(int argc, char *argv[])
{
    std::cout << "Column Selector Program\n";

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "could not open the file: " << argv[1] << ", exiting..." << std::endl;
        return 1;
    }
    std::clog << "file: " << argv[1] << " is open" << std::endl;

    // desired columns
    std::vector<std::string> inputColumns{};
    for (size_t i = 2; i < argc; i++)
    {
        inputColumns.push_back(argv[i]);
    }

#ifdef DEBUG // checking whether input info is correct
    std::cout << "------------------------------- DEBUG MODE ------------------------------------\n";
    std::cout << "desired headers:\n";
    for (auto &iColumn : inputColumns)
    {
        std::cout << iColumn << std::endl;
    }
    std::cout << "------------------------------- DEBUG MODE ------------------------------------\n";
#endif

    // output file
    std::ofstream outputFile("modified-" + static_cast<std::string>(argv[1]));

    std::map<int, std::string> fileColumns{}; // input file columns header
    std::string line{};                       // this object reads lines
    std::string word{};                       // this object reads words in line object

    // first line is the name of file
    getline(inputFile, line, '\n');
    outputFile << line << std::endl;

    // reading header - second line of input file is headers
    {
        getline(inputFile, line, '\n');
        std::stringstream sline{line};
        int columnNumber = 0;
        while (getline(sline, word, ','))
        {
            fileColumns.insert(std::pair<int, std::string>(columnNumber, word));
            columnNumber++;
            word.erase();
        }
    }

#ifdef DEBUG // checking whether if columns are detected correctly
    std::cout << "------------------------------- DEBUG MODE ------------------------------------\n";
    std::cout << "input file has below headers:\n";
    for (auto &fColumn : fileColumns)
    {
        std::cout << std::setw(5) << std::left << fColumn.first << std::setw(50) << fColumn.second << std::endl;
    }
    std::cout << "------------------------------- DEBUG MODE ------------------------------------\n";
#endif

    // checking input columns are correct
    std::map<int, std::string> selectedColumns{}; // selecting columns in input file
    for (auto &iColumn : inputColumns)
    {
        bool isTargetFound = false;
        for (auto &fColumn : fileColumns)
        {
            if (iColumn == fColumn.second)
            {
                selectedColumns.insert(fColumn);
                isTargetFound = true;
                break;
            }
        }
        if (!isTargetFound)
        {
            std::cerr << "could not find column with header: " << iColumn << ", exiting..." << std::endl;
            return 1;
        }
    }

#ifdef DEBUG
    std::cout << "------------------------------- DEBUG MODE ------------------------------------\n";
    for (auto &sColumn : selectedColumns)
    {
        std::cout << "header: " << sColumn.second << " is found and selected\n";
    }
#endif

    // writing header
    for (auto &sColumn : selectedColumns)
    {
        outputFile << sColumn.second << ",";
    }
    outputFile << std::endl;

    // writing data
    while (getline(inputFile, line, '\n'))
    {
        std::stringstream sline{line};
        int columnNumber = 0;
        while (getline(sline, word, ','))
        {
            for (auto &sColumn : selectedColumns)
            {
                if (columnNumber == sColumn.first)
                {
                    outputFile << word << ",";
                }
            }
            columnNumber++;
            word.erase();
        }
        outputFile << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Column Selector Program Executed Completely\n";
    return 0;
}