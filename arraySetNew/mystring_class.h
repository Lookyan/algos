#ifndef STRINGCLASS
#define STRINGCLASS
#include <string>
#include <cstring>

const int beginStrSize = 20;
class String
{
public:
    String();
    String(int size);
    String(char* toMake);
    String(const String * );
    ~String();
    void show();
    int getLen() { return strSize; }
    char getElem(int posit) { return string[posit]; }
    void operator= (const String* obj);
    bool operator== (const String* obj);
private:
    char* string;
    int strSize;
};

String::String()
{
    strSize = beginStrSize;
    string = new char[strSize];
}

String::String(int size)
{
    strSize = size;
    string = new char[strSize];
}

String::String(char* toMake)
{
    strSize = strlen(toMake);
    string = new char[strSize];
    for(int i = 0; i < strSize; ++i)
    {
        string[i] = toMake[i];
    }
}

String::String(const String* obj)
{
    if(this->string == obj->string) return;
    strSize = obj->strSize;
    string = new char[strSize];
    for(int i = 0; i < strSize; ++i)
    {
        string[i] = obj->string[i];
    }
}

String::~String()
{
    delete[] string;
}

void String::show()
{
    for(int i = 0; i < strSize; ++i)
    {
        std::cout << string[i];
    }
}

void String::operator= (const String* obj)
{
    if(this->string == obj->string) return;
    delete string;
    strSize = obj->strSize;
    string = new char[strSize];
    for(int i = 0; i < strSize; ++i)
    {
        string[i] = obj->string[i];
    }
}


bool String::operator== (const String* obj)
{
    if(this->strSize != obj->strSize) return false;
    else
    {
        for(int i = 0; i < strSize; ++i)
        {
            if(string[i] != obj->string[i]) return false;
        }
        return true;
    }
}

#endif // STRINGCLASS
