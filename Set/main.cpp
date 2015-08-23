#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;
const int length = 20;
const int beginSize = 20;
const int growFact = 2;
const int startSize = 1;

class IObject
{
public:
    virtual ~IObject() {}
    virtual bool less(IObject *) = 0;
    virtual bool equal(IObject *) = 0;
    virtual IObject *clone() = 0;
    virtual void show() = 0;
};

class IntObject:public IObject
{
public:
    IntObject(){ value = 0; }
    IntObject(int val) { value = val; }
    ~IntObject() {}
    int getValue() { return value; }
    bool less(IObject *obj);
    bool equal(IObject *obj);
    IObject *clone();
    void show();
private:
    int value;
};

bool IntObject::less(IObject *obj)
{
    IntObject *v = dynamic_cast<IntObject*>(obj);
    if(this->value < v->getValue()) return true;
    else return false;
}

bool IntObject::equal(IObject *obj)
{
    IntObject *v = dynamic_cast<IntObject*>(obj);
    if(this->value == v->getValue()) return true;
    else return false;
}

IObject *IntObject::clone()
{
    IntObject *copy = new IntObject(value);
    return copy;
}

void IntObject::show()
{
    cout<<this->value<<endl;
}

class StringObject:public IObject
{
public:
    StringObject() { value = new char[length]; }
    StringObject(char *toGet)
    {
        value = new char[length];
        strcpy(value,toGet);
    }
    ~StringObject();
    char *getStr() { return value; }
    bool less(IObject *obj);
    bool equal(IObject *obj);
    IObject *clone();
    void show();
private:
    char *value;
};

StringObject::~StringObject()
{
    delete[] value;
}

bool StringObject::less(IObject *obj)
{
    StringObject *temp = dynamic_cast<StringObject*>(obj);
    if(this->equal(obj)) return false;
    int min = strlen(value);
    if((int)strlen(temp->getStr()) < min) min = strlen(temp->getStr());
    char *checkThis = this->getStr();
    char *checkObj = temp->getStr();
    int count = 0;
    for(count = 0; count < min; ++count)
    {
        if(checkThis[count] > checkObj[count]) return false;
        else if(checkThis[count] < checkObj[count]) return true;
    }
    if(count == (int)strlen(value)) return true;
    else return false;
}

bool StringObject::equal(IObject *obj)
{
    StringObject *temp = dynamic_cast<StringObject*>(obj);
    if((strcmp(this->value, temp->getStr())) == 0) return true;
    else return false;
}

IObject *StringObject::clone()
{
    StringObject *temp = new StringObject(value);
    return temp;
}

