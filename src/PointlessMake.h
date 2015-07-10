#ifndef _POINTLESSMAKE_H__
#define _POINTLESSMAKE_H__

#define PointlessMakeFile "pointlessmake.pam"

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
        void CreateOutput();
        bool CheckIfFileIsCorrect();
        bool GetError();
    private:
        unsigned long long int GetLastModification(std::string&) const;
        void SetCurrentTimeInConfigFile() const;
        void ProcessingKeyword(std::vector<std::string>&);
        void RemoveTabs(std::string&);
        void RemovePointlessSpaces(std::string&);
        bool CheckIfFileExists(std::string&) const;
        bool CheckIfKeywordExists(std::string&);
        bool CheckNumberOfKeywords(std::vector<std::string>&);
        short int CheckIfDirExists(std::string);

        std::vector<SharedObject*> sharedObjects;
        std::vector<StaticLibrary*> staticLibraries;
        std::vector<Executable*> executables;
        std::vector<std::string> subdirectories;
        OutputType* object;
        bool error = false, compiler = true;
        short int existsBin, existsSrc, type;
        unsigned long long int seconds = 0, lines = 0;
};

#endif

