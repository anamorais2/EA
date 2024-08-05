#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>

int numPoints, numPreConnectedPairs;
std::vector<std::array<double, 2>> points;
std::vector<std::array<double, 3>> edges;
std::vector<int> parent;
std::vector<int> size;

int findSet(int x) {
    if (parent[x] != x) {
        parent[x] = findSet(parent[x]);
    }
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);
    if (size[rootX] > size[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootX] = rootY;
        if (size[rootX] == size[rootY]) {
            size[rootY]++;
        }
    }
}

double kruskalMST(int numEdges) {
    double totalWeight = 0;
    std::sort(edges.begin(), edges.end(), [](const std::array<double, 3>& a, const std::array<double, 3>& b) {
        return a[2] < b[2];
    });
    for (int i = 0; i < numEdges; i++) {
        if (findSet(edges[i][0]) != findSet(edges[i][1])) {
            totalWeight += edges[i][2];
            unionSets(findSet(edges[i][0]), findSet(edges[i][1]));
        }
    }
    return totalWeight;
}

int main() {
    int a, b, numEdges = 0;
    double dist;

    while (std::cin >> numPoints) {
        points.resize(numPoints);
        parent.resize(numPoints);
        size.resize(numPoints, 0);

        for (int i = 0; i < numPoints; i++) {
            std::cin >> points[i][0] >> points[i][1];
            parent[i] = i;
        }

        std::cin >> numPreConnectedPairs;
        for (int i = 0; i < numPreConnectedPairs; i++) {
            std::cin >> a >> b;
            unionSets(findSet(a-1), findSet(b-1));
        }

        for (int i = 0; i < numPoints; i++) {
            for (int j = i + 1; j < numPoints; j++) {
                dist = std::sqrt(std::pow(points[i][0] - points[j][0], 2) + std::pow(points[i][1] - points[j][1], 2));
                edges.push_back({(double)i, (double)j, dist});
                numEdges++;
            }
        }

        printf("%.2f\n", kruskalMST(numEdges));

        edges.clear();
        numEdges = 0;
    }
}
