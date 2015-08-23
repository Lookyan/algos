#include <iostream>

using namespace std;

int main()
{
    int n=0, m=0, k=0;
    cout<<"Enter size of matrix1 m and n (m*n)"<<endl;
    cin>>m>>n;
    cout<<"Enter size of k for matrix2(n*k) "<<endl;
    cin>>k;
    int arr1[m][n];
    int arr2[n][k];
    int arr3[m][k];
    cout<<"now enrter rows for 1st matrix"<<endl;
    for(int i=0; i<m; i++)
    {
        cout<<"it's "<<i+1<<" row - number of elements is "<<m<<endl;
        for(int l=0; l<n; l++)
        {
            cin>>arr1[i][l];
        }
    }
    cout<<"now enrter rows for 2nd matrix"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"it's "<<i+1<<" row - number of elements is "<<n<<" row"<<endl;
        for(int l=0; l<k; l++)
        {
            cin>>arr2[i][l];
        }
    }


    int sum=0;
    for(int a=0;a<m;a++)
    {
        for(int b=0;b<k;b++)
        {
              sum=0;
                for(int d=0;d<n;d++)
                {
                   sum+=arr1[a][d]*arr2[d][b];
                }
                arr3[a][b]=sum;

        }
    }

cout<<"here the final matrix"<<endl;
    for(int i=0;i<m;i++)
    {
        for(int l=0;l<k;l++)
        {
            cout<<arr3[i][l]<<" ";
        }
        cout<<endl;
    }
    return 0;
}

