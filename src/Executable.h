#ifndef _EXECUTABLE_H__
#define _EXECUTABLE_H__

#include "OutputType.h"

class Executable : public OutputType
{
    public:
        Executable(unsigned long long int, unsigned long long int);
        virtual~ Executable();
        void Create();
};

#endif

