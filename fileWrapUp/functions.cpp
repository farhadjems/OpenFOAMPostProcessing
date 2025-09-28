#include "functions.h"

std::string clearOutputFileName(char *argv)
{
    std::stringstream sName(argv);
    std::string name{};
    getline(sName, name, '.');

    return name;
}