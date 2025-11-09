#include<iostream>
#include<cmath>
using namespace std;

void print(int board[][9], int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(int board[][9], int row, int col, int val, int n) {
    for (int i = 0; i < n; i++) {
        if (board[row][i] == val)
            return false;
        if (board[i][col] == val)
            return false;
    }
    int rn = sqrt(n);
    int si = row - row % rn;
    int sj = col - col % rn;

    for (int i = si; i < si + rn; i++) {
        for (int j = sj; j < sj + rn; j++) {
            if (board[i][j] == val)
                return false;
        }
    }
    return true;
}

bool sudokuSolver(int board[][9], int row, int col, int n) {
    
    if (row == n) {
        print(board, n);
        return true;
    }

    
    if (col == n) {
        return sudokuSolver(board, row + 1, 0, n);
    }

    
    if (board[row][col] != 0) {
        return sudokuSolver(board, row, col + 1, n);
    }

    
    for (int val = 1; val <= 9; val++) {
        if (isSafe(board, row, col, val, n)) {
            board[row][col] = val;
            bool solved = sudokuSolver(board, row, col + 1, n);
            if (solved) {
                return true;
            } else {
                board[row][col] = 0; 
            }
        }
    }

    return false;
}

int main() {
    int n = 9;
    int board[9][9] = {
        {0,0,7,1,0,0,0,6,0},
        {1,0,5,2,0,8,0,0,0},
        {6,0,0,0,0,7,1,2,0},
        {3,1,2,4,0,5,0,0,8},
        {0,0,6,0,9,0,2,0,0},
        {0,0,0,0,0,3,0,0,1},
        {0,0,1,0,0,4,9,8,6},
        {8,0,3,9,0,6,0,0,0},
        {0,6,0,0,8,2,7,0,3}
    };

    if (!sudokuSolver(board, 0, 0, n)) {
        cout << "No solution exists!" << endl;
    } else {
        cout << "Sudoku is solved successfully!" << endl;
    }

    return 0;
}
