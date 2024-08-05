#include <iostream>
#include <algorithm>

bool compareFunc(int a, int b) {
    return a < b;
}

int checkFair(int guests[], int n) {
    std::sort(guests, guests + n, compareFunc);

    for (int i = 0; i < n; i++) {
        int j = i + 1;
        int k = n - 1;

        while (j < k) {
            int sum = guests[i] + guests[j] + guests[k];
            if (sum == 0) {
                if ((guests[i] > 0 && guests[j] < 0) ||
                    (guests[i] < 0 && guests[j] > 0) ||
                    (guests[i] > 0 && guests[k] < 0) ||
                    (guests[i] < 0 && guests[k] > 0) ||
                    (guests[j] > 0 && guests[k] < 0) ||
                    (guests[j] < 0 && guests[k] > 0)) {
                    return 1; 
                }
                j++;
                k--;
            } else if (sum < 0) {
                j++;
            } else {
                k--;
            }
        }
    }

    return 0; 
}

int main() {
    
    int n;
    std::cin >> n;

    while (n != 0) {

        int* guests = new int[n];
        int aux = n;
        
        for (int i = 0; i < n; i++) {
            std::cin >> guests[i];
        }

        std::cin >> n;
        if (n == 0) {
            if (checkFair(guests, aux) == 1) {
                std::cout << "Fair\n";
            } else if (checkFair(guests, aux) == 0) {
                std::cout << "Rigged\n";
            }
        }

        delete[] guests;

        std::cin >> n;
    }
    return 0;
}
