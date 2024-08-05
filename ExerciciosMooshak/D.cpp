#include <iostream>
#include <vector>

using namespace std;

int main() {
    int num_test_cases;
    cin >> num_test_cases;

    for (int t = 0; t < num_test_cases; ++t) {
        int num_rows;
        cin >> num_rows;

        vector<vector<int>> triangle(num_rows, vector<int>(num_rows));
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j <= i; ++j) {
                cin >> triangle[i][j];
            }
        }

        for (int i = num_rows - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                triangle[i][j] += max(triangle[i+1][j], triangle[i+1][j+1]);
            }
        }

        cout << triangle[0][0] << endl;
    }

    return 0;
}
