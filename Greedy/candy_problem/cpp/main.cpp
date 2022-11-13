#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;


int main() {
    vector<int> candy_for_day;
    int candy_num, day_num;
    cin >> candy_num >> day_num;
    vector<vector<vector<int>>> num_of_eaten_list;
    num_of_eaten_list.reserve(day_num);
    for (int i = 0; i < day_num; i++) {
        num_of_eaten_list.emplace_back();
    }

    int total_value = 0;
    for (int i = 0; i < candy_num; i++) {
        int val;
        cin >> val;
        total_value += val;
        num_of_eaten_list[0].push_back(vector<int>{i + 1, val, 0});
    }

    sort(num_of_eaten_list[0].begin(), num_of_eaten_list[0].end(),
         [](const vector<int> &i, const vector<int> &j) {
             return i[1] > j[1];
         });
    int max_eaten_candy = 0;
    for (int day = 0; day < day_num; day++) {
        int max_diff_index = 0;
        double max_diff = -10000;
        for (int i = 0; i < max_eaten_candy + 1; i++) {
            if (!num_of_eaten_list[i].empty()) {
                double mm = double(day) * num_of_eaten_list[i][0][1] / total_value -
                            num_of_eaten_list[i][0][2];
                if (mm > max_diff) {
                    max_diff = mm;
                    max_diff_index = i;
                }
            }
        }
        num_of_eaten_list[max_diff_index][0][2] += 1;
        candy_for_day.push_back(num_of_eaten_list[max_diff_index][0][0]);
        if (num_of_eaten_list[max_diff_index][0][2] > max_eaten_candy)
            max_eaten_candy = num_of_eaten_list[max_diff_index][0][2];
        num_of_eaten_list[max_diff_index + 1].push_back(
                num_of_eaten_list[max_diff_index][0]);
        num_of_eaten_list[max_diff_index].erase(num_of_eaten_list[max_diff_index].begin() + 0);
    }
    for (const auto &cand: candy_for_day) {
        cout << cand << " ";
    }

    return 0;
}
