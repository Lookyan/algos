#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int partition(int* arr, int start, int end)
{
    if(start == end) return start;
    //выбираем опорный эл-т
    int pivot = start + rand() % (end - start + 1);
    //меняем с первым
    swap(arr[pivot], arr[start]);
    int i = end;
    int j = end;
    
    while(j >= start + 1) {
        if(arr[j] < arr[start]) {
            j--;
        } else {
            swap(arr[i--], arr[j--]);
        }
    }
    swap(arr[start], arr[i]);
    return i;
}

int getAtPos(int*& arr, int n, int k)
{
    int start = 0, end = n - 1, p = -1;
    while ( p != k )
    {
        p = partition(arr, start, end);
        if ( k > p )
            start = p + 1;
        if ( k < p )
            end = p - 1;
    }
    return arr[k];
}

int main()
{    
    srand(time(0));
    int n = 0;
    int k = 0;
    cin >> n >> k;
    int* arr = new int[n];
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int el = getAtPos(arr, n, k);
    cout << el;
    delete[] arr;
    return 0;
}

