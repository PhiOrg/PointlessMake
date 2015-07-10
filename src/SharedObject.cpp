#include "SharedObject.h"
#include <iostream>

using namespace std;

SharedObject::SharedObject(unsigned long long int lastCompilation,
                           unsigned long long int line)
{
    this->line = line;
    this->lastCompilation = lastCompilation;
}

SharedObject::~SharedObject()
{

}

void SharedObject::Create()
{
    bool correct = true;
    string command = compiler + " -shared -o " + name + ' ';

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

