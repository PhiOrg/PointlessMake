#ifndef _OUTPUTTYPE_H__
#define _OUTPUTTYPE_H__

#include <string>
#include <vector>

#include "File.h"

#define FG_red 31
#define FG_green 32
#define FG_blue 34
#define FG_white 39
#define BG_red 41
#define BG_green 42
#define BG_blue 44
#define BG_black 49

class OutputType
{
    public:
        void SetName(std::string&);
        void SetCompiler(std::string&);
        void AddCflags(std::string&);
        void AddFiles(std::string&);
        void AddLdflags(std::string&);
        bool CompileFiles();
        virtual void Create() = 0;
    protected:
        void SetColor(int) const;
        unsigned long long int GetFileSize(std::string) const;
        unsigned long long int GetLastModification(std::string&) const;
        bool CheckIfExistsErrors(std::string) const;

        unsigned long long int lastCompilation, line;
        std::string name, compiler, cflags, ldflags;
        std::vector<File> files;
};

#endif

