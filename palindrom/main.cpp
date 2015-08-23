//#include <iostream>
//#include <cstring>

//using namespace std;

//const int size = 201;

//int main()
//{
//    char* str = new char[size];
//    cin >> str;
//    int length = strlen(str);
    
//    for(int i = 0; i < length / 2; ++i) {
//        if(str[i] != str[length - i - 1]) {
//            cout << "no";
//            delete[] str;
//            return 0;
//        }
//    }
    
//    cout << "yes";
    
//    delete[] str;
//    return 0;
//}

#include <iostream>

using namespace std;

int main()
{
    string toGet;
    getline(cin, toGet);
    for(int i = 0; i < toGet.length(); ++i)
    {
        if(toGet[i] != toGet[toGet.length()-i-1])
        {
            cout<<"no"<<endl;
            return 0;
        }
    }
    cout<<"yes"<<endl;
    return 0;
}

