#ifndef _STATICLIBRARY_H__
#define _STATICLIBRARY_H__

#include <string>
#include <vector>
#include "OutputType.h"

class StaticLibrary : public OutputType
{
    public:
        StaticLibrary(unsigned long long int);
        virtual~ StaticLibrary();
        void Create();
        void SetLdflags(std::string&);
};

#endif

