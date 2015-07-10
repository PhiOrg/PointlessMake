#include "OutputType.h"
#include "parser.h"
#include <cstdlib>
#include <sys/stat.h>
#include <iostream>

using namespace std;

void OutputType::SetName(string& name)
{
    this->name = "bin/" + name;
}

void OutputType::SetCompiler(string& compiler)
{
    this->compiler = compiler;
}

void OutputType::AddCflags(string& cflags)
{
    this->cflags += cflags + ' ';
}

void OutputType::AddFiles(string& file)
{
    files.push_back(File(file));
}

void OutputType::AddLdflags(string& ldflags)
{
    this->ldflags += ldflags + ' ';
}

bool OutputType::CompileFiles()
{
    bool result = true;
    for (unsigned int i = 0; i < files.size(); i++)
    {
        if (!files[i].FileIsOk())
        {
            result = false;
            cout << "pointlessmake.pm: " << line << ": error: ";
            cout << files[i].GetError() << "\n";
            continue;
        }

        if (files[i].CheckIfObjectFileExists())
        {
            string file = files[i].GetFile();
            if (GetLastModification(file) < lastCompilation)
                continue;
        }

        string command = compiler + ' ' + cflags + " -c " + files[i].GetFile();
        command += " -o " + files[i].GetObjectFile();
        system(command.c_str());
    }

    return result;
}

unsigned long long int OutputType::GetLastModification(std::string& file)
{
    struct stat st;
    if (stat(file.c_str(), &st))
    {
        return 0;
    }
    else
    {
        return st.st_mtim.tv_sec;
    }

    return 0;
}

