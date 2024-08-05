///////////100 points||||||||||||||
#include <iostream>
#include <vector>
#include <bitset>
#include <numeric>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;

int nc, nr, c, r;

// Função para converter as contagens de colunas atuais em um índice de estado, que contém as contagens de colunas atuais
long long int getStateIndex(vector<int>& countR) {
    sort(countR.begin(), countR.end()); // Ordena o vetor para normalizar a representação do estado
    long long int index = 0;
    long long int power = 1;
    for (int i = 0; i < countR.size(); ++i) {
        index += countR[i] * power; // Converte as contagens de colunas atuais em um índice de estado
        power *= (c + 1); // Aumenta a potência de acordo com o número de cartões que podem ser colocados em cada coluna
    }
    return index; // Retorna o índice de estado que contém as contagens de colunas atuais
}


// Função recursiva para explorar as colocações de cartões com memorização
long long int dp(const vector<int>& validMask, vector<unordered_map<long long int, long long int>>& memo, int row, vector<int>& countR, vector<int>& countC, int totalCards, int espRest) {
    // Variáveis auxiliares
    int nC = accumulate(countC.begin(), countC.end(), 0);
    int nR = accumulate(countR.begin(), countR.end(), 0);

    // Se a já não é possível continuar a preencher a grade
    if (nR > r * nr) return 0;

    // Se as cartas que faltam são mais do que as cartas que faltam para preencher a linha, não há como preencher a grade
    if (r - nR > totalCards) return 0;

    // Se já não há cartas suficientes para preencher as linhas e colunas, usando colunas e linhas
    if (totalCards < r * (nr - row) || totalCards < c * (nc - nC)) return 0;

    // Se não é cartas suficientes para preencher a grade
    if (espRest < totalCards) return 0;

    // Se o espaço restante não der para colocar as cartas
    if (espRest < r * (nr - row) || espRest < c * (nc - nC)) return 0;

    // Se a linha já está completa, avança para a próxima
    if (row == nr) {
        for (int count : countR) {
            if (count != c) return 0;
        }
        return 1;
    }

    long long int state = getStateIndex(countR); // Converte as contagens de colunas atuais em um índice de estado
    if (memo[row].find(state) != memo[row].end()) return memo[row][state]; // Se já calculamos o resultado para essa subestrutura, retornamos o valor armazenado
    
    long long int count = 0;   

    // Tenta colocar cartões em todas as colunas usando as máscaras válidas
    for (int mask : validMask) {
        vector<int> newcountR = countR;
        bool valid = true; 
        for (int col = 0; col < nc; ++col) {
            if (mask & (1 << col)) { // Se a coluna atual deve ser preenchida
                newcountR[col]++;
                //Adiciona mais 1 á linha em que foi adicionado um cartão
                countC[col]++;
                if (newcountR[col] > c) { // Se a contagem de cartões na coluna atual excede o limite, a grade é inválida
                    countC[col]--;
                    valid = false;
                    break;
                }
            }
        }

        if (valid) count += dp(validMask, memo, row + 1, newcountR, countC, totalCards - 1 , espRest - 1); // Chama a função recursivamente para a próxima linha
    }

    // Armazena o resultado na tabela de memoização e retorna
    return memo[row][state] = count;
}

int main() {
    int cases;
    cin >> cases;

    for (int t = 0; t < cases; t++) {
        // Read the grid size and card countR
        cin >> nc >> nr;
        cin >> c >> r;

        if (nc == 0 || nr == 0 || r == 0 || c == 0 || c > nr || r > nc) continue; // Skip invalid cases
        
        vector<int> countR(nc, 0);
        vector<int> countC(nc, 0);
        vector<unordered_map<long long int, long long int>> memo(nr);

        // Gera as máscaras válidas
        vector<int> validMask;
        for (int mask = 0; mask < (1 << nc); mask++) {
            if (bitset<32>(mask).count() == r) { // Apenas considera máscaras com exatamente `r` cartões
                validMask.push_back(mask);
            }
        }

        int totalCards = nc * c; // Número total de cartões que precisam ser colocados
        int espRest = nc * nr; // Número de espaços restantes na grade
        
        cout << dp(validMask, memo, 0, countR, countC, totalCards, espRest) << endl;
    }

    return 0;
}