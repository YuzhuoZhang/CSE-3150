#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./include/doctest.h"
#include <iostream>

bool non_neg_prefix_sum(const int arr[], int size) {
    int prefix_sum = 0;
    for (int i = 0; i < size; i++) {
        prefix_sum += arr[i];
        if (prefix_sum < 0) {
            return false;
        }
    }
    return true;
}

bool non_pos_prefix_sum(const int arr[], int size) {
    int prefix_sum = 0;
    for (int i = 0; i < size; i++) {
        prefix_sum += arr[i];
        if (prefix_sum > 0) {
            return false;
        }
    }
    return true;
}
int arr1[] = {1, -1, 1, -1};
int arr2[] = {-1, 1, -1, 1};
int arr3[] = {1, -1, -1, 1};
int arr4[] = {1, 1, -1, -1, 1};
int arr5[] = {};
TEST_CASE("Testing non_neg_prefix_sum") {
    CHECK(non_neg_prefix_sum(arr1, 4) == true);
    CHECK(non_neg_prefix_sum(arr2, 4) == false);
    CHECK(non_neg_prefix_sum(arr3, 4) == false);
    CHECK(non_neg_prefix_sum(arr4, 5) == true);
    CHECK(non_neg_prefix_sum(arr5, 0) == true);

    
}
int arr6[] = {-1, 1, -1, 1};
int arr7[] = {-1, -1, 1, 1};
int arr8[] = {-1, 1, 1, -1};
int arr9[] = {-1, 1, 1, -1};

TEST_CASE("Testing non_pos_prefix_sum") {
    CHECK(non_pos_prefix_sum(arr6, 4) == true);
    CHECK(non_pos_prefix_sum(arr7, 4) == true);
    CHECK(non_pos_prefix_sum(arr8, 4) == false);
    CHECK(non_pos_prefix_sum(arr9, 4) == false);
    CHECK(non_pos_prefix_sum(arr5, 0) == true);

    
  
}