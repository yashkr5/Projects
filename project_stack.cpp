#include <iostream>
#include <vector>
using namespace std;

class stack{
private:
    vector<int> v;
    int i;
    int max_size;

public:

    stack(int max_size){
        i = 0;
        this -> max_size = max_size;
        v = vector<int>(max_size);
        cout << "Stack initialised to size " << max_size << "." << endl;
    }

    void push(int n){
        if(i == max_size){
            cout << "Stack Overflow!" << endl << "Pop elements before pushing furthur." << endl;
            return;
        }
        v[i] = n;
        i++;
        cout << "Pushed " << n << " in the stack." << endl;
    }
    int size(){
        return i;
    }
    void pop(){
        if(i == 0){
            cout << "Stack is empty, can't pop." << endl;
            return;
        }
        i--;
    }
    int top(){
        if(i == 0){
            cout << "Stack is empty." << endl;
            return -1e8;
        }
        return v[i-1];
    }
};

int main()
{

    cout << "Enter maximum size of stack : ";
    int n; cin >> n;
    stack s(n);

    cout << "Enter number of queries : ";
    int q; cin >> q;

    cout << "Enter 1 {value} to push in stack" << endl;
    cout << "Enter 2 to get size of stack" << endl;
    cout << "Enter 3 to pop from stack" << endl;
    cout << "Enter 4 to get top element of the stack" << endl;

    while (q--)
    {
        int query; cin >> query;
        if(query == 1){
            int val; cin >> val;
            s.push(val);
        }
        else if(query == 2){
            cout << "Stack size : " << s.size() << endl;
        }
        else if(query == 3){
            s.pop();
        }
        else if(query == 4){
            cout << "Topmost element : " << s.top() << endl;
        }
        else{
            cout << "Invalid Input" << endl;
        }
    }
    

    return 0;
}

    