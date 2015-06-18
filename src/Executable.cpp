#include "Executable.h"

Executable::Executable(unsigned long long int lastCompilation)
{
    this->lastCompilation = lastCompilation;
}

Executable::~Executable()
{

}

void Executable::SetLdflags(std::string& ldflags)
{
    this->ldflags = ldflags;
}

void Executable::Create()
{

}

