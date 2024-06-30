#include <bits/stdc++.h>
using namespace std;

class SudokuSolver {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
    bool solve(vector<vector<char>>& board){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] == '.'){
                    for(int ch = '1'; ch <= '9'; ch++){
                        if(isPossible(board,i,j,ch)){
                            board[i][j] = ch;
                            if(solve(board))    return true;
                            else board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    bool isPossible(vector<vector<char>> &board ,int i, int j, char ch){
        for(int k = 0; k < 9; k++){
            if(board[i][k] == ch)   return false;
            if(board[k][j] == ch)   return false;
            if(board[3*(i/3) + k/3][3*(j/3) + k%3] == ch)   return false;
        }
        return true;
    }
};

int main()
{
    SudokuSolver solver;

    cout << "Welcome to sudoku solver! " << endl;
    cout << "Enter grid in a continuous stream, a number to enter a number, and '.' to enter a blank space." << endl;
    cout << "Insert spaces in between all characters" << endl; 
    vector<vector<char>> board(9,vector<char>(9,'.'));

    bool flag = true;
    for (int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++){
            char temp;
            cin >> temp;
            board[i][j] = temp;

            if((temp > '9' || temp < '0') && temp != '.')   flag = false;
        }
    }
    cout << endl;
    solver.solve(board);

    //verification stage

    map <char,int> mpp;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if(board[i][j] > '9' || board[i][j] < '0')
                flag = false;
            mpp[board[i][j]]++;
        }
        
    }
    for(auto it : mpp){
        if(it.second != 9)  flag = false;
    }

    //printing phase
    
    if(flag){
        cout << "Board Solved." << endl;
        cout << endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++){
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        
    }
    else{
        cout << "Board is not solveable." << endl;
    }
    

    return 0;
}

    