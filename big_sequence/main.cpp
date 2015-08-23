#include <iostream>

using namespace std;

template <class T>
void merge(T* A, int first, int last, T* mas);

template <class T>
void mergeSort(T* A, int first, int last, T* buff);

template <class T>
void mergeM(T* A, int first, int last, int middle, T* mas);

void getElements(int* arr, int n);

int main()
{
    int n = 0;
    int k = 0;
    cin >> n >> k;
    int allCount = n;
    int getCount = 0;
    int* arr = new int[2*k];
    int* buff = new int[2*k];
    getElements(arr, k);
    allCount -= k;
    mergeSort(arr, 0, k-1, buff);
    
    while(allCount > 0) {
        if(allCount - k >= 0) {
            getCount = k;
            allCount -= k;
        } else {
            getCount = allCount;
            allCount = 0;
        }
        getElements(arr + k, getCount);
        mergeSort(arr, k, k + getCount - 1, buff);
        mergeM(arr, 0, k + getCount - 1, k-1, buff);
    }
    
    for(int i = 0; i < k; i++) {
        cout << arr[i] << " ";
    }
    
    delete[] arr;
    delete[] buff;
    return 0;
}

template <class T>
void mergeM(T* A, int first, int last, int middle, T* mas)
{
    int start, final, j;
    start = first; //начало левой части
    final = middle+1; //начало правой части
    for(j = first; j <= last; j++) {//выполнять от начала до конца
        if((start <= middle) && ((final > last) || (A[start] <= A[final]))) {
            mas[j] = A[start];
            start++;
        }
        else {
            mas[j] = A[final];
            final++;
        }
    }
    
    for (j = first; j <= last; j++) A[j] = mas[j];
}

template <class T>
void merge(T* A, int first, int last, T* mas)
{
    int middle, start, final, j;
    middle = (first+last)/2; //вычисление среднего элемента
    start = first; //начало левой части
    final = middle+1; //начало правой части
    for(j = first; j <= last; j++) {//выполнять от начала до конца
        if((start <= middle) && ((final > last) || (A[start] <= A[final]))) {
            mas[j] = A[start];
            start++;
        }
        else {
            mas[j] = A[final];
            final++;
        }
    }
    
    for (j = first; j <= last; j++) A[j] = mas[j];
}

template <class T>
void mergeSort(T* A, int first, int last, T* buff)
{
    if(first < last)
    {
        mergeSort(A, first, (first+last)/2, buff); //сортировка левой части
        mergeSort(A, (first+last)/2+1, last, buff); //сортировка правой части
        merge(A, first, last, buff); //слияние двух частей
    }
}

void getElements(int* arr, int n)
{
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}
