#include <iostream>

using namespace std;

int partition(int* arr, int start, int end)
{
    int pivotPl = 0, half = ((end + start) / 2) - 1; 
    if(arr[start] < arr[half])
    {
        if(arr[half] < arr[end-1]) pivotPl = half;
        else pivotPl = end-1;
    }
    else
    {
        if(arr[half] < arr[end-1]) pivotPl = end-1;
        else pivotPl = half;
    }
    if(pivotPl != start) swap(arr[start], arr[pivotPl]);
    int pivot = arr[start];
    int i = end - 1, j = end - 1;
    while(j > start)
    {
        if(arr[j] < pivot) --j;
        else
        {
            if(i > j) swap(arr[i], arr[j]);
            --i;
            --j;
        }
    }
    swap(arr[i], arr[start]);
    return i;
}

int findPlace(int* arr, int start, int size, int num)
{
    int toFind = 0;
    for(int i = 0; i < size; ++i)
    {
        toFind = partition(arr, start, size);
        if(num == toFind) break;
        else if(num < toFind) size = toFind;
        else start = num + 1;
    }
    return arr[num];
}

int main()
{
    int k = 0, n = 0;
    cin >> n >>k;
    int* arr = new int[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    cout << findPlace(arr, 0, n, k);
    delete[] arr; 
    return 0;
}

