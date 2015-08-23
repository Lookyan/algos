#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <extrafuncs.cpp>

using namespace std;

int main()
{
    StrArr first;
    StrArr second;
    ifstream file1("file.txt");
    ifstream file2("file1.txt");
    first = toGet(file1);
    second = toGet(file2);
    menu(first, second);
    return 0;
}
