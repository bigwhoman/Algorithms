#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int LCS_Index(const string& input_string);


int main() {
    string a;
    cin >> a;
    int longest_prefix = LCS_Index(a);
    int found = a.length() % (longest_prefix + 1);
    string k = a.substr(found, longest_prefix + 1 - found);
    int remain = 8 - k.length();
    if (remain == 0) {
        cout << k;
    } else if (remain > 0) {
        int j = 0;
        while (remain > 0) {
            k += a[j];
            remain--;
            if (j == longest_prefix)
                j = 0;
            else j++;
        }
        cout << k;
    } else if (remain < 0) {
        cout << k.substr(0, 8);
    }

}

int LCS_Index(const string& input_string) {
    int n = input_string.length();
    vector<vector<int>> Prefix_table(n + 1, vector<int>(n + 1, 0));
    int max_length = 0;
    int index = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (input_string[i - 1] == input_string[j - 1] &&
                Prefix_table[i - 1].at(j-1) < (j - i)) {
                Prefix_table[i].at(j) = Prefix_table[i - 1].at(j-1) + 1;
                if (Prefix_table[i].at(j) > max_length) {
                    max_length = Prefix_table[i].at(j);
                    index = max(i, index);
                }
            }
        }
    }
    return index - 1;
}