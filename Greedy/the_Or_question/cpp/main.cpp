#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <array>
#include <string>

using namespace std;

bool comparison(vector<long> vect1, vector<long> vect2) {

    if (vect1.at(0) < vect2.at(0)) return true;
    if (vect1.at(0) == vect2.at(0)) return vect1.at(1) < vect2.at(1);
    return false;
}

template<typename T>
std::vector<int> findItems(std::vector<T> const &v, int target) {
    std::vector<int> indices;

    for (auto it = v.begin(); it != v.end(); it++) {
        if (*it == target) {
            indices.push_back(std::distance(v.begin(), it));
        }
    }

    return indices;
}

int main() {
    int size, num_of_constraints;
    cin >> size >> num_of_constraints;
    if (num_of_constraints == 0) {
        for (int i = 0; i < size; i++) {
            cout << 0 << " ";
        }
        return 0;
    }
    vector<vector<long>> constraints;
    for (int i = 0; i < num_of_constraints; i++) {
        long num1, num2;
        long or_ans;
        cin >> num1 >> num2 >> or_ans;
        if (num1 > num2) {
            long kk = num1;
            num1 = num2;
            num2 = kk;
        }
        vector<long> v;
        v.push_back(num1);
        v.push_back(num2);
        v.push_back(or_ans);
        constraints.push_back(v);
    }
    sort(begin(constraints), end(constraints), comparison);
    vector<vector<char>> ans_list;
    for (const auto &constraint: constraints) {
        string binary = bitset<32>(constraint.at(2)).to_string();
        vector<char> data(binary.begin(), binary.end());
        ans_list.push_back(data);
    }
    vector<vector<char>> n_list;
    for (int i = 0; i < size; i++) {
        vector<char> n;
        n.reserve(32);
        for (int bit = 0; bit < 32; bit++) {
            n.push_back('x');
        }
        n_list.push_back(n);
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < num_of_constraints; j++) {
            long n1 = constraints[j].at(0);
            long n2 = constraints[j].at(1);
            for (int bit = 0; bit < 32; bit++) {
                if (n1 != n2) {
                    if (ans_list[j].at(bit) == '0') {
                        n_list[n1 - 1].at(bit) = '0';
                        n_list[n2 - 1].at(bit) = '0';
                    } else {
                        if (n_list[n1 - 1].at(bit) == '0') {
                            n_list[n2 - 1].at(bit) = '1';
                        }

                        if (n_list[n2 - 1].at(bit) == '0') {
                            n_list[n1 - 1].at(bit) = '1';
                        }
                    }
                } else {
                    n_list[n1 - 1].at(bit) = ans_list[j].at(bit);
                    n_list[n2 - 1].at(bit) = ans_list[j].at(bit);
                }
            }
        }
    }

    vector<vector<int>> changed_bit;
    for (int i = 0; i < size; i++) {
        vector<int> indices = findItems(n_list[i], 'x');
        changed_bit.push_back(indices);
    }

    for (auto &num: n_list) {
        for (auto &bit: num) {
            if (bit == 'x')
                bit = '0';
        }
    }


    for (int i = 0; i < num_of_constraints; i++) {
        long n1 = constraints[i].at(0);
        long n2 = constraints[i].at(1);
        for (int bit = 0; bit < 32; bit++) {
            if (ans_list[i][bit] == '1') {
                if (n_list[n2 - 1][bit] == '0' && n_list[n1 - 1][bit] == '0')
                    n_list[n2 - 1][bit] = '1';
            }
        }
    }

    vector<long> numbers;
    for (const auto &number: n_list) {
        auto it = find(number.begin(), number.end(), 'x');
        if (it != number.end()) {
            numbers.push_back(0);
        } else {
            string num(number.begin(), number.end());
            long dec = stoi(num, nullptr, 2);
            numbers.push_back(dec);
        }

    }
    for (const auto j: numbers) {
        std::cout << j << " ";
    }


    return 0;


}
