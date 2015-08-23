#include <iostream>

using namespace std;
const int startSize = 1;

class Deque
{
public:
    Deque();
    Deque(const Deque&);
    ~Deque();
    void pushBack(int);
    void pushFront(int);
    int popBack();
    int popFront();
    void print();
private:
    int* arr;
    int size;
    int head;
    int tail;
    int buffSize;
    void grow();
};

Deque::Deque()
{
    buffSize = startSize;
    arr = new int[buffSize];
    size = head = tail = 0;
}

Deque::Deque(const Deque &obj)
{
    buffSize = size = obj.size;
    head = 0;
    tail = obj.size - 1;
    arr = new int[size];
    for(int i = 0; i < size; ++i)
    {
        arr[i] = obj.arr[i];
    }
}

Deque::~Deque()
{
    delete[] arr;
}

void Deque::grow()
{
    buffSize *= 2;
    int* temp = new int[buffSize];
    int cntr = 0;
    int beginer = head;
    while(cntr < size)
    {
        if(beginer >= size) beginer = 0;
        temp[cntr++] = arr[beginer++];
    }
    delete[] arr;
    head = 0;
    tail = size - 1;
    arr = temp;
}

void Deque::pushBack(int n)
{
    if(size == buffSize)
    {
        grow();
        ++tail;
    }
    else
    {
        if(size == 0 || (tail == buffSize && size < buffSize))
        {
            tail = 0;
        }
        else
        {
            ++tail;
        }
    }
    ++size;
    arr[tail] = n;
    return;
}

void Deque::pushFront(int n)
{
    if(size-1 == buffSize)
    {
        if(head == 0)
        {
            head = buffSize - 1;
        }
        else
        {
            --head;
        }
        arr[head] = n;
        ++size;
        grow();
        return;
    }
    else
    {
        if(size == 0 || (head == 0 && size < buffSize))
        {
            head = buffSize - 1;
        }
        else
        {
            --head;
        }
        arr[head] = n;
        ++size;
        return;
    }
}

int Deque::popFront()
{
    if(size == 0) return -1;
    else
    {
        if(head == buffSize)
        {
            --size;
            head = 0;
            return arr[head];
        }
        else
        {
            --size;
            return arr[head++];
        }
    }
}

int Deque::popBack()
{
    if(size == 0) return -1;
    else
    {
        if(tail == 0)
        {
            --size;
            tail = buffSize - 1;
            return arr[0];
        }
        else
        {
            --size;
            return arr[tail--];
        }
    }
}

void Deque::print()
{
    if(size == 0) cout <<"Deque is empty" <<endl;
    else
    {
        int start = head;
        while(start != tail+1)
        {
            if(start == buffSize) start = 0;
            cout <<" "<< arr[start];
            ++start;
        }
        cout << endl;
    }
}

int main()
{
    Deque mine;
    cout << "enter number of commands\t";
    int n = 0;
    cin >> n;
    int i = 0;
    int A[n];
    int B[n];
    while(i < n)
    {
        cout << "enter a\t";
        cin >> A[i];
        cout << "enter b\t";
        cin >> B[i++];
    }
    for(int k = 0; k < n; ++k)
    {
        switch(A[k])
        {
        case 1:
        {
            mine.pushFront(B[k]);
            break;
        }
        case 2:
        {
            int j = mine.popFront();
            if(j == B[k]) cout << "YES" <<endl;
            else cout <<"NO"<<endl;
        }
        case 3:
        {
            mine.pushBack(B[k]);
            break;
        }
        case 4:
        {
            int j = mine.popBack();
            if(j == B[k]) cout << "YES" <<endl;
            else cout <<"NO"<<endl;
        }
        }
    }
    return 0;
}

