#include "File.h"
#include <fstream>
#include <unistd.h>

using namespace std;

File::File(string& filePath)
{
    this->file = filePath;
    if (file.size() < 4)
        error = 1;

    if (file[0] != 's' || file[1] != 'r' || file[2] != 'c' || file[3] != '/')
        error = 1;

    if (error == 0)
    {
        if (!CheckIfFileExists())
            error = 2;
    }

    if (error == 0)
    {
        if (access(file.c_str(), R_OK) != 0)
            error = 3;
    }

    if (error == 0)
    {
        objectFile = file;
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

        CreateDirectoryForObjectFile();

        if (CheckIfObjectFileExists())
            if (access(objectFile.c_str(), R_OK) != 0)
                error = 4;
    }

}

void File::CreateDirectoryForObjectFile() const
{
    string path = objectFile;
    unsigned int i = path.size() - 1;
    while (path[i] != '/')
        path.erase(i--);

    string command = "mkdir -p " + path;
    system(command.c_str());
}

string File::GetFile() const
{
    return file;
}

string File::GetObjectFile() const
{
    return objectFile;
}

string File::GetError() const
{
    if (error == 1)
        return file + " isn't in the src directory.";
    if (error == 2)
        return file + " doesn't exists.";
    if (error == 3)
        return file + " permission denied.";
    if (error == 4)
        return objectFile + "permission denied";

    return "";
}

void File::SetCompilationErrors()
{
    if (error == 0)
        error = 5;
}

bool File::FileIsOk() const
{
    return error == 0;
}

bool File::CheckIfFileExists() const
{
    ifstream f(file.c_str());
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

bool File::CheckIfObjectFileExists() const
{
    ifstream f(objectFile.c_str());
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

