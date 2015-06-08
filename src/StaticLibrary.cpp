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

void StaticLibrary::SetName(string& name)
{
    this->name = name;
}

void StaticLibrary::SetCompiler(string& compiler)
{
    this->compiler = compiler;
}

void StaticLibrary::SetCflags(string& cflags)
{
    this->cflags = cflags;
}

void StaticLibrary::SetFiles(string& files)
{
    RemovePointlessSpaces(files);
    this->files = SplitString(files);
}

void StaticLibrary::CompileFiles()
{
    for (unsigned int i = 0; i < files.size(); i++)
    {
        if (GetLastModification(files[i]) < lastCompilation)
            continue;
        string objectFile = files[i];
        objectFile[0] = 'b';
        objectFile[1] = 'i';
        objectFile[2] = 'n';
        int j = objectFile.size() - 1;
        while (objectFile[j] != '.')
        {
            objectFile.erase(j);
            j--;
        }
        objectFile.push_back('o');
        objectFiles.push_back(objectFile);

        string command = compiler + ' ' + cflags + " -c " + files[i] + " -o ";
        command += objectFile;
        system(command.c_str());
    }

}

unsigned long long int StaticLibrary::GetLastModification(std::string& file)
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

void StaticLibrary::RemovePointlessSpaces(string& str)
{
    while (str[0] == ' ')
        str.erase(0);
    for (int i = 0; i < str.size() - 1; i++)
        if (str[i] == ' ' && str[i + 1] == ' ')
        {
            str.erase(i);
            i--;
        }
}

void StaticLibrary::Create()
{
    string command = "ar rcs " + nume ' ';
    for (unsigned int i = 0; i < objectFiles.size(); i++)
        command += objectFiles[i];
    system(command.c_str());
}

