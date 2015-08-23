#include <iostream>
#include <algorithm>

using namespace std;

const int delta = 3;

int main()
{
    int leg = 0;
    cin >> leg;
    int n = 0;
    cin >> n;
    int* arr = new int[n];
    int value = 0;
    int k = 0;
    for(int i = 0; i < n; i++) {
        cin >> value;
        if(value >= leg) {
            arr[k++] = value;
        }
    }
    
    if(k == 0) {
        cout << 0;
        delete[] arr;
        return 0;
    }
    
    //сортируем
    sort(arr, arr + k);
//    for(int i = 0; i < k; i++) {
//        cout << arr[i] << endl;
//    }
    
    int col = 1;
    int prev = arr[0];
    for(int i = 1; i < k; i++) {
        if(prev + delta <= arr[i]) {
            ++col;
            prev = arr[i];
        }
    }
    cout << col;
    delete[] arr;
    return 0;
}

