#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./include/doctest.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void fisher_yates_shuffle(vector<int>& arr) {
    for (int i = arr.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

bool is_well_balanced(const vector<int>& sequence) {
    int prefix_sum = 0;
    

    for (int num : sequence) {
        prefix_sum += num;

        if (prefix_sum < 0) return false;

    }

    return (prefix_sum == 0); 
}




double compute_well_balanced_ratio(int n, int trials) {
    int well_balanced_count = 0;
    srand(time(0));

    for (int t = 0; t < trials; ++t) {
        vector<int> sequence(n, 1);
        sequence.insert(sequence.end(), n, -1);

        fisher_yates_shuffle(sequence);

        if (is_well_balanced(sequence)) {
            ++well_balanced_count;
        }
    }

    return static_cast<double>(well_balanced_count) / trials;
}

// Unit tests
TEST_CASE("Fisher-Yates Shuffle Test") {
    vector<int> original = {1, -1, 1, -1};
    vector<int> shuffled = original;
    fisher_yates_shuffle(shuffled);
    CHECK(original.size() == shuffled.size());
    CHECK(count(shuffled.begin(), shuffled.end(), 1) == 2);
    CHECK(count(shuffled.begin(), shuffled.end(), -1) == 2);
}

TEST_CASE("Well-balanced Sequence Test") {
    CHECK(is_well_balanced({-1, 1, 1, -1}) == false);          
    CHECK(is_well_balanced({1, 1, -1, -1}) == true);          
    CHECK(is_well_balanced({1, -1, 1, -1}) == true);          
    CHECK(is_well_balanced({1, 1, 1, -1, -1, -1}) == true);   
    CHECK(is_well_balanced({1, 1, 1, -1, -1, -1, -1, -1}) == false); 

    CHECK(is_well_balanced({1, 1, 1, 1, -1, -1, -1, -1}) == true);   
    CHECK(is_well_balanced({1, 1, 1, 1, 1, 1, 1, -1}) == false);     
    CHECK(is_well_balanced({-1, -1, -1, 1, 1, 1}) == false);          
    CHECK(is_well_balanced({-1, -1, -1, -1, -1, -1}) == false);      
    CHECK(is_well_balanced({1, 1, 1, 1, 1, 1}) == false);            
    CHECK(is_well_balanced({1, -1}) == true);                       
    CHECK(is_well_balanced({1, 1, -1}) == false);                   
}




