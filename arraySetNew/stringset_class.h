#ifndef STRCLASS
#define STRCLASS
#include <assert.h>
#include <mystring_class.h>

using namespace std;
const int beginSize = 20;
const int length = 20;
int startSize = 1;
int grFact = 2;

class StrArr
{
public:
    StrArr();
    StrArr(int size);
    StrArr(const StrArr &obj);
    ~StrArr();
    void addStr(String* toAdd);
    String *getStr(int num) const;
    void setStr(String* toSet, int num);
    int getSize() const { return size; }
    void show();
    void show(int numOfStr);
    void sort();
    StrArr operator+ (const StrArr& obj);
    StrArr operator- (const StrArr& obj);
    StrArr operator* (const StrArr& obj);
    void operator= (const StrArr& obj);
    String& operator [](int place) const;
private:
    String *arr;
    int size;
    int buffSize;
    void grow();
};

StrArr::StrArr()
{
    size = 0;
    buffSize = startSize;
    arr = new String [buffSize];
}

StrArr::~StrArr()
{
    delete[] arr;
}

StrArr::StrArr(int size)
{
    this->size = size;
    this->buffSize = size;
    arr = new String [buffSize];
}

StrArr::StrArr(const StrArr &obj)
{
    buffSize = size = obj.getSize();
    arr = new String [buffSize];
    int toAlloc = 0;
    for(int i = 0; i < size; ++i)
    {
        toAlloc = obj.arr[i].getLen();
        arr[i] = new String(toAlloc);
        arr[i] = obj.getStr(i);
    }
}

String* StrArr::getStr(int num) const
{
    if(this->size <= num) return 0;
    int size = arr[num].getLen();
    String *temp = new String(size);
    temp = &arr[num];
    return temp;
}

void StrArr::setStr(String *toSet, int num)
{
    arr[num] = new String(toSet);
}

void StrArr::grow()
{
    buffSize = size * grFact;
    String *tempArr = new String [buffSize];
    for(int i = 0; i < size ; ++i)
    {
        tempArr[i] = &arr[i];
    }
    delete [] arr;
    arr = tempArr;
}

void StrArr::addStr(String* toAdd)
{
    if(size == buffSize) grow();
    int counter = 0;
    for(int i = 0; i < size; ++i)
    {
        if(!(arr[i] == toAdd)) ++counter;
    }
    if(counter == size)
    {
        arr[size++] = toAdd;
    }
    else return;
}

void StrArr::show()
{
    cout<<"---------------------------------------------------"<<endl;
    for(int i = 0; i < size ; ++i)
    {
        cout<<i+1<<". ";
        arr[i].show();
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
    arr[numOfStr].show();
    cout<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

void StrArr::sort()
{
    int min = 0, count = 0;
    for(int i = 0; i < size-1; ++i)
    {
        for(int k = i+1; 0 < k; --k )
        {
            String* prev = new String(&arr[k-1]);
            String* current = new String(&arr[k]);
            if((int)current->getElem(0) > (int)prev->getElem(0))
            {
                k = 0;
            }
            else
            {
                min = 0, count = 0;
                min = prev->getLen();
                if((current->getLen()) < min) min = current->getLen();
                for(int j = 0; j < min; ++j)
                {
                    if(((int)current->getElem(j)) > ((int)prev->getElem(j)))
                    {
                        j = min;
                        count = min;
                        k = 0;
                    }
                    else if(((int)current->getElem(j)) < ((int)prev->getElem(j))) j = min;
                    else ++count;
                }
                if(count != min)
                {
                    setStr(prev, k);
                    setStr(current,k-1);
                }
            }
            delete prev;
            delete current;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

StrArr StrArr::operator+ (const StrArr& obj)
{
    StrArr temp;
    for(int k = 0; k < size; ++k)
    {
        temp.addStr(&arr[k]);
    }
    int counter = obj.getSize();
    for(int c = 0; c < counter; ++c)
    {
        temp.addStr(&obj.arr[c]);
    }
    temp.sort();
    return temp;
}

StrArr StrArr::operator- (const StrArr& obj)
{
    StrArr temp;
    if(this->arr == obj.arr) return temp;
    int counter = 0;
    for(int i = 0; i < size; ++i)
    {
        counter = 0;
        for(int k = 0; k < obj.getSize(); ++k)
        {
            if(!(arr[i] == &obj.arr[k])) ++counter;
        }
        if(counter == obj.getSize())
        {
            temp.addStr(&arr[i]);
        }
    }
    temp.sort();
    return temp;
}

StrArr StrArr::operator* (const StrArr& obj)
{
    StrArr temp;
    int counter = 0;
    for(int i = 0; i < size; ++i)
    {
        counter = 0;
        for(int k = 0; k < obj.getSize(); ++k)
        {
            if(!(arr[i] == &obj.arr[k])) ++counter;
        }
        if(counter != obj.getSize())
        {
            temp.addStr(&arr[i]);
        }
    }
    temp.sort();
    return temp;
}

void StrArr::operator =(const StrArr& obj)
{
    if(this->arr == obj.arr) return;
    delete[] arr;
    int newSize  = obj.getSize();
    this->size = 0;
    this->buffSize = newSize;
    arr = new String [buffSize];
    for(int i = 0; i < newSize; ++i)
    {
        this->addStr(obj.getStr(i));
    }
}

String& StrArr::operator[] (int place) const
{
    assert(place < size && place >= 0);
    return arr[place];
}

#endif // STRCLASS
