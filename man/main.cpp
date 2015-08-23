#include <iostream>

using namespace std;
class Man
{
public:
    string name;
    int age;
    int height;
};

int main()
{
    cout << "enter a number of men"<<endl;
    int n=0;
    cin>>n;
    Man* Arr= new Man [n];
    for(int i=0; i<n; ++i)
    {
        cout<<"enter "<<i+1<<" name"<<endl;
        cin>>Arr[i].name;
        cout<<"enter "<<i+1<<" age"<<endl;
        cin>>Arr[i].age;
        cout<<"enter "<<i+1<<" height"<<endl;
        cin>>Arr[i].height;
    }

    for(int i=1;i<n;i++)
    {
        for(int k=i;0<k;--k)
        {
        if(Arr[k-1].height<Arr[k].height) swap(Arr[k-1],Arr[k]);
        }
    }

    for(int i=0;i<n;++i)
    {
        cout<<Arr[i].height<<" "<<Arr[i].name<<" "<<Arr[i].age<<endl;
    }
    return 0;
}

