#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;
const int beginSize = 20;
const int length = 20;
int startSize = 2;
int grFact = 2;

class StrArr
{
public:
    StrArr();
    StrArr(int size);
    StrArr(const StrArr &obj);
    ~StrArr();
    void addStr(char *toAdd);
    char *getStr (int num) const;
    void setStr(char *toSet, int num);
    int getSize() const { return size;}
    void show();
    void show(int numOfStr);

    void concat(const StrArr &obj);
    void mergeArr(const StrArr &obj);
    void sort();
private:
    char **arr;
    int size;
    int buffSize;
    void grow();
};

StrArr::StrArr()
{
    size = 0;
    buffSize = startSize;
    arr = new char* [buffSize];
    for(int i = 0; i < buffSize; ++i)
    {
        arr[i] = new char[length];
    }
}

StrArr::~StrArr()
{
    for(int i = 0; i < size; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;
    cout<<"deleted"<<endl;
}

StrArr::StrArr(int size)
{
    this->size = size;
    arr = new char* [size];
    for(int i = 0; i < size; ++i)
    {
        arr[i] = new char[length];
    }
}

StrArr::StrArr(const StrArr &obj)
{
    cout << "test";
    size = 0;
    buffSize = startSize;
    arr = new char* [buffSize];
    int toAlloc = 0;
    for(int i = 0; i < buffSize; ++i)
    {
        toAlloc = strlen(obj.getStr(i));
        arr[i] = new char [toAlloc];
    }
    while(obj.getSize() != size)
    {
        this->addStr(obj.getStr(size));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

char *StrArr::getStr(int num) const
{
    if(arr[num] == 0) return 0;
    int size = strlen (arr[num]);
    char *temp = new char[size];
    strcpy(temp, arr[num]);
    return temp;
}

void StrArr::setStr(char *toSet, int num)
{
    delete[] arr[num];
    int toAlloc = strlen(toSet);
    arr[num] = new char[toAlloc];
    strcpy(arr[num], toSet);
}

void StrArr::grow()
{
    buffSize = size * grFact;
    char **tempArr = new char *[buffSize];
    for(int i = 0; i < buffSize; ++i)
    {
        tempArr[i] = new char[length];
    }
    for(int i = 0; i < size ; ++i)
    {
        strcpy(tempArr[i], arr[i]);
    }
    for(int i = 0; i < size; ++i)
    {
        delete[] arr[i];
    }
    delete [] arr;
    arr = tempArr;
}

void StrArr::addStr(char *toAdd)
{
    if(size == buffSize) grow();
    strcpy(arr[size++], toAdd);
}

void StrArr::show()
{
    cout<<"---------------------------------------------------"<<endl;
    for(int i = 0; i < size ; ++i)
    {
        cout<<i+1<<". "<<arr[i];
        cout<<endl;
    }
    cout<<"---------------------------------------------------"<<endl;
}

void StrArr::show(int numOfStr)
{
    if(numOfStr < 1 || numOfStr > size)
    {
        cout<<"-------------!!!no such string!!!-------------"<<endl;
        return;
    }
    cout<<"The string number "<<numOfStr<<" is\t";
    for(int k = 0; k < length; ++k)
    {
        cout<<arr[numOfStr-1][k];
    }
    cout<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

void StrArr::concat(const StrArr &obj)
{
    int totalSize = 0;
    int toCmp = obj.getSize();
    char **tempArr = new char *[size];
    for(int i = 0; i < size; ++i)
    {
        if(i >= toCmp)
        {
            while (i < size)
            {
                tempArr[i] = new char[strlen(arr[i])];
                strcpy(tempArr[i], arr[i]);
                ++i;
            }
        }
        else
        {
            totalSize = strlen(arr[i]) + strlen(obj.getStr(i));
            tempArr[i] = new char[totalSize];
            int toAdd = strlen(arr[i]);
            strcpy(&tempArr[i][0], arr[i]);
            strcpy(&tempArr[i][toAdd], obj.getStr(i));
        }
    }
    for(int i = 0; i < size; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;
    arr = tempArr;
}

void StrArr::mergeArr(const StrArr &obj)
{
    int totalSize = size + (obj.getSize());
    char **tempArr = new char *[totalSize];
    int toAlloc = 0;
    int cntr = 0;
    int i=0;
    for(int k = 0; k < size; ++k)
    {
        int subcntr = 0;
        for(int j = 0; j < cntr; ++j)
        {
            if(strcmp(tempArr[j],arr[i])) ++subcntr;
        }
        if(cntr == subcntr)
        {
            toAlloc = strlen(arr[i]);
            tempArr[i] = new char[toAlloc];
            strcpy(tempArr[i], arr[i]);
            ++cntr;
            ++i;
        }
        else --totalSize;
    }
    for(int c = 0; c < obj.getSize(); ++c)
    {
        int subcntr = 0;
        for(int j = 0; j < cntr; ++j)
        {
            if(strcmp(tempArr[j],obj.getStr(c))) ++subcntr;
        }
        if(cntr == subcntr)
        {
            toAlloc = strlen(obj.getStr(c));
            tempArr[i] = new char[toAlloc];
            strcpy(tempArr[i], obj.getStr(c));
            ++cntr;
            ++i;
        }
        else --totalSize;
    }
    for(int i = 0; i < size; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;
    arr = tempArr;
    size = totalSize;
}

void StrArr::sort()
{
    for(int i = 0; i < size-1; ++i)
    {
        for(int k = i+1; 0 < k; --k )
        {
            char *prev = this->getStr(k-1);
            char *current = this->getStr(k);
            if((int)current[0] < (int)prev[0])
            {
                setStr(prev, k);
                setStr(current,k-1);
            }
            else if((int)current[0] == (int)prev[0])
            {

                int min = 0, count = 0;
                min = strlen(prev);
                if((int)strlen(current) < min) min = strlen(current);
                for(int i = 0; i < min; ++i)
                {
                    if((int)current[i] < (int)prev[i])i=min;
                    else ++count;
                }
                if(count != min)
                {
                    setStr(prev, k);
                    setStr(current,k-1);
                }

            }
            else k = 0;
            delete[] prev;
            delete[] current;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

StrArr *toGet(ifstream &file)
{
    StrArr *temp = new StrArr;
    char** enterArr = new char* [beginSize];
    for(int i = 0; i < beginSize ; ++i)
    {
        enterArr[i] = new char [length];
    }
    if (!file.is_open()) cout << "Файл не может быть открыт!\n";
    else
    {
        int cntr = 0;
        while(!file.eof())
        {
            file.getline(enterArr[cntr], length);
            temp->addStr(enterArr[cntr++]);
        }
    }
    file.close();
    for(int i = 0; i < beginSize ; ++i)
    {
        delete[] enterArr[i];
    }
    delete[] enterArr;
    return temp ;
}

void forFixedArr(StrArr *array, ifstream &file)
{
    if (!file.is_open()) cout << "Файл не может быть открыт!\n";
    else
    {
        int cntr = 0;
        while(cntr != array->getSize())
        {
            char *temp = new char[length];
            file.getline(temp, length);
            array->setStr(temp, cntr++);
            delete[] temp;
        }
    }
    file.close();
}

void showStr(StrArr *arr)
{
    cout<<"Enter a number of string you want to see (from 1 to "<<arr->getSize()<<")\t";
    int num = 0;
    arr->show(num);
}

void menu(StrArr *first, StrArr *second)
{
    cout<<"------------------------------MENU------------------------------"<<endl;
    cout<<"1. Show array"<<endl;
    cout<<"2. Show string in an array"<<endl;
    cout<<"3. Concatenate arrays (into one)"<<endl;
    cout<<"4. Merge and delete copies (into one)"<<endl;
    cout<<"5. Sort an array"<<endl;
    cout<<"6. Make a copy of an array"<<endl;
    cout<<"7. Construct an array of the fixed size"<<endl;
    cout<<"8. Exit"<<endl;
    cout<<"Please enter your destination\t";
    int target = 0;
    int toAct = 0;
    cin >> target;
    if(target == 8) return;
    if(target < 7)
    {
        cout<<"Please enter an array(1/2)\t";
        cin >> toAct;
    }
    if((int)target < 0 || (int)target > 9 )
    {
        cout<<"-------------!!!no such directory!!!-------------"<<endl;
        return;
    }
    if((toAct != 1) && (toAct != 2))
    {
        cout<<"No such array"<<endl;
        return;
    }
    switch(target)
    {
        case 1:
            if(toAct == 1) first->show();
            else second->show();
            break;
        case 2:
            cin.ignore();
            if(toAct == 1) showStr(first);
            else showStr(second);
            break;
        case 3:
            if(toAct == 1)
            {
                first->concat(*second);
                first->show();
            }
            else
            {
                second->concat(*first);
                second->show();
            }
            break;
        case 4:
            if(toAct == 1)
            {
                first->mergeArr(*second);
                first->show();
            }
            else
            {
                second->mergeArr(*first);
                second->show();
            }
            break;
        case 5:
            if(toAct == 1)
            {
                first->sort();
                first->show();
            }
            else
            {
                second->sort();
                second->show();
            }
            break;
        case 6:
        {
            if(toAct == 1)
            {
                StrArr *newArr = new StrArr(*first);
                newArr->show();
                delete newArr;
            }
            else
            {
                StrArr *newArr = new StrArr(*second);
                newArr->show();
                delete newArr;
            }
            break;
        }
        case 7:
        {
            int amount = 0;
            cout<<"Enter amount of strings\t";
            cin >> amount;
            StrArr * newArr = new StrArr(amount);
            ifstream file3("/home/alex/QtProjects/build-StrArr-Desktop-Debug/file.txt");
            forFixedArr(newArr, file3);
            newArr->show();
            delete newArr;
            break;
        }
        default:
            cout<<"-------------no such directory-----------"<<endl;
            break;
    }
    cout<<"Show the menu again?(y/n)\t";
    char ans;
    cin >> ans;
    if(ans == 'y')
    {
        menu(first, second);
    }
    else return;
}

int main()
{
    system("clear");
    StrArr *first;
    StrArr *second;
    ifstream file1("/home/alex/QtProjects/build-StrArr-Desktop-Debug/file.txt");
    ifstream file2("/home/alex/QtProjects/build-StrArr-Desktop-Debug/file1.txt");
    ifstream file3("/home/alex/QtProjects/build-StrArr-Desktop-Debug/file.txt");
    first = toGet(file1);
    second = toGet(file2);
    menu(first, second);
    delete first;
    delete second;
    return 0;
}

