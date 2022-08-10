#include <iostream>
#include <bits/stdc++.h>
#include <vector>

void first_method(int size, const std::pair<float, float> *points, std::vector<std::pair<float, float>> &convex);

using namespace std;

int main() {
    int size;
    cin >> size;
    pair<float, float> points[size];
    vector<pair<float, float>> convex;
    for (int i = 0; i < size; i++) {
        float x, y;
        cout << "Enter pair " << i << " : ";
        cin >> x;
        cin >> y;
        points[i] = make_pair(x, y);
    }


//    first_method(size, points, reinterpret_cast<vector<std::pair<float, float>> &>(reinterpret_cast<int &>(convex)));
    for (pair<float, float> i: convex)
        std::cout << i.first << ' ' << i.second << endl;
}

void second_method(int size, pair<float, float> points,vector<pair<float, float>> &convex) {


}

void first_method(int size, const pair<float, float> *points, vector<pair<float, float>> &convex) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            bool T = true;
            float a = (points[i].second - points[j].second) / (points[i].first - points[j].first);
            float b = points[i].second - a * points[i].first;
            for (int k = 0; k < size; ++k) {
                if (points[k].second - a * points[k].first - b > 0)
                    T = false;
            }
            if (T)
                convex.push_back(points[i]);
        }

    }
}
