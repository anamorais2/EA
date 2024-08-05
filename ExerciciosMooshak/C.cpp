#include <iostream>
#include <vector>

std::vector<int> visited;
std::vector<int> linkCount;
std::vector<std::vector<int>> costMatrix;
int numNodes, numEdges, maxLinks;
int minCost;

std::vector<std::vector<int>> createCostMatrix(std::vector<std::vector<int>>& edges){
    std::vector<std::vector<int>> matrix(numNodes, std::vector<int>(numNodes, 0));

    for(int i = 0; i < numEdges; i++){
        matrix[edges[i][0]-1][edges[i][1]-1] = edges[i][2];
        matrix[edges[i][1]-1][edges[i][0]-1] = edges[i][2];
    }

    return matrix;
}

std::vector<std::vector<int>> initializeVisitedAndLinkCount(){
    std::vector<int> visitedVector(numNodes);
    std::vector<int> linkCountVector(numNodes);
    std::vector<std::vector<int>> twoMatrices = {visitedVector, linkCountVector};

    return twoMatrices;
}

void findMinCost(int numVisited, int currentCost){
    if(currentCost >= minCost){
        return;
    }

    if(numVisited == numNodes){
        minCost = currentCost;
        return;
    }

    for(int i = 0; i < numNodes; i++){
        if(!visited[i]){
            for(int j = 0; j < numNodes; j++){
                if(visited[j] && costMatrix[i][j] > 0 && linkCount[j] < maxLinks){
                    linkCount[i]++;
                    linkCount[j]++;
                    visited[i] = 1;
                    findMinCost(numVisited + 1, currentCost + costMatrix[i][j]);
                    visited[i] = 0;
                    linkCount[i]--;
                    linkCount[j]--;
                }
            }
        }
    }
}

int main(){
    int node1, node2, edgeCost;
    std::vector<int> edge;
    std::vector<std::vector<int>> edges;
    int maxCost = 0;

    while(std::cin >> numNodes >> numEdges >> maxLinks){
        edges = {};
        for(int i = 0; i < numEdges; i++){
            edge = {};
            std::cin >> node1 >> node2 >> edgeCost;
            edge.push_back(node1);
            edge.push_back(node2);
            edge.push_back(edgeCost);
            edges.push_back(edge);
            maxCost += edgeCost;
        }

        costMatrix = createCostMatrix(edges);

        std::vector<std::vector<int>> twoMatrices = initializeVisitedAndLinkCount();
        visited = twoMatrices[0];
        visited[0] = 1;
        linkCount = twoMatrices[1];
        minCost = maxCost;

        findMinCost(1, 0);

        if(minCost == maxCost){
            std::cout << "NO WAY!\n";
        }
        else{
            std::cout << minCost << "\n";
        }

    }

    return 0;
}
