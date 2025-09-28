#include "functions.h"

// #define DEBUG
#define VERSION 1.0

int main(int argc, char *argv[])
{
    // this map stores the input data from user - includes the name of file, and a pair of cloumn name
    std::map<std::string, FileData> inputData{};
    try
    {
        // checking if number of inputs are OK
        inputData = cleanInputData(argv, argc);
    }
    catch (const int data)
    {
        std::cerr << "number of input data is not sufficient, exiting..." << std::endl;
    }

    // input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        // cheking if its open or not!
        std::cerr << "could not open input file, exiting..." << std::endl;
        return 1;
    }
    std::cout << "file with the name \"" << argv[1] << "\" is open" << std::endl;

    // this variable helps to read lines
    std::string line{};
    // reading first line - it is needed to extract column names
    std::getline(inputFile, line);

    // this map stores name and number of column
    std::map<std::string, int> headerLine{};
    headerLine = headerData(line);

    try
    {
        checkInputData(inputData, headerLine);
    }
    catch (const std::string columnName)
    {
        std::cerr << "column with name \"" << columnName << "\" does not exist in the input file" << std::endl;
        inputFile.close();
        return 1;
    }

    // creating output Files
    std::map<std::string, std::ofstream> outputFiles{};
    for (std::pair<std::string, FileData> file : inputData)
    {
        std::ofstream newOutputFile(file.first + "-" + static_cast<std::string>(argv[1]));
        // std::pair<std::string, std::ofstream> newFile(file.first, newOutputFile);
        // outputFiles.insert(std::pair<std::string, std::ofstream>(file.first, newOutputFile));
        outputFiles[file.first] = std::ofstream(file.first + "-" + static_cast<std::string>(argv[1]));

#ifdef DEBUG
        std::cout << "file with the name \"" << file.first << "\" is created" << std::endl;
#endif
    }

    // Extracting data from input file and printing into output files
    std::vector<double> dataLine;

    while (std::getline(inputFile, line))
    {
        dataLine = getDataFromLine(line);
        for (auto file : inputData)
        {
            int rDataColumnNumber = headerLine.find(file.second.iData)->second; // first column number
            int iDataColumnNumber = headerLine.find(file.second.rData)->second; // second column number

            outputFiles[file.first] << std::setw(20) << std::left << dataLine[rDataColumnNumber]
                                    << std::setw(20) << std::left << dataLine[iDataColumnNumber]
                                    << std::endl;
        }
    }

#ifdef DEBUG
    std::cout << "creating files are finished" << std::endl;
#endif

    // closing input file
    inputFile.close();

#ifdef DEBUG
    std::cout << "input file is closed" << std::endl;
#endif

    for (std::map<std::string, std::ofstream>::iterator i = outputFiles.begin(); i != outputFiles.end(); ++i)
    {
        i->second.close();
#ifdef DEBUG
        std::cout << "output file with the name \"" << i->first << "\" is closed" << std::endl;
#endif
    }

#ifdef DEBUG
    std::cout << "End" << std::endl;
#endif

    std::cout << "Operation on file with the name \"" << argv[1] << "\" has done successfully" << std::endl;
    return 0;
}
