#include <cstdlib>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include "OutputType.h"
#include "parser.h"

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
            if (files[i].CheckIfObjectFileExists())
            {
                string _command = "rm " + files[i].GetObjectFile();
                system(_command.c_str());
            }

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
            else
            {
                string _command = "rm " + files[i].GetObjectFile();
                system(_command.c_str());
            }
        }

        string command = compiler + ' ' + cflags + " -c " + files[i].GetFile();
        command += " -o " + files[i].GetObjectFile();

        SetColor(FG_blue);
        cout << command;
        SetColor(FG_white);
        cout << "\n";

        command += " 2>&1 | tee -a .compilationFile";
        system(command.c_str());

        if (GetFileSize(".compilationFile") == 0)
        {
            SetColor(FG_green);
            cout << "succesfully compilation";
            SetColor(FG_white);
            cout << "\n\n";
        }
        else
        {
            if (CheckIfExistsErrors(".compilationFile"))
            {
                files[i].SetCompilationErrors();
                SetColor(FG_red);
                cout << "failed compilation";
                SetColor(FG_white);
                cout << "\n\n";
            }
            else
            {
                SetColor(FG_red);
                cout << "the warnings should be fixed";
                SetColor(FG_white);
                cout << "\n\n";
            }
        }

        system("rm .compilationFile");
    }

    return result;
}

unsigned long long int OutputType::GetFileSize(string file) const
{
    struct stat filestatus;
    stat(file.c_str(), &filestatus);

    return filestatus.st_size;
}

bool OutputType::CheckIfExistsErrors(string file) const
{
    ifstream f(file.c_str());
    string line;

    int errors = 0;
    while (getline(f, line))
    {
        size_t found = line.find("error");
        if (found != string::npos)
            errors++;
    }

    return errors != 0;
}

unsigned long long int OutputType::GetLastModification(std::string& file) const
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

void OutputType::SetColor(int code) const
{
    cout << "\033[" << code << "m";
}

