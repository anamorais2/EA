#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


int tempoAtual, totalPontosDeCorte;
std::vector<int> temposDeVisita, menorTempoDeVisita, antecessor, marcadoComoPontoDeCorte;
std::vector<std::vector<int>> grafo;


int processarLinha(std::string linha){
    std::string numeroAtual = "";
    int tamanho = linha.size();
    int numero, verticeAtual = -1;

    for(int i = 0; i < tamanho; i++){
        if(linha[i] != ' '){            
            numeroAtual += linha[i];
            
            if(numeroAtual == "0"){
                return -1; // Indica o fim da entrada
            }

            if(i == tamanho - 1){
                numero = std::stoi(numeroAtual) - 1;

                grafo[verticeAtual].emplace_back(numero);
                grafo[verticeAtual][0]++;
                grafo[numero].emplace_back(verticeAtual);
                grafo[numero][0]++;
            }
        }
        else{
            numero = std::stoi(numeroAtual) - 1;

            if(verticeAtual == -1){
                verticeAtual = numero;
            }
            else{
                grafo[verticeAtual].emplace_back(numero);
                grafo[verticeAtual][0]++;
                grafo[numero].emplace_back(verticeAtual);
                grafo[numero][0]++;
            }
            
            numeroAtual = "";
        }
    }

    return 0;
}

// Função de busca em profundidade para encontrar pontos de corte
void encontrarPontosDeCorte(int vertice){
    int adjacente;
    menorTempoDeVisita[vertice] = temposDeVisita[vertice] = tempoAtual++;
    
    for(int i = 1; i < grafo[vertice][0] + 1; i++){
        adjacente = grafo[vertice][i];
        if(temposDeVisita[adjacente] == -1){
            antecessor[adjacente] = vertice;
            encontrarPontosDeCorte(adjacente);
            menorTempoDeVisita[vertice] = std::min(menorTempoDeVisita[vertice], menorTempoDeVisita[adjacente]);
            if(marcadoComoPontoDeCorte[vertice] != 1){
                if(temposDeVisita[vertice] == 1 && temposDeVisita[adjacente] != 2){
                    marcadoComoPontoDeCorte[vertice] = 1;
                    totalPontosDeCorte++;
                }
                if(temposDeVisita[vertice] != 1 && menorTempoDeVisita[adjacente] >= temposDeVisita[vertice]){
                    marcadoComoPontoDeCorte[vertice] = 1;
                    totalPontosDeCorte++;
                }
            }
        }
        else if(antecessor[vertice] != adjacente){
            menorTempoDeVisita[vertice] = std::min(menorTempoDeVisita[vertice], temposDeVisita[adjacente]);
        }
    }
}

int main(){
    int n; 
    std::string linha;

    while(std::cin >> n && n != 0){
        getline(std::cin, linha);

        totalPontosDeCorte = 0;
        tempoAtual = 1;
        temposDeVisita = menorTempoDeVisita = antecessor = marcadoComoPontoDeCorte = std::vector<int>(n, -1);
        grafo = std::vector<std::vector<int>>(n, std::vector<int>(1, 0));

        while(getline(std::cin, linha) && processarLinha(linha) != -1);

        encontrarPontosDeCorte(0);
        
        std::cout << totalPontosDeCorte << "\n";
    }

    return 0;
}
