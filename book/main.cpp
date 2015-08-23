#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>


const int size = 30;
using namespace std;

class book
{
public:
    book();
    ~book();
    book(const book &obj);

    char *getAuthor() const { return author; }
    void setAuthor(char *auth) { author = auth; }

    char *getTitle() const { return title; }
    void setTitle(char *tit) { title = tit; }

    char *getPublisher() const { return publisher; }
    void setPublisher(char *publ) { publisher = publ; }

    int getYear() const { return year; }
    void setYear(int yearOfPubl) { year = yearOfPubl; }

    int getNumOfPages() const { return numOfPages; }
    void setNumOfPages(int numPages) { numOfPages = numPages; }

    void show();

private:
    char *author;
    char *title;
    char *publisher;
    int year;
    int numOfPages;
};

book::book()
{
    author = new char[size];
    title = new char[size];
    publisher = new char[size];
    year = 0;
    numOfPages = 0;
}

book::~book()
{
    delete[] author;
    delete[] title;
    delete[] publisher;
    cout<<"book deleted"<<endl;
}

book::book(const book &obj)
{
    author = new char[size];
    title = new char[size];
    publisher = new char[size];
    strcpy (author, obj.getAuthor());
    strcpy (title, obj.getTitle());
    strcpy (publisher, obj.getPublisher());
    year = obj.getYear();
    numOfPages = obj.getNumOfPages();
}

void book::show()
{
    cout<<"------------------------------------------------"<<endl;
    cout<<"Author\t\t"<<this->getAuthor()<<endl;
    cout<<"Title\t\t"<<this->getTitle()<<endl;
    cout<<"Publisher\t"<<this->getPublisher()<<endl;
    cout<<"Year\t\t"<<this->getYear()<<endl;
    cout<<"Pages\t\t"<<this->getNumOfPages()<<endl;
    cout<<"------------------------------------------------"<<endl;
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void findAuthor(book *array[], int arrSize)
{
    char *quest = new char[size];
    cout<<"Enter an author\t"<<endl;
    cin.ignore();
    cin.getline(quest, size);
    if(strlen(quest) == 0) return;
    char *temp_from = new char[size];
    for(int i=0; i < arrSize; i++)
    {
        temp_from = array[i]->getAuthor();
        int countr = 0;
        for(int k = 0; k < (int)strlen(quest); ++k){
           if(temp_from[k] == quest[k]) countr++;
        }
        if(countr == (int)strlen(quest))array[i]->show();
    }
    delete[] quest;
}

void findPublisher(book *array[],int arrSize)
{
    int size2find = 0;
    char *quest = new char[size];
    cout<<"Enter a publisher\t"<<endl;
    cin.ignore();
    cin.getline(quest, size);
    if(strlen(quest) == 0) return;
    char *temp_from = new char[size2find];
    for(int i=0; i < arrSize;i++)
    {
        temp_from = array[i]->getPublisher();
        int countr = 0;
        for(int k=0; k < (int)strlen(quest); ++k){
           if(temp_from[k] == quest[k]) countr++;
        }
        if(countr == (int)strlen(quest)) array[i]->show();
    }
    delete quest;
    return;
}

void findYear(book *array[],int arrSize)
{
    int year2find =0;
    cout<<"Enter a year"<<endl;
    cin>>year2find;
    for(int i=0; i < arrSize;++i){
        if(year2find == array[i]->getYear()) array[i]->show();
    }
    return;
}

void printAll(book *array[],int arrSize)
{
    for(int i = 0; i < arrSize; ++i){
        array[i]->show();
    }
    return;
}

void menu(book *array[], int arrSize)
{
    cout<<"-------------------------MENU-------------------------"<<endl;
    cout<<"1. Find books of the particular author"<<endl;
    cout<<"2. Find books by publication year"<<endl;
    cout<<"3. Find books by its publishing house"<<endl;
    cout<<"4. Show all the books"<<endl;
    cout<<"5. Exit (delete all сopies)"<<endl;
    cout<<"Enter your action :\t";
    int action = 0;
    cin >> action;
    if ((int)action<  0 || (int)action > 9) return;
    switch (action)
    {
        case 1:
        {
            findAuthor(array, arrSize);
            cout<<"Show menu again? (y/n)\t";
            char ans;
            cin >> ans;
            if(ans=='y')
            {
                menu(array, arrSize);
                return;
            }
            else return;
        }
        case 2:
        {
            findYear(array, arrSize);
            cout<<"Show menu again? (y/n)\t";
            char ans;
            cin >> ans;
            if(ans=='y')
            {
                menu(array, arrSize);
                return;
            }
            else return;
        }
        case 3:
        {
            findPublisher(array, arrSize);
            cout<<"Show menu again? (y/n)\t";
            char ans;
            cin >> ans;
            if(ans=='y')
            {
                menu(array, arrSize);
                return;
            }
            else return;
        }
        case 4:
        {
            printAll(array, arrSize);
            cout<<"Show menu again? (y/n)\t";
            char ans;
            cin >> ans;
            if(ans=='y')
            {
                menu(array, arrSize);
                return;
            }
            else return;
        }
        case 5:
        {
            return;
        }
        default:
        {
            cout<<endl;
            cout<<"!!!!!no such directory!!!!!"<<endl;
            return;
        }
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

int main()
{
    system("clear");
    const int quantOfBooks = 7;
    const int grFact = 3;
    const int sizeOfArr = 5*quantOfBooks;
    book *bookArr[quantOfBooks];
    char **buff_ch = new char*[sizeOfArr];
    for(int i = 0; i < sizeOfArr; i++)
    {
        buff_ch[i] = new char[size];
    }
    int buff=0;
    ifstream toRead("/home/alex/Загрузки/file.txt");
    if (!toRead.is_open()) cout << "Файл не может быть открыт!\n";
    else
    {
        for(int sub=0; sub < (quantOfBooks-1)*grFact;)
        {
            for(int cntr=0; cntr < (quantOfBooks-1); ++cntr)
            {
                bookArr[cntr] = new book;

                toRead.getline(buff_ch[sub],size);
                bookArr[cntr]->setAuthor(buff_ch[sub]);
                sub+=1;

                toRead.getline(buff_ch[sub],size);
                bookArr[cntr]->setTitle(buff_ch[sub]);
                sub+=1;

                toRead.getline(buff_ch[sub],size);
                bookArr[cntr]->setPublisher(buff_ch[sub]);
                sub+=1;

                toRead >> buff;
                toRead.getline(buff_ch[sub],size);
                bookArr[cntr]->setYear(buff);
                sub+=1;

                toRead >> buff;
                toRead.getline(buff_ch[sub],size);
                bookArr[cntr]->setNumOfPages(buff);
                sub+=1;
            }
        }
    }
    toRead.close();
    bookArr[quantOfBooks-1] = new book (*(bookArr[0]));
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
    menu(bookArr,quantOfBooks);
    cout<<endl;
    cout<<"-------------------------EXIT-------------------------"<<endl;
    for(int i = 0 ; i < quantOfBooks; ++i)
    {
        delete bookArr[i];
    }
    delete[] buff_ch;
    return 0;
}

