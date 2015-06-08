#ifndef _STATICLIBRARY_H__
#define _STATICLIBRARY_H__

#include <string>
#include <vector>

class StaticLibrary
{
    public:
        StaticLibrary(unsigned long long int);
        virtual~ StaticLibrary();
        void SetName(std::string&);
        void SetCompiler(std::string&);
        void SetCflags(std::string&);
        void SetFiles(std::string&);
        void CompileFiles();
    private:
        void RemovePointlessSpaces(std::string&);
        unsigned long long int GetLastModification(std::string&);
        unsigned long long int lastCompilation;
        std::string name, compiler, cflags;
        std::vector<std::string> files, objectFiles;
};

#endif

