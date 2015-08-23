#include <iostream>
#include <string.h>

using namespace std;

const int MAX_LENGTH = 50;

struct Premium
{
    Premium() { name = new char[MAX_LENGTH]; value = 0; }
    
    Premium(char* name, int val) { 
        name = new char[MAX_LENGTH]; 
        strcpy(this->name, name); 
        value = val; 
    }
    
    Premium(const Premium& inst) {
        name = new char[MAX_LENGTH];
        strcpy(this->name, inst.name);
        value = inst.value;
    }
    
    Premium& operator=(const Premium& inst) {
        strcpy(this->name, inst.name);
        this->value = inst.value;
    }

    ~Premium() { 
        delete[] name; 
    }
    
    void setInfo(char* name, int val) { 
        strcpy(this->name, name); 
        value = val;
    }
    
    char* name;
    int value;
};

void countSortSym(Premium* arr, int pos, int start, int end, int& notUnique)
{
    if(end - start < 2) return;
    
    char min = arr[start].name[pos];
    char max = arr[start].name[pos];
    for(int i = start + 1; i < end; i++) {
        min = std::min(min, arr[i].name[pos]);
        max = std::max(max, arr[i].name[pos]);
    }
    
    if(min == 0 && max == 0) {
        notUnique += end - start - 1;
        return;
    }
    
    if(min == max) {
        countSortSym(arr, pos + 1, start, end, notUnique);
        return;
    }
            
    int valuesCount = max - min + 1;
    int* valuesData = new int[valuesCount];
    
    for(int i = 0; i < valuesCount; i++) {
        valuesData[i] = 0;
    }
    
    for(int i = start; i < end; i++) {
        valuesData[arr[i].name[pos] - min]++;
    }
    
    for( int i = 1; i < valuesCount; i++ ) {
        valuesData[i] += valuesData[i - 1];
    }
    
    int* intervals = new int[valuesCount]; //для рекурсивных вызовов
    for(int i = 0; i < valuesCount; i++) {
        intervals[i] = valuesData[i];
    }
    
    Premium* tempData = new Premium[end-start];
    
    for(int i = end - 1; i >= start; i--) {
        char value = arr[i].name[pos] - min;
        valuesData[value]--;
        tempData[valuesData[value]] = arr[i];
    }
    
    for(int i = start; i < end; i++) {
        arr[i] = tempData[i - start];
    }
    
    delete[] tempData;
    
    //отправляем сортировать по следующим символам
    int startsFrom = start;
    for(int i = 0; i < valuesCount; i++) {
        countSortSym(arr, pos + 1, startsFrom, start + intervals[i], notUnique);
        startsFrom = start + intervals[i];
    }
    
}

void MSDSort(Premium* arr, int size, int& notUnique)
{
    notUnique = 0;
    countSortSym(arr, 0, 0, size, notUnique);
}

void makeUnique(Premium* src, Premium* dest, int n) {
    if(n == 0) return;
    dest[0] = src[0];
    int j = 1;
    for(int i = 0; i < n; i++) {
        if(strcmp(src[i].name, dest[j-1].name) != 0) {
            dest[j++] = src[i];
        } else {
            dest[j - 1].value += src[i].value;
        }
    }
}

int main()
{
    int n = 0; //кол-во премий
    cin >> n;
    
    Premium* arr = new Premium[n];
    char* name = new char[MAX_LENGTH];
    int prem = 0;
    for(int i = 0; i < n; i++) {
        cin >> name >> prem;
        arr[i].setInfo(name, prem);
    }
    
    int notUnique = 0;
    
    MSDSort(arr, n, notUnique);
    
    Premium* groupByName = new Premium[n - notUnique];
    makeUnique(arr, groupByName, n);
    
    for(int i = 0; i < n; i++) {
        cout << groupByName[i].name << " " << groupByName[i].value << endl;
    }
    
    delete[] name;
    delete[] arr;
    delete[] groupByName;
    
    return 0;
}

