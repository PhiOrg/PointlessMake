#include "SharedObject.h"
#include "parser.h"
#include <cstdlib>
#include <sys/stat.h>

using namespace std;

SharedObject::SharedObject(unsigned long long int lastCompilation)
{
    this->lastCompilation = lastCompilation;
}

SharedObject::~SharedObject()
{

}

void SharedObject::SetName(string& name)
{
    this->name = name;
}

void SharedObject::SetCompiler(string& compiler)
{
    this->compiler = compiler;
}

void SharedObject::SetCflags(string& cflags)
{
    this->cflags = cflags;
}

void SharedObject::SetFiles(string& files)
{
    RemovePointlessSpaces(files);
    this->files = SplitString(files);
}

void SharedObject::CompileFiles()
{
    cflags += " -fPIC";
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

unsigned long long int SharedObject::GetLastModification(std::string& file)
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

void SharedObject::RemovePointlessSpaces(string& str)
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

void SharedObject::Create()
{
    string command = compiler + " -shared -o " + name + ' ';
    for (unsigned int i = 0; i < objectFiles.size(); i++)
        command += objectFiles[i];
    system(command.c_str());
}

