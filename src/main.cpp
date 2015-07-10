#include "PointlessMake.h"

int main()
{
    PointlessMake pm;
    if (!pm.GetError())
    {
        if (pm.CheckIfFileIsCorrect())
        {
            pm.CreateOutput();
        }
    }

    return 0;
}

