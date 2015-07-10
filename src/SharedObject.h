#ifndef _SHAREDOBJECT_H__
#define _SHAREDOBJECT_H__

#include <string>
#include <vector>
#include "OutputType.h"

class SharedObject : public OutputType
{
    public:
        SharedObject(unsigned long long int, unsigned long long int);
        virtual~ SharedObject();
        void Create();
};

#endif

