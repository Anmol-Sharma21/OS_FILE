#include <iostream>
using namespace std;

#define N 5
#define M 3

bool isSafe(int allocation[N][M], int max[N][M], int need[N][M], int available[M]) {
    int work[M], finish[N];

    for (int i = 0; i < M; i++)
        work[i] = available[i];
    for (int i = 0; i < N; i++)
        finish[i] = 0;

    int count = 0;
    while (count < N) {
        bool found = false;
        for (int i = 0; i < N; i++) {
            if (finish[i] == 0) {
                int j;
                found = true;
                for (j = 0; j < M; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == M) {
                    for (j = 0; j < M; j++)
                        work[j] += allocation[i][j];
                    finish[i] = 1;
                    count++;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

int main() {
    int allocation[N][M] = { { 0, 1, 0 }, { 2, 0, 0 }, { 3, 0, 2 }, { 2, 1, 1 }, { 0, 0, 2 } };
    int max[N][M] = { { 0, 2, 2 }, { 3, 0, 2 }, { 4, 0, 3 }, { 3, 2, 2 }, { 2, 0, 2 } };
    int need[N][M];
    int available[M] = { 2, 2, 2 };

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    if (isSafe(allocation, max, need, available))
        cout << "System is in safe state.\n";
    else
        cout << "System is in unsafe state.\n";

    return 0;
}
