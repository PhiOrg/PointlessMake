#ifndef _STATICLIBRARY_H__
#define _STATICLIBRARY_H__

#include <string>

class StaticLibrary
{
    public:
        StaticLibrary();
        virtual~ StaticLibrary();
        void SetName(std::string&);
        void SetCompiler(std::string&);
        void SetCflags(std::string&);
        void SetFiles(std::string&);
    private:
        std::string name, compiler, cflags, files;
};

#endif

