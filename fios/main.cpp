#include <iostream>
#include "assert.h"

using namespace std;

const int MAX_LENGTH = 250;

class Employee
{
public:
	Employee(): realSize(0), bufferSize(startSize) { buffer = new char*[startSize]; premium = new int[startSize]; }
    Employee(int _buffSize): realSize(0), bufferSize(_buffSize) { buffer = new char*[bufferSize]; premium = new int[_buffSize]; }
	~Employee() { delete[] buffer; delete[] premium; }
	void Add(char* el, int prem);
	int Size() { return realSize; }
	char*& operator[] (int index) { assert(index < realSize); return buffer[index]; }
    int getPremium(int index) { assert(index < realSize); return premium[index]; }
private:
	char** buffer;
    int* premium;
	int realSize;
	int bufferSize;
	static const int startSize = 50; 
	void grow();
    void stringCopy(char* from, char* to);
    void swap(int ind1, int ind2);
};

void MSDSort(Employee& arr);
void countSortSym(Employee& arr, int pos, int start, int end);
void makeUnique(Employee& arr);


int main()
{
    Employee arr;
    char* name = new char[MAX_LENGTH];
    int prem = 0;
    cin >> name >> prem;
    while(!cin.eof()) {
        arr.Add(name, prem);
        cin >> name >> prem;
    }
    
    //сортируем
    MSDSort(arr);
    
    for(int i = 0; i < arr.Size(); i++) {
        cout << arr[i] << " " << arr.getPremium(i) << endl;
    }
    
    delete[] name;
    return 0;
}


void Employee::Add(char* el, int prem)
{
	if(realSize == bufferSize) {
		grow();
	}
    premium[realSize] = prem;
	buffer[realSize] = new char[MAX_LENGTH];
    stringCopy(el, buffer[realSize++]);
}


void Employee::grow()
{
	int newBufferSize = bufferSize * 2;
	char** newBuffer = new char*[newBufferSize];
	for(int i = 0; i < bufferSize; i++) {
		newBuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = newBuffer;    
    int* newPremium = new int[newBufferSize];
    for(int i = 0; i < bufferSize; i++) {
        newPremium[i] = premium[i];
    }
    delete[] premium;
    premium = newPremium;
	bufferSize = newBufferSize;
}

void Employee::stringCopy(char *from, char *to)
{
    if(from != NULL && to != NULL) {
        int i = 0;
        while(*(from + i) != '\0') {
            to[i] = from[i++];
        }
        to[i] = '\0';
    }
}

void Employee::swap(int ind1, int ind2)
{
    char* temp = buffer[ind1];
    buffer[ind1] = buffer[ind2];
    buffer[ind2] = temp;
    std::swap(premium[ind1], premium[ind2]);
}

void MSDSort(Employee &arr)
{
    countSortSym(arr, 0, 0, arr.Size());
}

void countSortSym(Employee& arr, int pos, int start, int end)
{
    if(end - start < 2) return;
    
    char min = arr[start][pos];
    char max = arr[start][pos];
    for(int i = start + 1; i < end; i++) {
        min = std::min(min, arr[i][pos]);
        max = std::max(max, arr[i][pos]);
    }
    
    if(min == 0 && max == 0) return;
    
    if(min == max) {
        countSortSym(arr, pos + 1, start, end);
        return;
    }
            
    int valuesCount = max - min + 1;
    int* valuesData = new int[valuesCount];
    
    for(int i = 0; i < valuesCount; i++) {
        valuesData[i] = 0;
    }
    
    for(int i = start; i < end; i++) {
        valuesData[arr[i][pos] - min]++;
    }
    
    for( int i = 1; i < valuesCount; i++ ) {
        valuesData[i] += valuesData[i - 1];
    }
    
    int* intervals = new int[valuesCount]; //для рекурсивных вызовов
    for(int i = 0; i < valuesCount; i++) {
        intervals[i] = valuesData[i];
    }
    
    char** tempData = new char*[end-start];
    
    for(int i = end - 1; i >= start; i--) {
        char value = arr[i][pos] - min;
        valuesData[value]--;
        tempData[valuesData[value]] = arr[i];
    }
    
    for(int i = start; i < end; i++) {
        arr[i] = tempData[i - start];
    }
    
    //отправляем сортировать по следующим символам
    int startsFrom = start;
    for(int i = 0; i < valuesCount; i++) {
        countSortSym(arr, pos + 1, startsFrom, start + intervals[i]);
        startsFrom = start + intervals[i];
    }
    
}

void makeUnique(Employee& arr) {
    char* currentName;
    for(int i = 0; i < arr.Size(); i++) {
        
    }
}
