#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

const int MAX_COORD = 200;
const int MOVES_X[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int MOVES_Y[] = {1, 2, 2, 1, -1, -2, -2, -1};

struct Knight {
    int x, y, moves;
};

int board[401][401];

int algorithm(int x, int y, int m){
    int count = 0;

    if(board[x+200][y+200]==0){
        board[x+200][y+200]=1;
        count++;
    }

    if(m>0){
        for (int k = 0; k < 8; ++k) {
            int next_x = x + MOVES_X[k];
            int next_y = y + MOVES_Y[k];
            
            if (next_x >= -200 && next_x <= 200 && next_y >= -200 && next_y <= 200) {
                count += algorithm(next_x, next_y, m-1);
            }
        }
    }       
    return count;
}

int main() {
    int n;
    cin >> n;

    vector<Knight> knights(n);

    for (int i = 0; i < n; ++i) {
        cin >> knights[i].x >> knights[i].y >> knights[i].moves;
    }

    int count_moves = 0;

    for (const auto& knight : knights) {
        count_moves += algorithm(knight.x, knight.y, knight.moves);
    }

    cout << count_moves << endl;

    return 0;
}
