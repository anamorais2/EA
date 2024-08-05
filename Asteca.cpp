#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm> 

using namespace std;

const int maxi = INT_MAX;
int r, c, m, bestSolution = maxi;

void rLeft(vector<vector<int>>& grid, int r, int c){
    int aux1 = grid[r][c];
    grid[r][c] = grid[r + 1][c]; 
    grid[r + 1][c] = grid[r + 1][c + 1];
    grid[r + 1][c + 1] = grid[r][c + 1];
    grid[r][c + 1] = aux1;
}

void rRight(vector<vector<int>>& grid, int r, int c) {
    int aux1 = grid[r][c];
    grid[r][c] = grid[r][c + 1];
    grid[r][c + 1] = grid[r + 1][c + 1];
    grid[r + 1][c + 1] = grid[r + 1][c];
    grid[r + 1][c] = aux1;
}

bool todosIguaisNaLinha(vector<int>& linha) {
    int primeiroElemento = linha[0];

    for (int i = 1; i < linha.size(); ++i) if (linha[i] != primeiroElemento) return false;
    
    return true; 
}

int isCorrect(vector<vector<int>>& grid, vector<bool>& bloqueio, int mo) {
    int valido = 1, subidas = 0, descidas = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] != i + 1) valido = 0;

            int temp = grid[i][j] - (i + 1);
            if (temp > 0) subidas += temp;
            else descidas += abs(temp);
            if (subidas > mo || descidas > mo) return -1;
            
        }
        // Caso: Bloqueio de uma linha já organizada
        if(valido != 0 && bloqueio[i] == false && c >= 3) {
                    
            if((i == r - 1 || i == 0) && todosIguaisNaLinha(grid[i])) bloqueio[i] = true;
            
            else if (i > 0 && todosIguaisNaLinha(grid[i]) && bloqueio[i-1]) bloqueio[i] = true;

            else if (i < r - 1 && todosIguaisNaLinha(grid[i]) && bloqueio[i+1]) bloqueio[i] = true;
        }
    }
    return valido;
}

int findMinMoves(vector<vector<int>>& grid, int x, int y, int moves, vector<bool>& bloqueio) {
    vector<bool> linhasBloqueadasInicio = bloqueio;
    int movesLeft = bestSolution == INT_MAX ? m - moves : bestSolution - moves;
    if (moves > m) return 0;
    if (moves >= bestSolution) return 0;
    int aux = isCorrect(grid,bloqueio, movesLeft);

    if (aux == 1) {
        bestSolution = min(bestSolution, moves); 
        return 1;
    }else if (aux == -1){
        return 0;
    }

    int found = 0;
    for (int i = 0; i < r - 1; i++) {
    
        if(bloqueio[i]) continue;   

        for (int j = 0; j < c - 1; j++) {
            if (i == x && j == y) continue;

            // Caso: Blocos iguais
            if (grid[i][j] == grid[i][j+1] && grid[i][j+1] == grid[i+1][j+1] && grid[i+1][j+1] == grid[i+1][j]) continue;
            
            // Caso: Blocos diagonais iguais
            if (grid[i][j] == grid[i+1][j+1] && grid[i][j+1] == grid[i+1][j]) {
            
                rRight(grid, i, j);
                found = max(found, findMinMoves(grid, i, j, moves + 1, bloqueio)); 
                rLeft(grid, i, j);

                continue;
            }

            rLeft(grid, i, j);
            found = max(found, findMinMoves(grid, i, j, moves + 1, bloqueio)); 
            rRight(grid, i, j); 

            rRight(grid, i, j);
            found = max(found, findMinMoves(grid, i, j, moves + 1, bloqueio)); 
            
            rRight(grid, i, j);
            found = max(found, findMinMoves(grid, i, j, moves + 2, bloqueio)); 
            rLeft(grid, i, j);
            rLeft(grid, i, j);

        }
    }
    
    bloqueio = linhasBloqueadasInicio;
    return found;
}

bool contarNumeros(vector<vector<int>>& grid) {
    unordered_map<int, int> contador;

    for (const auto& linha : grid) {
        for (int num : linha) contador[num]++;
    }

    for (const auto& [numero, contagem] : contador) {
        if (contagem != c) return false;
    }

    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {

        bestSolution = maxi;
        cin >> r >> c >> m;

        vector<vector<int>> grid(r, vector<int>(c, 0));

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> grid[i][j];
            }
        }

        vector<bool> bloqueio(r, false);
                
        if (contarNumeros(grid)){

                if (findMinMoves(grid, r, c, 0, bloqueio)) cout << bestSolution << "\n";

                else cout << "the treasure is lost!\n";
      
        }else cout << "the treasure is lost!\n";
    
    }

    return 0;
}