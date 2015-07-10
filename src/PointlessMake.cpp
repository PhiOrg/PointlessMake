#include "PointlessMake.h"
#include "parser.h"

#include <fstream>
#include <iostream>
#include <new>
#include <algorithm>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

PointlessMake::PointlessMake()
{
    string configFile = PointlessMakeFile;
    if (!CheckIfFileExists(configFile))
    {
        cout << "ERROR: " << configFile << " doesn't exists\n";
        error = true;
    }
    else
    {
        existsBin = CheckIfDirExists("bin/");
        existsSrc = CheckIfDirExists("src/");

        if (existsSrc == 1)
        {
            if (existsBin == 1)
            {
                string path = "bin/.config.pm";
                if (CheckIfFileExists(path))
                {
                    ifstream f(path.c_str());
                    f >> seconds;
                    f.close();
                }
            }
            else
                if (existsBin == 0)
                {
                    system("mkdir bin");
                }
                else
                {
                    error = true;
                    cout << "ERROR: permission denied to the bin directory\n";
                }
        }
        else
        {
            if (existsSrc == 0)
                cout << "ERROR: the src directory doesn't exist\n";
            else
                cout << "ERROR: permission denied to the src directory\n";
            error = true;
        }
    }
}

PointlessMake::~PointlessMake()
{
    for (unsigned int i = 0; i < sharedObjects.size(); i++)
        delete sharedObjects[i];
    for (unsigned int i = 0; i < staticLibraries.size(); i++)
        delete staticLibraries[i];
    for (unsigned int i = 0; i < executables.size(); i++)
        delete executables[i];

    SetCurrentTimeInConfigFile();
}

short int PointlessMake::CheckIfDirExists(string path)
{
    short int existsDir;
    struct stat info;
    if (stat(path.c_str(), &info))
        existsDir = 0;
    else
        existsDir = 1;

    if (existsDir == 1)
        if (access(path.c_str(), R_OK && W_OK))
            existsDir = 2;

    return existsDir;
}

void PointlessMake::RemoveTabs(string& str)
{
    for (unsigned int i = 0; i < str.size(); i++)
        if (str[i] == '\t')
        {
            str.erase(i);
            i--;
        }
}

void PointlessMake::RemovePointlessSpaces(string& str)
{
    int i = 0;
    while (str.size() != 0)
        if (str[i] == ' ')
            str.erase(str.begin());
        else
            break;

    i = str.size() - 1;
    while (str.size() != 0)
        if (str[i] == ' ')
        {
            str.erase(i);
            i--;
        }
        else
            break;

    for (unsigned int i = 0; i < str.size() - 1; i++)
        if (str[i] == ' ' && str[i + 1] == ' ')
        {
            str.erase(i);
            i--;
        }
}

bool PointlessMake::CheckIfFileIsCorrect()
{
    if (error)
        return false;

    string configFile = PointlessMakeFile;
    string line;
    ifstream input(configFile.c_str());
    while (getline(input, line))
    {
        lines++;
        RemoveTabs(line);
        RemovePointlessSpaces(line);

        if (line == "")
            continue;

        vector<string> words = SplitString(line);
        if (!CheckIfKeywordExists(words[0]))
        {
            error = true;
            cout << "pointlessmake.pm: " << lines;
            cout << ": error: the keyword doesn't exist\n";
            continue;
        }

        if (!CheckNumberOfKeywords(words))
        {
            error = true;
            cout << "pointlessmake.pm: " << lines;
            cout << ": error: too many keywords on a line\n";
        }

        ProcessingKeyword(words);
    }

    return !error;
}

bool PointlessMake::CheckNumberOfKeywords(vector<string>& words)
{
    int number = 0;
    for (unsigned int i = 1; i < words.size(); i++)
        if (CheckIfKeywordExists(words[i]))
            number++;

    if (number == 0)
        return true;
    return false;
}

bool PointlessMake::CheckIfKeywordExists(string& keyword)
{
    static vector<string> keywords = { "compiler",
                                       "cflags",
                                       "ldflags",
                                       "files",
                                       "SharedObject",
                                       "StaticLibrary",
                                       "Executable" };

    auto i = find(keywords.begin(), keywords.end(), keyword);
    if (i == keywords.end())
        return false;

    return true;
}

