#include <iostream>

using namespace std;

int part(int* arr, int left, int right)
{
    int i = left, j = left;
    int pivot = arr[right - 1];
    while(j < right - 1)
    {
        if(arr[j] > pivot) 
        {
            ++j;
        }
        else
        {
            swap(arr[i], arr[j]);
            ++i;
            ++j;
        }
    }
    swap(arr[i], arr[right - 1]);
    return i;
}

void xoara(int* arr, int left, int right)
{
    if(left < right)
    {
        int q = part(arr, left, right);
        xoara(arr, left, q);
        xoara(arr, q + 1, right);
    }
}

int main()
{
    
    int arr[7] = {32, 42, 23, 22, 3, 2, -2};
    xoara(arr, 0, 7);
    for(int i = 0; i < 7; ++i)
    {
        cout << arr[i] <<" ";
    }
    return 0;
}

