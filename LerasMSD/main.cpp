#include <iostream>

using namespace std;

void countSort(char** arr, int from, int till, int posit)
{
    int biggest = arr[from][posit], smallest = arr[till-1][posit];
    for(int i = from; i < till; ++i)
    { 
        if((int)arr[i][posit] > biggest ) biggest = (int)arr[i][posit];
        if((int)arr[i][posit] < smallest) smallest = (int)arr[i][posit];
    }
    int delta = biggest-smallest + 1;
    int bigDelta = till - from;
    int* temp = new int[delta];
    for(int i = 0; i < delta; ++i)
    {
        temp[i] = 0;
    }
    for(int i = from; i < till; ++i)
    {
        int place = (int)arr[i][posit] - smallest;
        temp[place] += 1;
    }
    for(int i = 1; i < delta; ++i)
    {
        temp[i] += temp[i-1];
    }
    char** result = new char*[bigDelta];
    for(int i = till - 1; i >= from; --i)
    {
        int place = arr[i][posit] - smallest;
        int sub = temp[place] -= 1;
        result[sub] = arr[i];
    }
    delete[] temp;
    for(int i = 0; i < bigDelta; ++i)
    {
         arr[from + i] = result[i];
    }
    delete[] result;
}


void mainSort(char** arr, int from, int till, int posit)
{
    if(from + 1 >= till) return;
    countSort(arr, from, till, posit);
    int i = from, start = from;
    while(i < till)
    {
        if(arr[i][posit] == '\0') start = ++i;
        else
        if((i == till - 1) || (arr[i][posit] != arr[i+1][posit]))
        {       
            cout << start << " " << i+1 << endl;
            mainSort(arr, start, i+1, posit + 1);
            start = ++i;
        }
        else ++i;
    }
}

int main()
{   
    char** arr = new char*[7];
//    for(int i = 0; i < 7; ++i)
//    {
//        arr[i] = new char[5];
//    }
    arr[0] ="azcd\0";
    arr[1]= "aac\0";
    arr[2] = "bzds\0";
    arr[3] = "adda\0";
    arr[4] = "bwqe\0";
    arr[5] = "baac\0";
    arr[6] = "aaaa\0";
    
    mainSort(arr, 0, 7, 0);
//    countSort(arr, 0, 7, 0);
    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            cout << arr[i][j] <<" ";
        }
        cout << endl;
    }
//    for(int i = 0; i < 7; ++i)
//    {
//        delete arr[i];
//    }
    delete[] arr;
    return 0;
}

