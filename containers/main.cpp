#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int getNext(int i, int n) {
    if((i + 1) == n) {
        return 0;
    } else 
        return (i + 1);
}

int main()
{
    int n = 0;
    cin >> n;
    vector< stack<int> > position(n, stack<int>());
    int bad = 1; //кол-во испорченных столбцов
    
    int k = 0;
    int number = 0;
    for(int i = 0; i < n; i++) {
        cin >> k;
        for(int j = 0; j < k; j++) {
            cin >> number;
            position[i].push(number);
        }
    }
    //перекидываем всё на первую:
    for(int i = 1; i < n; i++) {
        while(!position[i].empty()) {
            position[0].push(position[i].top());
            position[i].pop();
            cout << (i + 1) << " " << 1 << endl;
        }
    }
    
    int col = 0; //текущая стопка
    while(bad != 0) {
        int iters = position[col].size();
        for(int i = 0; i < iters; i++) {
            int current = position[col].top();
            position[col].pop();
            if(current == (col + 1)) {
                if((i + 1) == iters) {
                    position[col].push(current);
                    break;
                }
                int next = getNext(current - 1, n);
                position[next].push(current);
                bad++;
                /*if(bad == n) {
                    cout << "It's too complex to me ;(" << endl;
                    return 0;
                }*/
                cout << (col + 1) << " " << (next + 1) << endl;
            } else {
                position[current - 1].push(current);
                cout << (col + 1) << " " << current << endl;
            }    
        }
        bad--;
        col = getNext(col, n);
    }
    return 0;
}

