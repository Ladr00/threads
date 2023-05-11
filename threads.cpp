#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 4;

int RandomeNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

void multiply(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int row, int col) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += A[row][i] * B[i][col];
    }
    C[row][col] = sum;
}

int main() {
    srand(time(0));

    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = RandomeNumber(1, 100);
        }
    }

    vector<vector<int>> B(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = RandomeNumber(1, 100);
        }
    }

    vector<vector<int>> C(N, vector<int>(N, 0));

    vector<thread> threads;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            threads.push_back(thread(multiply, ref(A), ref(B), ref(C), i, j));
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }

    cout << "Matrix A:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix B:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Result:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
