using namespace std;
#include <mystring_class.h>
#include <stringset_class.h>

StrArr toGet(ifstream &file)
{
    StrArr temp;
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
            file.getline(enterArr[cntr++], length);
        }
        String* strArr = new String [cntr];
        for(int i = 0; i < cntr; ++i)
        {
            strArr[i] = new String(enterArr[i]);
            temp.addStr(&strArr[i]);
        }
        delete[] strArr;
    }
    file.close();
    for(int i = 0; i < beginSize ; ++i)
    {
        delete[] enterArr[i];
    }
    delete[] enterArr;
    temp.sort();
    return temp ;
}

StrArr symmethricDiff (StrArr& first, StrArr& second)
{
    StrArr sum;
    sum = first + second;
    StrArr differ;
    differ = first * second;
    StrArr temp;
    temp = sum - differ;
    temp.sort();
    return temp;
}

ostream& operator<< (ostream& stream, StrArr& toShow)
{
    stream<<"---------------------------------------------------"<<endl;
    for(int i = 0; i < toShow.getSize() ; ++i)
    {
        stream << i+1<<". ";
        toShow[i].show();
        stream << endl;
    }
    stream<<"---------------------------------------------------"<<endl;
    return stream;
}

ostream& operator<< (ostream& stream, String& toShow)
{
    stream << "---------------------------------------------------" << endl;
    toShow.show();
    cout << endl;
    stream << "---------------------------------------------------" << endl;
    return stream;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

void menu(StrArr& first, StrArr& second)
{
    system("clear");
    cout<<"------------------------------MENU------------------------------"<<endl;
    cout<<"1. Show arrays"<<endl;
    cout<<"2. Addition"<<endl;
    cout<<"3. Subtraction"<<endl;
    cout<<"4. Intersection"<<endl;
    cout<<"5. Symmetric difference"<<endl;
    cout<<"6. Show element in first array"<<endl;
    cout<<"7. Change element in first array"<<endl;
    cout<<"8. Exit"<<endl;
    cout<<"Please enter your destination\t";
    int target = 0;
    int toAct = 0;
    cin >> target;
    if((int)target < 0 || (int)target > 8 )
    {
        cout<<"-------------!!!no such directory!!!-------------"<<endl;
        return;
    }
    if(target == 8) return;
    if(target == 6 || target == 7)
    {
        cout<<"Enter an element place - from 1 to "<< first.getSize()<<"\t"<<endl;
        cin >> toAct;
        if(toAct >= first.getSize())
        {
            cout<<"No such element"<<endl;
            return;
        }
    }
    switch(target)
    {
    case 1:
    {
        cout << first;
        cout << second;
        break;
    }
    case 2:
    {
        StrArr addition;
        addition = first + second;
        cout << addition;
        break;
    }
    case 3:
    {
        StrArr substraction;
        substraction = first - second;
        cout << substraction;
        break;
    }
    case 4:
    {
        StrArr intersect;
        intersect = first * second;
        cout << intersect;
        break;
    }
    case 5:
    {
        StrArr symmDiffer;
        symmDiffer = symmethricDiff(first, second);
        cout << symmDiffer;
        break;
    }
    case 6:
    {
        cout << first[toAct];
        break;
    }
    case 7:
    {
        cin.ignore();
        char* enter = new char[length];
        cin.getline(enter, length);
        String* temp = new String(enter);
        first[toAct-1] = temp;
        first.show();
        break;
    }
    default:
    {
        cout<<"-------------no such directory-----------"<<endl;
        break;
    }
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

