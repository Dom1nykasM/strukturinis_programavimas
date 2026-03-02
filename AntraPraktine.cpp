#include <iostream>
using namespace std;

const int MAX_MOKINIU = 100;
const int MAX_PAZYMIU = 10;

//palyginimas tekstu
in VienodiVardai (char a[], char b[])
{
    int i = 0;
    while ( a[i] != '\0' || b[i] != '\0')
    {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return 1;
}