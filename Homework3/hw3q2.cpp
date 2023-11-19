#include <iostream>
using namespace std;

const int N = 4;


void taranahade(int A[N][N], int B[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = A[j][i];
        }
    }
}

int main() {
    int A[N][N] = {{0,0,0,0},
                   {0,0,0,0},
                   {1,1,0,0},
                   {0,0,0,0}};
    
    int taranahadeA[N][N];

     taranahade(A, taranahadeA);

    cout << "Taranahade A:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << taranahadeA[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}