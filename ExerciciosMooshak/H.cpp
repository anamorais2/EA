#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

int n, m;
std::vector<std::vector<int>> train_stations;
std::vector<int> colors;


bool isCorrupted(int v){
    int t, u;
    std::deque<int> Q;
    colors[v-1] = 1;
    Q.push_back(v);

    while(!Q.empty()){
         t = Q[0];
        Q.pop_front();

        for(int i=1; i<train_stations[t-1][0]+1; i++){
            u = train_stations[t-1][i];
            if(colors[u-1] == 0){
                colors[u-1] = 1-colors[t-1];
                Q.push_back(u);
            }
            else if(colors[u-1] == colors[t-1]){
                return false;
            }
        }
    }
    
    return true;
}


int main(){
    int aux, aux2;

    while(std::cin >> n >> m){
        colors = std::vector<int>(n, 0);
        train_stations = std::vector<std::vector<int>>(n, std::vector<int>(1,0));

        for(int i=0; i<m; i++){
            std::cin >> aux >> aux2;
            train_stations[aux-1].emplace_back(aux2);
            train_stations[aux-1][0]++;
            train_stations[aux2-1].emplace_back(aux);
            train_stations[aux2-1][0]++;
        }

        if(!isCorrupted(1)){
            std::cout << "NO\n";
        }
        else{
            std::cout << "NOT SURE\n";
        }

        train_stations = {};
    }
}