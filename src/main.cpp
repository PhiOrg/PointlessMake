#include "PointlessMake.h"
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

#define VERSION "1.0";

void help()
{
    cout << "Options:\n";
    cout << "   clean   - delete the bin directory\n";
    cout << "   all     - delete the bin directory and compiles all files\n";
    cout << "   version - print the version\n";
    cout << "   about   - Print some informations about this project\n";
}

void version()
{
    cout << "PointlessMake " << VERSION << "\n";
}

void about()
{
    cout << "This software is a auto-tools. It's free and open source.\n";
    cout << "The source code you can find on github:\n";
    cout << "http://github.com/RoumanianSoftwareDevelopment/PointlessMake\n";
}

void clean()
{
    system("rm -rf bin/");
}

void pointlessMake(bool pmAll)
{
    if (pmAll)
        clean();

    PointlessMake pm;
    if (!pm.GetError())
    {
        if (pm.CheckIfFileIsCorrect())
        {
            pm.CreateOutput();
        }
    }
}

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        cout << "ERROR: too many arguments\n";
        cout << "Try 'PointlessMake help' for more information.\n";
    }

    if (argc == 1)
    {
        pointlessMake(false);
    }
    else
    {
        string command = argv[1];
        if (command == "clean")
        {
            clean();
            return 0;
        }
        if (command == "help")
        {
            help();
            return 0;
        }
        if (command == "version")
        {
            version();
            return 0;
        }
        if (command == "about")
        {
            about();
            return 0;
        }
        if (command == "all")
        {
            pointlessMake(true);
            return 0;
        }

        cout << "ERROR: the second arguments doesn't exists.\n";
        cout << "Try 'PointlessMake help' for more information.\n";
    }

    return 0;
}

