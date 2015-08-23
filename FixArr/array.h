#ifndef ARRAY
#define ARRAY
#include <iostream>
#include <assert.h>
#include <logger.h>
#include <stdexcept>

using namespace std;

template <int arrSize, typename T>
class Array
{
public:
    Array();
    Array(int setSize);
    Array(const Array&);
    ~Array();
    T* getArr() const { return arr; }
    int getSize() const { return size; }
    void sort();
    template<int N>
    void arrMerge(const Array<N, T> &);
    void showArr() const;
    T& operator[] (int place) const;
    void operator= ( Array&);
private:
    T* arr;
    int size;
};

template < int arrSize, typename T>
Array<arrSize, T>::Array()
{
    size = arrSize;
    try
    {
        arr = new T[arrSize];
    }
    catch(bad_alloc)
    {
        LOG_TRACE ("------bad allocation------");
        throw;
    }
    LOG_TRACE ("-");
}

template < int arrSize, typename T>
Array<arrSize, T>::Array(int setSize)
{
    size = setSize;
    try
    {
        arr = new T[size];
    }
    catch(bad_alloc)
    {
        LOG_TRACE ("------bad allocation------");
        throw;
    }
    LOG_TRACE (setSize);
}

template < int arrSize, typename T>
Array<arrSize, T>::Array(const Array& obj)
{
    size = obj.size;
    try
    {
        arr = new T[size];
    }
    catch(bad_alloc)
    {
        LOG_TRACE ("------bad allocation------");
        throw;
    }
    for(int i = 0; i < size; ++i)
    {
        arr[i] = obj.arr[i];
    }
    LOG_TRACE (obj.getArr());
}

template < int arrSize, typename T>
Array<arrSize, T>::~Array()
{
    LOG_TRACE ("-");
    delete[] arr;
}

template <int arrSize, typename T>
void Array<arrSize, T>::sort()
{
    LOG_TRACE ("-");
    for(int i = 1; i < size; ++i)
    {
        for(int k = i; k > 0; --k)
        {
            if(arr[k] < arr[k-1]) swap(arr[k], arr[k-1]);
        }
    }
}

template <int arrSize, typename T>
template <int N>
void Array<arrSize, T>::arrMerge(const Array<N, T>& obj)
{
    int total = this->size + obj.size;
    Array<arrSize, T>* temp = new Array<arrSize, T>(total);
    int place = 0;
    for(int  i = 0; i < size; ++i)
    {
        temp->arr[place++] = this->arr[i];
    }
    for(int i = 0; i < obj.size ; ++i)
    {
        temp->arr[place++] = obj.arr[i];
    }
    delete[] arr;
    size = total;
    try
    {
        arr = new T[size];
    }
    catch(bad_alloc)
    {
        delete temp;
        LOG_TRACE ("------bad allocation------");
        return;
    }
    for(int i = 0; i < total; ++i)
    {
        arr[i] = temp->arr[i];
    }
    delete temp;
    LOG_TRACE (obj.getArr());
}

template <int arrSize, typename T>
void Array<arrSize, T>::showArr() const
{
    LOG_TRACE("-");
    cout << "-----------------------------------------------"<<endl;
    for(int i = 0; i < size; ++i)
    {
        cout << arr[i] <<" ";
    }
    cout << endl;
    cout << "-----------------------------------------------"<<endl;
}

template <int arrSize, typename T>
T& Array<arrSize, T>::operator[] (int place) const
{
    LOG_TRACE(place);
    if(place < 0 || place >= size) throw out_of_range("-----OUT OF AN ARRAY-----");
    return arr[place];
}

template <int arrSize, typename T>
void Array<arrSize, T>::operator= (Array& obj)
{
    LOG_TRACE (obj.arr);
    if(this == &obj) return;
    delete[] arr;
    size = obj.size;
    try
    {
        arr = new T[size];
    }
    catch(bad_alloc)
    {
        LOG_TRACE ("------bad allocation------");
        return;
    }
    for(int i = 0; i < size; ++i)
    {
        arr[i] = obj.arr[i];
    }
    //LOG_TRACE (obj.arr);
}

#endif // ARRAY
