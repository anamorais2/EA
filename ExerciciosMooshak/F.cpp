#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<int> object;
std::vector<int> guards;
int object_num;
int guard_meters;

int countGuards() {

    guards = {};
    std::sort(object.begin(), object.end());

    int i=0;
    guards.push_back(object[i] + guard_meters);

    for(int j=1; j<object_num; j++){
        if(object[j] > guards[i] + guard_meters){
            guards[i+1] = object[j] + guard_meters;
            i++;
        }
    }

    return i+1;

}


int main() {
    int test_case;
    int pos_object;
    
    std::cin >> test_case;

    for (int i = 0; i < test_case; i++) {
        std::cin >> object_num >> guard_meters;
        
        object = {};
        
        for (int i = 0; i < object_num; i++) {
            std::cin >> pos_object;
            object.push_back(pos_object);
        }

        //for (int i = 0; i < object_num; i++) {
        //    std::cout << object[i] << " ";
        //}

        //std::cout << "test_case: " << test_case << " object_num: " << object_num << " guard_meters: " << guard_meters << "\n";
        std::cout << countGuards() << "\n";
    }

    return 0;
}
