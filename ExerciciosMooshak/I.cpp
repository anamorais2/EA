#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

int n, s = 1, t;
std::vector<std::vector<int>> places;
std::vector<int> distances;
std::deque<int> Q;

int dijkstra(int max){
    int u = 0;

    for(int i=1; i<n; i++){
        distances[i] = max;
    }
    distances[0] = 0;
    int min = max;

    while(!Q.empty()){
        for(int i=0; i<n; i++){
            if(Q[i] != -10){
                if(distances[i] < min){
                    u = i;
                    min = distances[i]; 
                }
            }
        }
        Q[u] = -10;
        
        if(u == t-1){
            break;
        }

        for(int v=0; v<n; v++){
            if(places[u][v] != -1){
                if(distances[v] > distances[u] + places[u][v]){
                    distances[v] = distances[u] + places[u][v];
                }
            }
        }

        min = max;
    }

    return distances[t-1];
}


int main(){
    int node;
    int max = 0;
    
    while(std::cin >> n >> t){
        places = std::vector<std::vector<int>> (n, std::vector<int>(n));
        distances = std::vector<int> (n);

        for(int i=0; i<n; i++){
            for(int j=0; j<n+1; j++){
                if(j==0){
                    std::cin >> node;
                    node--;
                }
                else{
                    std::cin >> places[node][j-1];
                    if(places[node][j-1] > 0){
                        max += places[node][j-1];
                    }
                }
            }
            Q.emplace_back(i);
        }

        std::cout << dijkstra(max*2) << "\n";
        distances = {};
        Q = {};
        distances = {};
    }
}