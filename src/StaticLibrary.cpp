#include "StaticLibrary.h"
#include "parser.h"
#include <cstdlib>
#include <sys/stat.h>

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
    string command = "ar rcs " + name + ' ';
    for (unsigned int i = 0; i < files.size(); i++)
        command += files[i].GetObjectFile() + ' ';
    system(command.c_str());
}

