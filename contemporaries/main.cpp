#include <iostream>
#include "assert.h"

using namespace std;

const int MIN = 18;
const int MAX = 80;

template <class T>
class CArray
{
public:
	CArray(): realSize(0), bufferSize(startSize) { buffer = new T[startSize]; }
    CArray(int _buffSize): realSize(0), bufferSize(_buffSize) { buffer = new T[bufferSize]; }
	~CArray() { delete[] buffer; }
	void Add(T el);
	int Size() { return realSize; }
	T& operator[] (int index) { assert(index < realSize); return buffer[index]; }
private:
	T* buffer;
	int realSize;
	int bufferSize;
	static const int startSize = 10; 
	void grow();
};

class Date
{
public:
    Date(): day(0), month(0), year(0), isBirth(true) {}
    Date(int d, int m, int y, bool birth):day(d), month(m), year(y), isBirth(birth) {}
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    bool getIsBirth() const { return isBirth; }
    friend bool operator <(const Date&, const Date&);
    friend bool operator >(const Date&, const Date&);
    friend bool operator ==(const Date&, const Date&);
private:
    int day;
    int month;
    int year;
    bool isBirth;
};

template <class T>
void merge(CArray<T>& A, int first, int last);

template <class T>
void mergeSort(CArray<T>& A, int first, int last);

int maxLayer(CArray<Date>& A);

int main()
{
    CArray<Date> dates;
    int n = 0;
    cin >> n;
    int day = 0;
    int month = 0;
    int year = 0;
    bool birth = true;
    for(int i = 0; i < 2*n; i++) {
        cin >> day >> month >> year;
        if(birth == true) {
            year += MIN;
        } else {
            if(dates[i - 1] < Date(day, month, year - MAX + MIN, birth)) {
                //Прожил больше 80 лет
                day = dates[i - 1].getDay();
                month = dates[i - 1].getMonth();
                year = dates[i - 1].getYear() + MAX - MIN;
            }
        }
        dates.Add(Date(day, month, year, birth));
        birth = birth ? false : true;
    }
    
    //сортируем все даты
    mergeSort(dates, 0, 2*n - 1);
    
    //находим максимальный слой:
    int max = maxLayer(dates);
    
    cout << max;
    return 0;
}

bool operator <(const Date& date1, const Date& date2)
{
    if(date1.getYear() < date2.getYear()) {
        return true;
    } else if(date1.getYear() > date2.getYear()) {
        return false;
    } else {
        if(date1.getMonth() < date2.getMonth()) {
            return true;
        } else if(date1.getMonth() > date2.getMonth()) {
            return false;
        } else {
            if(date1.getDay() < date2.getDay()) {
                return true;
            } else {
                return false;
            }
        }
    }
}

bool operator >=(const Date& date1, const Date& date2)
{
    return !(date1 < date2);
}

bool operator ==(const Date& date1, const Date& date2)
{
    if(date1.getDay() == date2.getDay() && 
       date1.getMonth() == date2.getMonth() && 
       date1.getYear() == date2.getYear()) {
        return true;
    } else {
        return false;
    }
}

template <class T>
void CArray<T>::Add(T el)
{
	if(realSize == bufferSize) {
		grow();
	}
	
	buffer[realSize++] = el;
}

template <class T>
void CArray<T>::grow()
{
	int newBufferSize = bufferSize * 2;
	T* newBuffer = new T[newBufferSize];
	for(int i = 0; i < bufferSize; i++) {
		newBuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;
}

template <class T>
void merge(CArray<T>& A, int first, int last)
{
    int middle, start, final, j;
    T* mas = new T[A.Size()];
    middle = (first+last)/2; //вычисление среднего элемента
    start = first; //начало левой части
    final = middle+1; //начало правой части
    for(j = first; j <= last; j++) {//выполнять от начала до конца
        if((start <= middle) && ((final > last) || (A[start] < A[final]))) {
            mas[j] = A[start];
            start++;
        }
        else {
            mas[j] = A[final];
            final++;
        }
    }
    //возвращение результата в список
    for (j = first; j <= last; j++) A[j] = mas[j];
    delete[] mas;
}

template <class T>
void mergeSort(CArray<T>& A, int first, int last)
{
    if(last >= A.Size()) return;
    if(first < last)
    {
        mergeSort(A, first, (first+last)/2); //сортировка левой части
        mergeSort(A, (first+last)/2+1, last); //сортировка правой части
        merge(A, first, last); //слияние двух частей
    }
}

int maxLayer(CArray<Date>& A)
{
    int max = 0;
    int layer = 0;
    for(int i = 0; i < A.Size(); i++) {
        if(A[i].getIsBirth()) {
            layer++;
            if(layer > max) max = layer;
        } else {
            layer--;
        }
    }
    return max;
}
