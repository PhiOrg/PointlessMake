#include "SharedObject.h"
#include "parser.h"
#include <cstdlib>
#include <sys/stat.h>

using namespace std;

SharedObject::SharedObject(unsigned long long int lastCompilation)
{
    this->lastCompilation = lastCompilation;
    this->cflags = "-fPIC";
}

SharedObject::~SharedObject()
{

}

void SharedObject::SetLdflags(std::string& unused)
{

}

void SharedObject::Create()
{
    string command = compiler + " -shared -o " + name + ' ';
    for (unsigned int i = 0; i < objectFiles.size(); i++)
        command += objectFiles[i];
    system(command.c_str());
}

