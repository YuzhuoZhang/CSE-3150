#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./include/doctest.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to perform modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Miller-Rabin primality test
bool miller_rabin(long long n, int k) {
    if (n < 2)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0)
        return false;

    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    srand(time(0));
    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 3);
        long long x = mod_exp(a, d, n);

        if (x == 1 || x == n - 1)
            continue;

        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mod_exp(x, 2, n);

            if (x == n - 1) {
                composite = false;
                break;
            }
        }

        if (composite)
            return false;
    }

    return true;
}

// Unit tests using doctest
TEST_CASE("Test for MR") {
    {
    int k =5;
    CHECK(miller_rabin(2, k) == true);
    }
    {
    int k =5;
    CHECK(miller_rabin(3, k) == true);
    }
    {
    int k =5;
    CHECK(miller_rabin(5, k) == true);
    }
    {
        int k =5;
        CHECK(miller_rabin(7, k) == true);
    }
    {
        int k =5;
        CHECK(miller_rabin(11, k) == true);
    }
    {
        int k =5;
        CHECK(miller_rabin(4, k) == false);
    }
    {
        int k =5;
        CHECK(miller_rabin(6, k) == false);
    }
    {
        int k =5;
        CHECK(miller_rabin(8, k) == false);
    }
    {
        int k =5;
        CHECK(miller_rabin(9, k) == false);
    }
    {
        int k =5;
        CHECK(miller_rabin(15, k) == false);
    }
}

