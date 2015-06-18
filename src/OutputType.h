#ifndef _OUTPUTTYPE_H__
#define _OUTPUTTYPE_H__

#include <string>
#include <vector>

class OutputType
{
    public:
        void SetName(std::string&);
        void SetCompiler(std::string&);
        void SetCflags(std::string&);
        void SetFiles(std::string&);
        void CompileFiles();
        virtual void Create() = 0;
        virtual void SetLdflags(std::string&) = 0;
    protected:
        void RemovePointlessSpaces(std::string&);
        unsigned long long int GetLastModification(std::string&);
        unsigned long long int lastCompilation;
        std::string name, compiler, cflags;
        std::vector<std::string> files, objectFiles;
};

#endif

