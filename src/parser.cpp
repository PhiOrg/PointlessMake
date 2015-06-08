#include "parser.h"

using namespace std;

vector<string> SplitString(string& command, char delimiter)
{
    vector<string> parameters;

    size_t found = command.find(delimiter);
    while (found != string::npos)
    {
        parameters.push_back(command.substr(0, found));
        command.erase(command.begin(), command.begin() + found + 1);
        found = command.find(delimiter);
    }

    if (command.size() > 0)
    {
        parameters.push_back(command);
        command = "";
    }

    return parameters;
}

