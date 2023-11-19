#include <iostream>
using namespace std;

void add(int A[4][4], int B[4][4], int C[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void sub(int A[4][4], int B[4][4], int C[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void mul(int A[4][4], int B[4][4], int C[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////
int main() {
    int A[4][4] = {{9, 9, 9, 9}, {7, 7, 7, 7}, {5, 5, 5, 5}, {3, 3, 3, 3}};
    int B[4][4] = {{1, 3, 5, 7}, {0, 2, 4, 6}, {9, 11, 13, 15}, {8, 10, 12, 14}};
    int C[4][4];

    
    add(A, B, C);
    cout << "Add is :" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    
    sub(A, B, C);
    cout << "Sub is :" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    mul(A, B, C);
    cout << "mul is :" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}