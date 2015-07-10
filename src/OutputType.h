#ifndef _OUTPUTTYPE_H__
#define _OUTPUTTYPE_H__

#include <string>
#include <vector>
#include "File.h"

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
        unsigned long long int GetLastModification(std::string&);
        unsigned long long int lastCompilation, line;
        std::string name, compiler, cflags, ldflags;
        std::vector<File> files;
};

#endif

