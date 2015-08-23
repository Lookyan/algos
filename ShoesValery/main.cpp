#include <iostream>
#include <algorithm>
 
using namespace std;
 
int main()
{
    int customSize = 0;
    int numOfShoes = 0;
    cin >> customSize >> numOfShoes;
    if(customSize > 100 || numOfShoes > 1000) return 0;
    int* shoesArr = new int[numOfShoes];
    int cntr = 0;
    while( cntr != numOfShoes)
    {
        cin >> shoesArr[cntr++];
    }
    
    sort(shoesArr, shoesArr + numOfShoes);
    
    const int differ = 3;
    int toPropose = 0;
    int minSize = customSize;
    for(int i = 0; i < numOfShoes; ++i)
    {
        if(minSize <= shoesArr[i])
        {
            ++toPropose;
            minSize = shoesArr[i] + differ;
        }
    }
    cout << toPropose << endl;
    return 0;
}
