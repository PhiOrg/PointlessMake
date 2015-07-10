#include "Executable.h"

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
    string command = compiler + " -o " + name + ' ';
    for (unsigned int i = 0; i < files.size(); i++)
        command += files[i].GetObjectFile() + ' ';
    command += ldflags;

    system(command.c_str());
}