void StringObject::show()
{
    cout<<this->getStr()<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

class Set
{
public:
    Set();
    Set(int siz);
    Set(const Set &obj);
    ~Set();
    int getSize() const { return size;}
    IObject *getElem(int pos) const;
    void addObj(IObject *obj);
    void delObj(IObject *obj);
    int searchObj(IObject *obj);

    bool isPart(IObject *obj);
    Set *setUnion(Set &obj);
    Set *setIntersection(Set &obj);
    Set *setComplement(Set &obj);
    void show();
private:
    IObject **arr;
    int size;
    int buffSize;
    void grow();
};

Set::Set()
{
    size = 0;
    buffSize =  startSize;
    arr = new IObject*[buffSize];
}

Set::Set(int siz)
{
    buffSize = size = siz;
    arr = new IObject*[size];
}

Set::Set(const Set &obj)
{
    this->size = obj.getSize();
    buffSize = size;
    arr = new IObject*[size];
    for(int i = 0; i < size; ++i)
    {
        arr[i] = obj.getElem(i);
    }
}

Set::~Set()
{
    cout<<"deleted"<<endl;
    for(int i = 0; i < size; ++i)
    {
        delete arr[i];
    }
    delete[] arr;
}


IObject *Set::getElem(int pos) const
{
    return arr[pos];
}

void Set::addObj(IObject *obj)
{
    if(size == buffSize) grow();
    int place = searchObj(obj);
    size+=1;
    IObject **temp = new IObject*[size];
    for(int i = 0; i < place; ++i)
    {
        temp[i] = arr[i]->clone();
    }
    temp[place] = obj->clone();
    for(int i = place+1; i < size; ++i)
    {
        temp[i] = arr[i-1]->clone();
    }
    for(int i = 0; i < size - 1; i++) 
    {
        delete arr[i];
    }
    delete[] arr;
    arr = temp;
}


void Set::delObj(IObject *obj)
{
    if(!this->isPart(obj))
    {
        cout<<"no such object"<<endl;
        return;
    }
    else
    {
        int place = (this->searchObj(obj))-1;
        cout<<place<<endl;
        --size;
        IObject **temp = new IObject*[size];
        for(int i = 0;i < place ; ++i)
        {
            temp[i] = arr[i];
        }
        for(int i = place+1;i < size ; ++i)
        {
            temp[i-1] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
}

void Set::grow()
{
    buffSize = size*growFact;
    IObject **temp = new IObject*[buffSize];
    for(int  i = 0; i< size; ++i)
    {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
}

int Set::searchObj(IObject *obj)
{
    if(this->size == 0) return 0;
    int mid = 0;
    int left = 0;
    int right = size;
    while(left < right)
    {
        mid = (left + right)/2;
        if(!obj->less(arr[mid])) left = mid+1;
        else right = mid;
    }
    return right;
}

bool Set::isPart(IObject *obj)
{
    int place = searchObj(obj)-1;
    if(place < 0 || place >= size)place = 0;
    if(obj->equal(arr[place])) return true;
    else return false;
}

void Set::show()
{
    cout<<"--------------------------------------------"<<endl;
    for(int i = 0; i < size; ++i)
    {
        cout<<i<<". ";
        arr[i]->show();
    }
    cout<<"--------------------------------------------"<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Set *Set::setUnion(Set &obj)
{
    Set *temp = new Set;
    for(int i = 0; i < size; ++i)
    {
        temp->addObj(arr[i]);
    }
    for(int k = 0; k < obj.getSize(); ++k)
    {
        if(!(this->isPart(obj.getElem(k))))
        temp->addObj(obj.getElem(k));
    }
    return temp;
}

Set *Set::setIntersection(Set &obj)
{
    Set *fin = new Set;
    for(int i = 0; i < size ; ++i)
    {
        if(obj.isPart(arr[i])) fin->addObj(arr[i]);
    }
    return fin;
}

Set *Set::setComplement(Set &obj)
{
    Set *fin = new Set;
    for(int i = 0; i < size; ++i)
    {
        if(!(obj.isPart(arr[i]))) fin->addObj(arr[i]);
    }
    return fin;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Set *toGetStr(ifstream &file)
{
    Set *temp = new Set;
    char** enterArr = new char* [beginSize];
    StringObject *strArr[beginSize];
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
            strArr[cntr] = new StringObject(enterArr[cntr]);
            temp->addObj(strArr[cntr]);
            ++cntr;
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

Set *toGetInt(ifstream &file)
{
    Set *temp = new Set;
    int *enterArr = new int[beginSize];
    IntObject *intArr[beginSize];
    if (!file.is_open()) cout << "Файл не может быть открыт!\n";
    else
    {
        int cntr = 0;
        while(!file.eof())
        {
            file >> enterArr[cntr];
            intArr[cntr] = new IntObject(enterArr[cntr]);
            temp->addObj(intArr[cntr]);
            ++cntr;
        }
    }
    file.close();
    delete[] enterArr;
    return temp ;
}

void menu(Set *firstInt, Set *secondInt, Set *firstStr, Set *secondStr)
{
    cout<<"------------------------------MENU------------------------------"<<endl;
    cout<<"--------------------------FIGURES-SET---------------------------"<<endl;
    cout<<"1. Show sets"<<endl;
    cout<<"2. Create set union"<<endl;
    cout<<"3. Create set intersection"<<endl;
    cout<<"4. Ceate set copmlement"<<endl;
    cout<<"--------------------------STRINGS-SET---------------------------"<<endl;
    cout<<"5. Show sets"<<endl;
    cout<<"6. Create set union"<<endl;
    cout<<"7. Create set intersection"<<endl;
    cout<<"8. Ceate set copmlement"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"9. EXIT"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"Please enter your destination\t";
    int target = 0;
    int toAct = 0;
    cin >> target;
    if(target == 9) return;
    if((int)target < 1 || (int)target > 10 )
    {
        cout<<"-------------!!!no such destination!!!-------------"<<endl;
        return;
    }
    if(target == 4 || target == 8)
    {
        cout<<"Please enter a set(1/2)\t";
        cin >> toAct;
        if((toAct != 1) && (toAct != 2))
        {
            cout<<"No such set"<<endl;
            return;
        }
    }
    switch(target)
    {
        case 1:
        {
            firstInt->show();
            secondInt->show();
            break;
        }
        case 2:
        {
            Set *intUnion = firstInt->setUnion(*secondInt);
            intUnion->show();
            delete intUnion;
            break;
        }
        case 3:
        {
            Set *intIntersect = firstInt->setIntersection(*secondInt);
            intIntersect->show();
            delete intIntersect;
            break;
        }
        case 4:
        {
            if(toAct == 1)
            {
                Set *complInt = firstInt->setComplement(*secondInt);
                complInt->show();
                delete complInt;
            }
            else
            {
                Set *complInt = secondInt->setComplement(*firstInt);
                complInt->show();
                delete complInt;
            }
            break;
        }
        case 5:
        {
            firstStr->show();
            secondStr->show();
            break;
        }
        case 6:
        {
            Set *strUnion = firstStr->setUnion(*secondStr);
            strUnion->show();
            delete strUnion;
            break;
        }
        case 7:
        {
            Set *strIntersect = firstStr->setIntersection(*secondStr);
            strIntersect->show();
            delete strIntersect;
            break;
        }
        case 8:
        {
            if(toAct == 1)
            {
                Set *complStr = firstStr->setComplement(*secondStr);
                complStr->show();
                delete complStr;
            }
            else
            {
                Set *complStr = secondStr->setComplement(*firstStr);
                complStr->show();
                delete complStr;
            }
            break;
        }
        default:
        {
            cout<<"-------------no such destination-----------"<<endl;
            break;
        }
    }
    cout<<"Show the menu again?(y/n)\t";
    char ans;
    cin >> ans;
    if(ans == 'y')
    {
        menu(firstInt, secondInt, firstStr, secondStr);
    }
    else return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    system("clear");
    ifstream file1("/home/alex/QtProjects/build-Set-Desktop-Debug/file.txt");
    ifstream file2("/home/alex/QtProjects/build-Set-Desktop-Debug/file1.txt");
    Set *firstStr = toGetStr(file1);
    Set *secondStr = toGetStr(file2);
    ifstream file3("/home/alex/QtProjects/build-Set-Desktop-Debug/file2.txt");
    ifstream file4("/home/alex/QtProjects/build-Set-Desktop-Debug/file3.txt");
    Set *firstInt = toGetInt(file3);
    Set *secondInt = toGetInt(file4);
    menu(firstInt, secondInt, firstStr, secondStr);
    cout<<"1st string SET ";
    delete firstStr;
    cout<<"2nd string SET ";
    delete secondStr;
    cout<<"1st int SET ";
    delete firstInt;
    cout<<"2nd int SET ";
    delete secondInt;
    return 0;
}

