#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void Create(int **a, const int ROW, const int COL, const int Low, const int High) {
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int **a, const int ROW, const int COL) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++)
            cout << setw(5) << a[i][j];
        cout << endl;
    }
}

void ChangeCols(int **a, const int ROW, int c1, int c2) {
    for (int i = 0; i < ROW; i++) {
        int tmp = a[i][c1];
        a[i][c1] = a[i][c2];
        a[i][c2] = tmp;
    }
}

void SortCols(int **a, const int ROW, const int COL) {
    for (int pass = 0; pass < COL - 1; pass++)
        for (int j = 0; j < COL - pass - 1; j++) {
            bool swapNeeded = false;
            if (a[0][j] > a[0][j + 1]) swapNeeded = true;
            else if (a[0][j] == a[0][j + 1]) {
                if (a[1][j] > a[1][j + 1]) swapNeeded = true;
                else if (a[1][j] == a[1][j + 1] && a[2][j] < a[2][j + 1]) swapNeeded = true;
            }
            if (swapNeeded) ChangeCols(a, ROW, j, j + 1);
        }
}

void Calc(int **a, const int ROW, const int COL, int &S, int &k) {
    S = 0;
    k = 0;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if (a[i][j] % 2 == 0 && a[i][j] % 7 != 0) {
                S += a[i][j];
                k++;
                a[i][j] = 0;
            }
}

int main() {
    srand((unsigned)time(NULL));

    const int ROW = 9;
    const int COL = 6;
    const int Low = 18;
    const int High = 74;

    int **Z = new int*[ROW];
    for (int i = 0; i < ROW; i++) Z[i] = new int[COL];

    Create(Z, ROW, COL, Low, High);
    cout << "start:" << endl;
    Print(Z, ROW, COL);

    int S = 0, k = 0;
    Calc(Z, ROW, COL, S, k);
    cout << endl << "S = " << S << endl;
    cout << "k = " << k << endl;

    cout << endl << "reset:" << endl;
    Print(Z, ROW, COL);

    SortCols(Z, ROW, COL);
    cout << endl << "sort:" << endl;
    Print(Z, ROW, COL);

    for (int i = 0; i < ROW; i++) delete[] Z[i];
    delete[] Z;
    return 0;
}
