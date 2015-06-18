#include "StaticLibrary.h"
#include "parser.h"
#include <cstdlib>
#include <sys/stat.h>

using namespace std;

StaticLibrary::StaticLibrary(unsigned long long int lastCompilation)
{
    this->lastCompilation = lastCompilation;
}

StaticLibrary::~StaticLibrary()
{

}

void StaticLibrary::SetLdflags(std::string& unused)
{

}

void StaticLibrary::Create()
{
    string command = "ar rcs " + name + ' ';
    for (unsigned int i = 0; i < objectFiles.size(); i++)
        command += objectFiles[i];
    system(command.c_str());
}

