#include "Executable.h"
#include <iostream>

using namespace std;

Executable::Executable(unsigned long long int lastCompilation,
                       unsigned long long int line)
{
    this->line = line;
    this->lastCompilation = lastCompilation;
}

Executable::~Executable()
{

}

void Executable::Create()
{
    bool correct = true;
    string command = compiler + " -o " + name + ' ';

    for (unsigned int i = 0; i < files.size(); i++)
    {
        command += files[i].GetObjectFile() + ' ';
        if (files[i].FileIsOk() == false)
            correct = false;
    }
    command += ldflags;

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

