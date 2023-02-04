#include <iostream>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

// idea got from : https://www.geeksforgeeks.org/ways-to-place-k-bishops-on-an-nxn-chessboard-so-that-no-two-attack/
// the idea is that only white and black squares could attack eachother so if we see how many could attack in only blacks
// we can find the total number
// it is a simple dynamic programming :
// -    We place the jth bishop in ith diagonal ==> remains j - 1 bishops that will be placed in (i - 2) diagonals
// -    We dont place it in ith diagonal ==> remains j bishops to be placed in (i - 2) diagonals

int countWays(int n, int k) {
    int diagonals[2*n-1+1];
    for (int i = 1; i <= 2*n-1;i++){
        int rem = i % 4;
        int num_of_group = floor(i/4);
        if (rem == 1 || rem == 2){
            diagonals[i] = num_of_group * 2 + rem;
        } else {
            diagonals[i] = diagonals[i - 2];
        }
    }

    vector<vector<int>> Placed(2 * n + 1, vector<int>(k + 1, 0));
    for (int i = 0; i < 2 * n + 1; ++i) {
        for (int j = 0; j < k + 1; ++j) {
            Placed[i].at(j) = 0;
            if ((j == 1 && i == 1) || j == 0)
                Placed[i].at(j) = 1;
        }
    }
    for (int i = 2; i <= 2 * n - 1; ++i) {
        for (int j = 1; j <= k; ++j) {
            Placed[i].at(j) = Placed[i - 2].at(j) + Placed[i - 2].at(j - 1) * max((diagonals[i] - (j - 1)), 0);
        }
    }


    int count = 0;
    for (int i = 0; i <= k; i++) {
        count += Placed[n * 2 - 1][i] * Placed[n * 2 - 2].at(k - i);
    }
    return count;
}

int main() {
    int n, k;
    cin >> n >> k;
    cout << countWays(n, k) << endl;
    return 0;
}
