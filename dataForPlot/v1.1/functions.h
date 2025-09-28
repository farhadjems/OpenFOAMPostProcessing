#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <set>
#include <map>

struct FileData
{
    std::string iData; // independent data
    std::string rData; // relative data
};

std::string cleanString(const std::string &input);

std::map<std::string, FileData> cleanInputData(char *inputData[], int size);

std::map<std::string, int> headerData(std::string line);

void checkInputData(std::map<std::string, FileData> inputData, std::map<std::string, int> headerLine);

std::vector<std::string> getDataFromLine(std::string line);

#endif
