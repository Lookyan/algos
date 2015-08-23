/* Лукьянченко Александр. АПО-12
 * Задача 3_2. Современники
 * Группа людей называется современниками если был такой момент, когда они могли собраться вместе. Для этого в этот момент каждому из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
*/

#include <iostream>

using namespace std;

const int MIN = 18;
const int MAX = 80;

class Date
{
public:
    Date(): day(0), month(0), year(0), isBirth(true) {}
    Date(int d, int m, int y, bool birth):day(d), month(m), year(y), isBirth(birth) {}
    Date(const Date&);
    ~Date() {}
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    bool getIsBirth() const { return isBirth; }
    friend bool operator <(const Date&, const Date&);
    friend bool operator >(const Date&, const Date&);
    friend bool operator ==(const Date&, const Date&);
    Date& operator= (Date date);
private:
    int day;
    int month;
    int year;
    bool isBirth;
};

void merge(Date* A, int first, int last, Date* buff);

void mergeSort(Date* A, int first, int last, Date* buff);

int maxLayer(Date* A, int n);

int main()
{
    int n = 0;
    cin >> n;
    Date* dates = new Date[2*n];
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
        dates[i] = Date(day, month, year, birth);
        birth = birth ? false : true;
    }
    
    Date* buff = new Date[2*n];
    
    //сортируем все даты
    mergeSort(dates, 0, 2*n - 1, buff);
    
    //находим максимальный слой:
    int max = maxLayer(dates, 2*n);
    
    cout << max;
    delete[] dates;
    delete[] buff;
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

Date& Date::operator= (Date date)
{
    this->day = date.getDay();
    this->month = date.getMonth();
    this->year = date.getYear();
    this->isBirth = date.getIsBirth();
    return *this;
}

Date::Date(const Date& date)
{
    this->day = date.getDay();
    this->month = date.getMonth();
    this->year = date.getYear();
    this->isBirth = date.getIsBirth();
}

void merge(Date* A, int first, int last, Date* mas)
{
    int middle, start, final, j;
    middle = (first+last)/2; //вычисление среднего элемента
    start = first; //начало левой части
    final = middle+1; //начало правой части
    for(j = first; j <= last; j++) {//выполнять от начала до конца
        // при одинаковых датах сначала должны идти даты смерти
        if((start <= middle) && ((final > last) || ((A[start] == A[final]) && A[start].getIsBirth() == false) || (A[start] < A[final]))) {
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

void mergeSort(Date* A, int first, int last, Date* buff)
{
    if(first < last)
    {
        mergeSort(A, first, (first+last)/2, buff); //сортировка левой части
        mergeSort(A, (first+last)/2+1, last, buff); //сортировка правой части
        merge(A, first, last, buff); //слияние двух частей
    }
}

int maxLayer(Date* A, int n)
{
    int max = 0;
    int layer = 0;
    for(int i = 0; i < n; i++) {
        if(A[i].getIsBirth()) {
            layer++;
            if(layer > max) max = layer;
        } else {
            layer--;
        }
    }
    return max;
}
