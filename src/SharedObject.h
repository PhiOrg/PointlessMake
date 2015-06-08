#ifndef _SHAREDOBJECT_H__
#define _SHAREDOBJECT_H__

#include <string>
#include <vector>

class SharedObject
{
    public:
        SharedObject(unsigned long long int);
        virtual~ SharedObject();
        void SetName(std::string&);
        void SetCompiler(std::string&);
        void SetCflags(std::string&);
        void SetFiles(std::string&);
        void CompileFiles();
        void Create();
    private:
        void RemovePointlessSpaces(std::string&);
        unsigned long long int GetLastModification(std::string&);
        unsigned long long int lastCompilation;
        std::string name, compiler, cflags;
        std::vector<std::string> files, objectFiles;
};

#endif

