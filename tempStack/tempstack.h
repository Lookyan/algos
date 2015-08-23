#ifndef TEMPSTACK
#define TEMPSTACK
#include "assert.h"

using namespace std;
const int growFactor = 2;
const int startSize = 1;

template <typename T>
class Stack
{
public:
    Stack();
    Stack(const Stack<T>&);
    ~Stack();
    void push(T toPush);
    void pop();
    T getTop();
    int getSize() const { return stackSize; }
    T getElement(int place) const;
    void showStack();
    Stack<T> operator +(Stack<T> &);
    Stack<T> operator -(Stack<T> &);
    void operator =(const Stack<T> &);
private:
    T* stackPntr;
    int stackSize;
    int buffSize;
    void grow();
};

template <typename T>
Stack<T>::Stack()
{
    stackSize = 0;
    buffSize = startSize;
    stackPntr = new T[buffSize];
}

template <typename T>
Stack<T>::Stack(const Stack<T> &toCopy)
{
    buffSize = stackSize = toCopy.getSize();
    stackPntr = new T[buffSize];
    for(int  i = 0; i < stackSize; ++i)
    {
        stackPntr[i] = toCopy.getElement(i);
    }
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] stackPntr;
}

template <typename T>
void Stack<T>::push(T toPush)
{
    if(stackSize == buffSize) grow();
    stackPntr[stackSize++] = toPush;
}

template <typename T>
void Stack<T>::pop()
{
    if(stackSize == 0) {
        cout<<"stack is empty"<<endl;
        return;
    }
    else
    {
        stackPntr[--stackSize] = 0;
    }
}

template <typename T>
T Stack<T>::getTop()
{
    if(stackSize == 0) return 0;
    return stackPntr[stackSize-1];
}

template <typename T>
T Stack<T>::getElement(int place) const
{
    assert(place < buffSize);
    return stackPntr[place];
}

template <typename T>
void Stack<T>::grow()
{
    buffSize = stackSize * growFactor;
    T* temp = new T[buffSize];
    for(int i = 0; i < stackSize; ++i)
    {
        temp[i] = stackPntr[i];
    }
    delete[] stackPntr;
    stackPntr = temp;
}

template <typename T>
void Stack<T>::showStack()
{
    cout<<"--------------------------------------"<<endl;
    for(int  i = 0; i < stackSize; ++i)
    {
        cout<<stackPntr[i];
    }
    cout<<endl;
    cout<<"--------------------------------------"<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Stack<T> Stack<T>::operator + ( Stack<T>& toAdd)
{
    Stack <T> sum;
    Stack <T>* thisTemp = new Stack<T>;
    int counter = 0;
    int size = this->getSize();
    while(counter < size)
    {
        thisTemp->push(this->getTop());
        this->pop();
        ++counter;
    }
    counter = 0;
    while(counter < size)
    {
        sum.push(thisTemp->getTop());
        this->push(thisTemp->getTop());
        thisTemp->pop();
        ++counter;
    }
    Stack <T>* toAddTemp = new Stack <T>;
    counter = 0;
    size = toAdd.getSize();
    while(counter < size)
    {
        toAddTemp->push(toAdd.getTop());
        toAdd.pop();
        ++counter;
    }
    counter = 0;
    while(counter < size)
    {
        sum.push(toAddTemp->getTop());
        toAdd.push(toAddTemp->getTop());
        toAddTemp->pop();
        ++counter;
    }
    delete thisTemp;
    delete toAddTemp;
    return sum;
}

template <typename T>
Stack<T> Stack<T>::operator - (Stack<T>& toSubsrtact)
{
    Stack <T>* cloneThis = new Stack<T>;
    Stack <T>* thisTemp = new Stack<T>;
    int substractSize = toSubsrtact.getSize();
    int thisSize = this->getSize() -1;
    bool del = false;
    for(int  i = thisSize; 0 <= i; --i)
    {
        del = false;
        for(int  k = 0; k < substractSize; ++k)
        {
            if(stackPntr[i] == toSubsrtact.getElement(k))
            {
                k = substractSize;
                del = true;
            }
        }
        if(del == false)
        {
            thisTemp->push(this->getTop());
            cloneThis->push(this->getTop());
            this->pop();
        }
        else
        {
            cloneThis->push(this->getTop());
            this->pop();
        }
    }
    for(int  i = thisSize; 0 <= i; --i)
    {
        this->push(cloneThis->getTop());
        cloneThis->pop();
    }
    Stack <T> substract;
    int counter = 0;
    int tempSize = thisTemp->getSize();
    while(counter <  tempSize)
    {
        substract.push(thisTemp->getTop());
        thisTemp->pop();
        ++counter;
    }
    delete thisTemp;
    delete cloneThis;
    return substract;
}

template <typename T>
void Stack<T>::operator =(const Stack<T>& toChange)
{
    this->stackSize = toChange.stackSize;
    this->buffSize = toChange.buffSize;
    delete[] stackPntr;
    this->stackPntr = new T[buffSize];
    for(int i = 0; i < toChange.buffSize; i++)
    {
        this->stackPntr[i] = toChange.getElement(i);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
ostream& operator<<(ostream& stream,const Stack<T>& toShow)
{
    int counter = toShow.getSize();
    for(int i = 0; i < counter; ++i)
    {
        stream << (T)toShow.getElement(i);
    }
    return stream;
}

template <typename T>
void deleteOdds(Stack<T>& toFormate)
{
    Stack<T> * temp = new Stack<T>;
    int counter = 0;
    int size = toFormate.getSize();
    while(counter < size)
    {
        toFormate.pop();
        ++counter;
        if(counter >= size) break;
        temp->push(toFormate.getTop());
        toFormate.pop();
        ++counter;
    }
    counter = 0;
    size = temp->getSize();
    while(counter < size)
    {
        toFormate.push(temp->getTop());
        temp->pop();
        ++counter;
    }
    delete temp;
}

#endif // TEMPSTACK
