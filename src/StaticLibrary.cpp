#include "StaticLibrary.h"
#include "parser.h"

#include <cstdlib>
#include <sys/stat.h>
#include <iostream>

using namespace std;

StaticLibrary::StaticLibrary(unsigned long long int lastCompilation,
                             unsigned long long int line)
{
    this->line = line;
    this->lastCompilation = lastCompilation;
}

StaticLibrary::~StaticLibrary()
{

}

void StaticLibrary::Create()
{
    bool correct = true;
    string command = "ar rcs " + name + ' ';

    for (unsigned int i = 0; i < files.size(); i++)
    {
        command += files[i].GetObjectFile() + ' ';
        if (files[i].FileIsOk() == false)
            correct = false;
    }

    if (correct)
    {
        system(command.c_str());
        SetColor(FG_green);
        cout << command << "\n";
        SetColor(FG_white);
    }
    else
    {
        SetColor(FG_red);
        cout << command << "\n";
        SetColor(FG_white);
    }
}

