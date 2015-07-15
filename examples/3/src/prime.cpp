#include <iostream>

using namespace std;

bool isPrime(int number)
{
    for (int i = 2; i < number / 2; i++)
        if (number % i == 0)
            return false;

    return true;
}

int main()
{
    if (isPrime(17))
        cout << "The number is prime\n";
    else
        cout << "The number is not prime\n";

    return 0;
}

