#include <iostream>
#include <vector>
#include <cmath>

int sum;
int absolute_diff;

int calculate_minimum_difference(int num_pizzas, std::vector<int> pizzas, int total_sum){
    int half = std::floor(total_sum/2);
    std::vector<std::vector<bool>> dp(num_pizzas+1, std::vector<bool> (half+1, false));

    for(int i=0; i<num_pizzas+1; i++){
        dp[i][0] = true;
    }
    
    for(int i=1; i<num_pizzas+1; i++){
        for(int j=1; j<half+1; j++){
            if(pizzas[i-1] > j){
                dp[i][j] = dp[i-1][j];
            }
            else{
                dp[i][j] = (dp[i-1][j] || dp[i-1][j-pizzas[i-1]]);
            }
        }
    }

    for(int j=half; j>-1; j--){
        if(dp[num_pizzas][j]){
            return std::abs(j-(total_sum-j));
        }
    }

    return 0;
}

int main(){
    int num_pizzas, total_sum;
    int pizza_time;
    std::vector<int> pizzas;

    while(std::cin >> num_pizzas){
        total_sum = 0;
        absolute_diff = 0;

        for(int i=0; i<num_pizzas; i++){
            std::cin >> pizza_time;
            pizzas.push_back(pizza_time);
            total_sum += pizza_time;
        }

        std::cout << calculate_minimum_difference(num_pizzas, pizzas, total_sum) << "\n";

        pizzas = {};
    }

}
