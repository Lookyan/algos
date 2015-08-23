#include <iostream>

using namespace std;

template <class T, int Size = 10>
class Arr
{
public:
    Arr() {
        real = 0;
        buff = Size;
    }
//    template<int N>
//    void merge(Arr<T, N>& arr) {
//        cout << "Everything is OK!" << arr.getSize();
//    }
    template<int N>
    void merge(Arr<T, N>& arr);

    int getSize() {
        return Size;
    }

private:
    int buff;
    int real;
};

template<typename T, int Size>
template<int N>
void Arr<T, Size>::merge(Arr<T, N>& arr) {
    cout << "Everything is OK!" << arr.getSize();
}

int main()
{
//    Arr<int, 5> arr1;
//    Arr<int, 500> arr2;
//    arr1.merge(arr2);
    double* arr = 0;
    while(true) {
        cout << new double[9999999999] << endl;
    }
    
    return 0;
}

