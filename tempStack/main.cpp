#include <iostream>
#include <tempstack.h>
#include <stdlib.h>

using namespace std;

void menu(Stack<int>* intArr, Stack<char>* charArr)
{
    system("clear");
    cout<<"------------------------------MENU------------------------------"<<endl;
    cout<<"1. Show arrays"<<endl;
    cout<<"2. Addition (~concatenation)"<<endl;
    cout<<"3. Subctraction (first - second)"<<endl;
    cout<<"4. Assignment (first = second)"<<endl;
    cout<<"5. Delete odds (in first array)"<<endl;
    cout<<"6. EXIT"<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"Please enter your destination\t";
    int target = 0;
    int toAct = 0;
    cin >> target;
    if(target == 6) return;
    if((int)target < 1 || (int)target > 6 )
    {
        cout<<"-------------!!!no such destination!!!-------------"<<endl;
        return;
    }
    if(target < 6)
    {
        cout<<"Work with 1 - ints/ 2 - chars\t";
        cin >> toAct;
        if((toAct != 1) && (toAct != 2))
        {
            cout<<"No such data type"<<endl;
            return;
        }
    }
    switch(target)
    {
        case 1:
        {
            if(toAct == 1)
            {
                cout << intArr[0] <<endl;
                cout << intArr[1] <<endl;
            }
            else
            {
                cout << charArr[0] <<endl;
                cout << charArr[1] <<endl;
            }
            break;
        }
        case 2:
        {
            if(toAct == 1)
            {
                Stack <int> sum;
                sum = intArr[0] + intArr[1];
                cout << sum << endl;
            }
            else
            {
                Stack<char> sum;
                sum = charArr[0] + charArr[1];
                cout << sum <<endl;
            }
            break;
        }
        case 3:
        {
            if(toAct == 1)
            {
                Stack<int> substraction;
                substraction = intArr[0] - intArr[1];
                cout << substraction <<endl;
            }
            else
            {
                Stack<char> substraction;
                substraction = charArr[0] - charArr[1];
                cout << substraction <<endl;
            }
            break;
        }
        case 4:
        {
            if(toAct == 1)
            {
                intArr[0] = intArr[1];
                cout << intArr[0] <<endl;
            }
            else
            {
                charArr[0] = charArr[1];
                cout << charArr[0] <<endl;
            }
            break;
        }
        case 5:
        {
            if(toAct == 1)
            {
                deleteOdds(intArr[0]);
                cout << intArr[0] <<endl;
            }
            else
            {
                deleteOdds(charArr[0]);
                cout << charArr[0] <<endl;
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
        menu(intArr, charArr);
    }
    else return;
}

int main()
{
    Stack<int> firstInt;
    firstInt.push(1);
    firstInt.push(2);
    firstInt.push(3);
    firstInt.push(4);
    firstInt.push(5);
    Stack<int> secondInt;
    secondInt.push(6);
    secondInt.push(7);
    secondInt.push(8);
    secondInt.push(9);
    secondInt.push(10);
    Stack<char> firstChar;
    firstChar.push('a');
    firstChar.push('l');
    firstChar.push('e');
    firstChar.push('x');
    firstChar.push('a');
    firstChar.push('n');
    firstChar.push('d');
    firstChar.push('r');
    Stack<char> secondChar;
    secondChar.push('v');
    secondChar.push('a');
    secondChar.push('l');
    secondChar.push('e');
    secondChar.push('r');
    secondChar.push('y');
    Stack<int>* intArr = new Stack<int>[2];
    intArr[0] = firstInt;
    intArr[1] = secondInt;
    Stack<char>* charArr = new Stack<char>[2];
    charArr[0] = firstChar;
    charArr[1] = secondChar;
    menu(intArr, charArr);
    delete[] intArr;
    delete[] charArr;
    return 0;
}

