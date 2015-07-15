#include "prime/prime.h"
#include "number/number.h"

#include <iostream>

using namespace std;

int main(void)
{
    if (isPrime(17))
        cout << "The number is prime\n";
    else
        cout << "The number is not prime\n";

    if (checkIfNumberIsOdd(3))
        cout << "The number is odd\n";
    else
        cout << "The number is not odd\n";

    return 0;
}

