#include <iostream>
#include <string>

using namespace std;

class Stud {
public:
    Stud() {
        name = "";
        val = 0;
    }
    void set(string name, int val) {
        this->name = name;
        this->val = val;
    }

private:
    string name;
    int val;
};

int main()
{
    
    return 0;
}

