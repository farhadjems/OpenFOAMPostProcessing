#include "functions.h"

std::string cleanString(const std::string &input)
{
    std::string result{};

    for (char c : input)
    {
        if (c != ' ' && c != ',' && c != '.')
        {
            result.push_back(toupper(c));
        }
    }

    return result;
}

std::map<std::string, FileData> cleanInputData(char *inputData[], int size)
{
    if (size % 3 != 2)
    {
        throw -1;
    }

    std::map<std::string, FileData> result{};
    for (size_t i = 2; i < size; i++)
    {
        std::pair<std::string, FileData> newFile{};
        newFile.first = cleanString(inputData[i]);
        newFile.second.iData = cleanString(inputData[i + 1]);
        newFile.second.rData = cleanString(inputData[i + 2]);
        i += 2;
        result.insert(newFile);
    }

    return result;
}

std::map<std::string, int> headerData(std::string line)
{
    std::string word;
    std::stringstream ss;
    ss << line;
    int lineNumber = 0;
    std::map<std::string, int> result{};
    while (std::getline(ss, word, ','))
    {
        result.insert(std::pair<std::string, int>(cleanString(word), lineNumber));
        lineNumber++;
    }

    return result;
}

void checkInputData(std::map<std::string, FileData> inputData, std::map<std::string, int> headerLine)
{
    for (auto data : inputData)
    {
        if (headerLine.find(data.second.iData) == headerLine.end())
        {
            throw data.second.iData;
        }
        if (headerLine.find(data.second.rData) == headerLine.end())
        {
            throw data.second.rData;
        }
    }
}

std::vector<std::string> getDataFromLine(std::string line)
{
    std::string dataString{};
    std::stringstream ss{};
    std::vector<std::string> result;
    ss << line;
    while (std::getline(ss, dataString, ','))
    {
        result.push_back(dataString);
    }
    return result;
}