void PointlessMake::ProcessingKeyword(vector<string>& words)
{
    if (words[0] == "SharedObject")
    {
        type = 1;
        compiler = false;
        object = new SharedObject(seconds, lines);
        sharedObjects.push_back((SharedObject*)object);
        if (words.size() != 2)
        {
            error = true;
            if (words.size() == 1)
                cout << "pointlessmake.pm: " << lines << ": error: too few arguments\n";
            else
                cout << "pointlessmake.pm: " << lines << ": error: too many arguments\n";
        }
        else
            object->SetName(words[1]);
        return;
    }

    if (words[0] == "StaticLibrary")
    {
        type = 2;
        compiler = false;
        object = new StaticLibrary(seconds, lines);
        staticLibraries.push_back((StaticLibrary*)object);
        if (words.size() != 2)
        {
            error = true;
            if (words.size() == 1)
                cout << "pointlessmake.pm: " << lines << ": error: too few arguments\n";
            else
                cout << "pointlessmake.pm: " << lines << ": error: too many arguments\n";
        }
        else
            object->SetName(words[1]);
        return;
    }

    if (words[0] == "Executable")
    {
        type = 3;
        compiler = false;
        object = new Executable(seconds, lines);
        executables.push_back((Executable*)object);
        if (words.size() != 2)
        {
            error = true;
            if (words.size() == 1)
                cout << "pointlessmake.pm: " << lines << ": error: too few arguments\n";
            else
                cout << "pointlessmake.pm: " << lines << ": error: too many arguments\n";
        }
        else
            object->SetName(words[1]);
        return;
    }

    if (words[0] == "cflags")
    {
        if (words.size() == 1)
        {
            cout << "pointlessmake.pm: " << lines << ": error: to few arguments\n";
            return;
        }

        for (unsigned int i = 1; i < words.size(); i++)
            object->AddCflags(words[i]);
        return;
    }

    if (words[0] == "ldflags")
    {
        if (type == 2)
        {
            cout << "pointlessmake.pm: " << lines << ": error: ";
            cout << " the static library doens't have ldflags\n";
            error = true;

            return;
        }

        if (words.size() == 1)
        {
            cout << "pointlessmake.pm: " << lines << ": error: to few arguments\n";
            return;
        }

        for (unsigned int i = 1; i < words.size(); i++)
            object->AddLdflags(words[i]);
        return;
    }

    if (words[0] == "compiler")
    {
        if (compiler)
        {
            cout << "pointlessmake.pm: " << lines;
            cout << ": error: the compiler keyword may be used just once ";
            cout << "within an output type\n";
            error = true;

            return;
        }

        compiler = true;

        if (words.size() != 2)
        {
            error = true;
            if (words.size() == 1)
                cout << "pointlessmake.pm: " << lines << ": error: too few arguments\n";
            else
                cout << "pointlessmake.pm: " << lines << ": error: too many arguments\n";
            return;
        }

        object->SetCompiler(words[1]);
        return;
    }

    if (words[0] == "files")
    {
        if (words.size() == 1)
        {
            cout << "pointlessmake.pm: " << lines << ": error: to few arguments\n";
            return;
        }

        for (unsigned int i = 1; i < words.size(); i++)
            object->AddFiles(words[i]);
    }

}

bool PointlessMake::CheckIfFileExists(string& filePath) const
{
    ifstream f(filePath.c_str());
    if (f.good())
    {
        f.close();
        return true;
    }
    else
    {
        f.close();
        return false;
    }
}

bool PointlessMake::GetError()
{
    return error;
}

void PointlessMake::CreateOutput()
{
    for (unsigned int i = 0; i < staticLibraries.size(); i++)
    {
        if (staticLibraries[i]->CompileFiles())
            staticLibraries[i]->Create();
    }
    for (unsigned int i = 0; i < sharedObjects.size(); i++)
    {
        if (sharedObjects[i]->CompileFiles())
            sharedObjects[i]->Create();
    }
    for (unsigned int i = 0; i < executables.size(); i++)
    {
        if (executables[i]->CompileFiles())
            executables[i]->Create();
    }
}

void PointlessMake::SetCurrentTimeInConfigFile() const
{
    string path = "bin/.config.pm";
    if (CheckIfFileExists(path))
        system("rm bin/.config.pm");

    system("touch bin/.config.pm");
    unsigned long long int _seconds = GetLastModification(path);

    ofstream f("bin/.config.pm");
    f << _seconds;

    f.close();
}

unsigned long long int PointlessMake::GetLastModification(string& file) const
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

