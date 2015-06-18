#include "PointlessMake.h"
#include "parser.h"

#include <fstream>
#include <iostream>
#include <new>
#include <algorithm>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

using namespace std;

PointlessMake::PointlessMake()
{
    existsBin = CheckIfDirExists("bin/");
    existsSrc = CheckIfDirExists("src/");

    if (existsSrc != 1 || existsBin == 3)
    {
        if (existsBin == 1)
        {
            string path = "bin/.config.pm";
            if (CheckIfFileExists(path))
            {
                ifstream f("bin/.config.pm");
                f >> seconds;
                f.close();
            }
        }
/*        else
        {
            system("mkdir bin");
            GetSubdirectories("src/");
            for (int i = 0; i < subdirectories.size(); i++)
            {
                subdirectories[i][0] = 'b';
                subdirectories[i][1] = 'i';
                subdirectories[i][2] = 'n';
                string s = "mkdir -p " + subdirectories[i];
                system(s.c_str());
            }
        }
*/
    }
    else
    {
        if (existsSrc == 0)
            cout << "ERROR: the src directory doesn't exist\n";
        else
            cout << "ERROR: permission denied to the src directory\n";

        if (existsBin == 3)
            cout << "ERROR: permission denied to the bin directory\n";
    }

}

PointlessMake::~PointlessMake()
{
    for (int i = 0; i < sharedObjects.size(); i++)
        delete sharedObjects[i];
    for (int i = 0; i < staticLibraries.size(); i++)
        delete staticLibraries[i];
    for (int i = 0; i < executables.size(); i++)
        delete executables[i];
}

void PointlessMake::GetSubdirectories(std::string s)
{
    DIR *d = opendir(s.c_str());
    struct dirent *dir;
    if (d != NULL)
    {
        int x = 0;
        while (1)
        {
            dir = readdir(d);
            if (dir != NULL)
            {
                string s2 = dir->d_name;
                if (s2 != "." && s2 != "..")
                {
                    x++;
                    string s3 = s + dir->d_name + '/';
                    GetSubdirectories(s3);
                }
            }
            else
            {
                if (x == 0)
                    subdirectories.push_back(s);
                break;
            }
        }
        closedir(d);
    }
}

short int PointlessMake::CheckIfDirExists(string path)
{
    short int existsDir;
    struct stat info;
    if (stat(path.c_str(), &info))
        existsDir = 0;
    else
        existsDir = 1;

    if (access(path.c_str(), R_OK && W_OK))
        existsDir = 3;

    return existsDir;
}

void PointlessMake::RemoveTabs(string& str)
{
    for (int i = 0; i < str.size(); i++)
        if (str[i] == '\t')
        {
            str.erase(i);
            i--;
        }
}

void PointlessMake::RemovePointlessSpaces(string& str)
{
    int i = 0;
    while (str[i] == ' ')
        str.erase(str.begin());

    i = str.size() - 1;
    while (str[i] == ' ')
    {
        str.erase(i);
        i--;
    }

    for (i = 0; i < str.size() - 1; i++)
        if (str[i] == ' ' && str[i + 1] == ' ')
        {
            str.erase(i);
            i--;
        }
}

bool PointlessMake::CheckIfFileIsCorrect()
{
    string configFile = PointlessMakeFile;
    if (!CheckIfFileExists(configFile))
        return false;

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
            ret = false;
            cout << "pointlessmake.pm: " << lines << ": error: the keyword doesn't exist\n";
            continue;
        }

        ProcessingKeyword(words);
    }

    return ret;
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
        object = new SharedObject(seconds);
        if (words.size() != 2)
        {
            ret = false;
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
        object = new StaticLibrary(seconds);
        if (words.size() != 2)
        {
            ret = false;
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
        object = new Executable(seconds);
        if (words.size() != 2)
        {
            ret = false;
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

    }

}

bool PointlessMake::CheckIfFileExists(string& filePath)
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

