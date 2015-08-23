#include <iostream>
#define DEBUG 9
#include <array.h>
#include <logger.h>
#include <fstream>

const int beginSize = 20;
using namespace std;

template <int arrSize, typename T>
bool setArr(Array<arrSize, T>& arr, ifstream& file)
{
    int size = arr.getSize();
    T* temp = new T[size];
    try
    {
        for(int i = 0; i < size; ++i)
        {
            if(file.eof()) throw "-----the file is smaller than an array size-----";
            file >> temp[i];
        }
    }
    catch(const char* obj)
    {
        LOG_TRACE(obj);
        delete[] temp;
        return false;
    }
    for(int i = 0; i < size; ++i)
    {
        try
        {
            arr[i] = temp[i];
        }
        catch(const char* obj)
        {
            LOG_TRACE(obj);
        }
    }
    delete[] temp;
    return true;
}

template <int arrSize, typename T>
bool opening(Array<arrSize, T>& arr, ifstream& file)
{
    try
    {
        if(!file.is_open()) throw ("------FILE CAN'T BE OPENED------");
        if(!setArr(arr, file)) throw ("---------ARRAY IS TOO SMALL---------");
    }
    catch(const char* obj)
    {
        LOG_TRACE(obj);
        return false;
    }
    LOG_TRACE(arr.getArr());
    return true;
}

template <int arrSize, typename T>
ostream& operator<< ( ostream& stream, const Array<arrSize, T>& toShow)
{
    toShow.showArr();
    return stream;
}

template <int arrSize, typename T>
void mergeNsort(Array<arrSize, T>& first, Array<arrSize, T>& second)
{
    try
    {
        Array<arrSize, T>* temp = new Array<arrSize, T>(first);
        first.arrMerge(second);
        first.sort();
        cout << first;
        first = *temp;
        delete temp;
    }
    catch(bad_alloc)
    {
        LOG_TRACE ("------bad allocation------");
        return;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    ifstream file1("file1.txt");
    ifstream file2("file2.txt");
    ofstream logFile("log.txt");
    if(!logFile.is_open())
    {
        cout << "-------------MIND THE LOG FILE!!!------------" <<endl;
        return 0;
    }
    try
    {
        Array <beginSize, char> firstChar;
        Array <beginSize, char> secondChar;
        if(!opening(firstChar, file1)) return 0;
        if(!opening(secondChar, file2)) return 0;
        Array <beginSize, char>* arrArr = new Array <beginSize, char>[2];
        arrArr[0] = firstChar;
        arrArr[1] = secondChar;
        cout << "First array" <<endl;
        cout << arrArr[0];
        cout << "Second array" <<endl;
        cout << arrArr[1];
        cout << "Merged arrays" <<endl;
        mergeNsort(arrArr[0], arrArr[1]);
        try {
            cout << "Out of range" <<endl;
            cout << arrArr[0][40];
        }
        catch(out_of_range& e) {
            LOG_TRACE(e.what());
            cout << e.what() <<endl;
        }
    }
    catch(bad_alloc)
    {
        LOG_TRACE ("------bad allocation------");
        file1.close();
        file2.close();
        logFile.close();
        return 0;
    }
    file1.close();
    file2.close();
    logFile.close();
    return 0;
}

