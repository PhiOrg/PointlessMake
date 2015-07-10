#include "SharedObject.h"
#include "parser.h"
#include <cstdlib>
#include <sys/stat.h>

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
    string command = compiler + " -shared -o " + name + ' ';
    for (unsigned int i = 0; i < files.size(); i++)
        command += files[i].GetObjectFile() + ' ';
    command += ldflags;

    system(command.c_str());
}

