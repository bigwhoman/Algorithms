//#include <bits/stdc++.h>
//
//using namespace std;
//#define INF INT_MAX/2;
//
//
//int main() {
//    int num_of_buildings = 5;
//    cin >> num_of_buildings;
//    int heights[num_of_buildings + 2];
//
//    for (int i = 1; i <= num_of_buildings; i++) {
//        int height;
//        cin >> height;
//        heights[i] = height;
//    }
//    heights[0] = 0;
//    heights[num_of_buildings + 1] = 0;
//
//    heights[0] = 0;
//    heights[num_of_buildings + 1] = 0;
//    int table[num_of_buildings + 1][int(ceil(float(num_of_buildings) / 2)) + 1][2];
//    for (int i = 0; i <= num_of_buildings; i++) {
//        for (int j = 0; j <= ceil(float(num_of_buildings) / 2); ++j) {
//            for (int k = 0; k < 2; k++) {
//                table[i][j][k] = INF;
//            }
//        }
//    }
//    for (int i = 0; i <= num_of_buildings; i++) {
//        for (int j = 0; j <= ceil(float(num_of_buildings) / 2); ++j) {
//            for (int k = 0; k < 2; k++) {
//
//                if (j > ceil(float(i) / 2))
//                    table[i][j][k] = INF;
//                if (i == 0 && j != 0)
//                    table[i][j][k] = INF;
//                if (j == 0 && i != 0) {
//                    if (k == 0) {
//                        table[i][j][k] = 0;
//                    } else {
//                        if (heights[i] <= heights[i - 1])
//                            table[i][j][k] = heights[i - 1] - heights[i] + 1;
//                        else
//                            table[i][j][k] = 0;
//                    }
//                }
//                if (i == 1 && j == 1) {
//                    if (k == 0) {
//                        table[i][j][k] = INF;
//                    } else {
//                        table[i][j][k] = 0;
//                    }
//                }
//            }
//        }
//    }
//
//    for (int i = 2; i <= num_of_buildings; i++) {
//        for (int j = 1; j <= ceil(float(num_of_buildings) / 2); ++j) {
//            table[i][j][0] = min(table[i - 1][j][0], table[i - 1][j][1]
//                                                     + max(0, heights[i] - heights[i - 1] + 1));
//            table[i][j][1] = min(table[i - 2][j - 1][0] + max(0, heights[i - 1] - heights[i] + 1),
//                                 table[i - 2][j - 1][1] + max(0,
//                                                              heights[i - 1] - min(heights[i], heights[i - 2]) +
//                                                              1));
//        }
//    }
//    for (int i = 1; i <= ceil(float(num_of_buildings) / 2); i++)
//        cout << min(table[num_of_buildings][i][0], table[num_of_buildings][i][1]) << " ";
//    return 0;
//}
#include <bits/stdc++.h>

using namespace std;
#define INF 3*INT_MAX/2;


int main() {
    int num_of_buildings = 5;
    cin >> num_of_buildings;
    int heights[num_of_buildings + 2];

    for (int i = 1; i <= num_of_buildings; i++) {
        int height;
        cin >> height;
        heights[i] = height;
    }
    heights[0] = 0;
    heights[num_of_buildings + 1] = 0;

    heights[0] = 0;
    heights[num_of_buildings + 1] = 0;
    int table[num_of_buildings + 1][int(ceil(float(num_of_buildings) / 2)) + 1][2];
    for (int i = 0; i <= num_of_buildings; i++) {
        for (int j = 0; j <= ceil(float(num_of_buildings) / 2); ++j) {
            for (int k = 0; k < 2; k++) {
                table[i][j][k] = INF;
            }
        }
    }
    for (int i = 0; i <= num_of_buildings; i++) {
        for (int j = 0; j <= ceil(float(num_of_buildings) / 2); ++j) {
            for (int k = 0; k < 2; k++) {

                if (j > ceil(float(i) / 2))
                    table[i][j][k] = INF;
                if (i == 0 && j != 0)
                    table[i][j][k] = INF;
                if (j == 0) {
                    if (k == 0) {
                        table[i][j][k] = 0;
                    } else {
                        if (heights[i + 1] < heights[i])
                            table[i][j][k] = heights[i] - heights[i + 1] +1;
                        else
                            table[i][j][k] = 0;
                    }
                }
                if (i == 1 && j == 1) {
                    if (k == 0) {
                        table[i][j][k] = INF;
                    } else {
                        table[i][j][k] = 0;
                    }
                }
            }
        }
    }

    for (int i = 2; i <= num_of_buildings; i++) {
        for (int j = 1; j <= ceil(float(num_of_buildings) / 2); ++j) {
            table[i][j][0] = min(table[i - 1][j][0], table[i - 1][j][1]
                                                     + max(0, heights[i] - heights[i - 1] + 1));
            table[i][j][1] = min(table[i - 2][j - 1][0] + max(0, heights[i - 1] - heights[i] + 1),
                                 table[i - 2][j - 1][1] + max(0,
                                                              heights[i - 1] - min(heights[i], heights[i - 2]) +
                                                              1));
        }
    }
    for (int i = 1; i <= ceil(float(num_of_buildings) / 2); i++)
        cout << min(table[num_of_buildings][i][0], table[num_of_buildings][i][1]) << " ";
    return 0;
}
