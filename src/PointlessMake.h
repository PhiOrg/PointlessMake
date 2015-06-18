#ifndef _POINTLESSMAKE_H__
#define _POINTLESSMAKE_H__

#define PointlessMakeFile "pointlessmake.pm"

#include <string>
#include <vector>

#include "OutputType.h"
#include "SharedObject.h"
#include "StaticLibrary.h"
#include "Executable.h"

class PointlessMake
{
    public:
        PointlessMake();
        virtual~ PointlessMake();
        void Execute();
        bool CheckIfFileIsCorrect();
    private:
        void GetSubdirectories(std::string);
        void ProcessingKeyword(std::vector<std::string>&);
        void RemoveTabs(std::string&);
        void RemovePointlessSpaces(std::string&);
        bool CheckIfFileExists(std::string&);
        bool CheckIfKeywordExists(std::string&);
        short int CheckIfDirExists(std::string);

        std::vector<SharedObject*> sharedObjects;
        std::vector<StaticLibrary*> staticLibraries;
        std::vector<Executable*> executables;
        std::vector<std::string> subdirectories;
        OutputType* object;
        bool ret = true;
        short int existsBin, existsSrc;
        unsigned long long int seconds = 0, lines = 0;
};

#endif

