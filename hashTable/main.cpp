#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int InitialSize = 8;
const float LoadFactor = 0.75;
const int toGrow = 2;
const int FirstK = 7;
const int SecondK = 127;


//Hash table
//N - пусто
//- - удалено
template <class T>
class CHashTable
{
public:
    CHashTable();
    ~CHashTable();
    int Hash(int p, int h1, int h2) const; //получаем пустую ячейку для записи по строке и номеру пробы
    bool Has(const T& data) const;
    bool Add(const T& data);
    bool Delete(const T& data);
private:
    int hash(const T &str, int c) const; // hash для строки
    vector<T> table;
    unsigned int keysCount;
    void growTable();
};

int main()
{
    CHashTable<string> table;
    char operation;
    string word;
    
    while( cin >> operation >> word ) {
        if( operation == '+' ) {
            cout << (table.Add(word) ? "OK" : "FAIL") << "\n";
        } else if( operation == '-' ) {
            cout << (table.Delete(word) ? "OK" : "FAIL") << "\n";
        }if( operation == '?' ) {
            cout << (table.Has(word) ? "OK" : "FAIL") << "\n";
        }
    }
    
    return 0;
}

template <class T>
CHashTable<T>::CHashTable(): keysCount(0)
{
    table.resize(InitialSize, "N");
}

template <class T>
CHashTable<T>::~CHashTable()
{
}

template <class T>
bool CHashTable<T>::Has(const T& data) const
{
    int h1 = hash(data, FirstK);
    int h2 = hash(data, SecondK);
    for(int i = 0; i < table.size(); i++) {
        int pos = Hash(i, h1, h2);
        if(table[pos] == string("N")) {
            return false;
        } else if(table[pos] == data) {
            return true;
        }
    }
    return false;
}

template <class T>
bool CHashTable<T>::Add(const T &data)
{
    if(keysCount + 1 > table.size() * LoadFactor)
        growTable();
    
    //проверяем есть ли уже в таблице
    if(Has(data) == true) {
        return false;
    }
    
    int h1 = hash(data, FirstK);
    int h2 = hash(data, SecondK);
    for(int i = 0; i < table.size(); i++) {
        int pos = Hash(i, h1, h2);
        if(table[pos] == string("N") || table[pos] == string("-")) {
            table[pos] = data;
            keysCount++;
            return true;
        }
    }    
    throw "Can't insert!";
}

template <class T>
bool CHashTable<T>::Delete(const T &data)
{
    int h1 = hash(data, FirstK);
    int h2 = hash(data, SecondK);
    
    for(int i = 0; i < table.size(); i++) {
        int pos = Hash(i, h1, h2);
        if(table[pos] == data) {
            table[pos] = "-";
            keysCount--;
            return true;
        } else if(table[pos] == string("N")) {
            return false;
        }
    }
    return false;
}

template <class T>
int CHashTable<T>::hash(const T& str, int c) const
{
    int hash = 0;
    for( unsigned int i = 0; i < str.size(); i++ ) {
        hash = (hash * c + str[i]) % table.size();
    }
    return hash;
}

template <class T>
int CHashTable<T>::Hash(int p, int h1, int h2) const
{
    int result = (h1 + p * (h2 * 2 + 1)) % table.size();
    return result;
}

template <class T>
void CHashTable<T>::growTable()
{
    vector<T> oldTable = table;
    table = vector<T>(table.size() * toGrow, "N");
    keysCount = 0;
    for(int i = 0; i < oldTable.size(); i++) {
        if(oldTable[i] != string("N") || oldTable[i] != string("-"))
            Add(oldTable[i]);
    }
}
