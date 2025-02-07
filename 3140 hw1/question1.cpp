#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./include/doctest.h"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;


// a*x + b*y = gcd(a, b)
long long gcd_extend(long long a, long long b, long long &x, long long &y)
{

    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;
    long long result = gcd_extend(b, a%b, x1, y1);
    x = y1;
    y = x1 - (a/b) *y1;
    return result;
}

//Function to compute the inverse element y_i
long long inverse_y(long long a, long long b)
{
    long long x, y;
    long long gcd = gcd_extend(a,b, x,y );
    //Handle cases where gcd is not equal to 1
    if (gcd != 1) {
        throw invalid_argument("Modular inverse does not exist because gcd(a, b) != 1");
    }

    x = (x % b + b) % b;
    return x;

}


long long crt(const vector<long long> & remainders, const vector<long long> & modulis)
{

    long long M = 1;
    for(long long m : modulis)
    {   
        M *= m ; // M = M*m
    }

    long long result =0 ;
    for(int i=0; i < modulis.size(); i++)
    {
        long long a_i = remainders[i];
        long long m_i = modulis[i];
        long long M_i = M / m_i;

        long long y_i = inverse_y(M_i, m_i);

        long long x_i = (a_i * M_i * y_i) % M;

        result = (result % M + x_i % M) % M;;
    }
    return result;
}

//Unit test
TEST_CASE("CRT Test"){
    {
    vector<long long> remainders_1 = {2, 3, 2};
    vector<long long> modulis_1= {3, 5, 7};
    CHECK(crt(remainders_1, modulis_1) == 23 );
    }

    {
    vector<long long> remainders_2 = {0, 1};
    vector<long long> modulis_2= {2, 3};
    CHECK(crt(remainders_2, modulis_2) == 4 );
    }

    {
    vector<long long> remainders_3 = {3, 4};
    vector<long long> modulis_3= {4, 5};
    CHECK(crt(remainders_3, modulis_3) == 19 );
    }
    {
    vector<long long> remainders_3 = {3, 6, 1};
    vector<long long> modulis_3= {13, 11, 9};
    CHECK(crt(remainders_3, modulis_3) == 523 );
    }
    {
    vector<long long> remainders_3 = {5, 7, 3};
    vector<long long> modulis_3= {12, 10, 14};
    CHECK_THROWS(crt(remainders_3, modulis_3) == 17 );//Non-mutual prime should throw an exception
    }
    {
    vector<long long> remainders_3 = {2, 4, 0};
    vector<long long> modulis_3= {11, 5, 6};
    CHECK(crt(remainders_3, modulis_3) == 24 );
    }
    {
    vector<long long> remainders_3 = {9, 1, 5};
    vector<long long> modulis_3= {13, 10, 6};
    CHECK_THROWS(crt(remainders_3, modulis_3) == 191 );//Non-mutual prime should throw an exception
    }
    {
    vector<long long> remainders_3 = {0, 0};
    vector<long long> modulis_3= {4, 5};
    CHECK(crt(remainders_3, modulis_3) == 0 );//The solution of 0 modulo 4 and 0 modulo 5 should be 0
    }
    {
    vector<long long> remainders_3 = {2, 6, 4};
    vector<long long> modulis_3= {5, 11, 14};
    CHECK(crt(remainders_3, modulis_3) == 732 );
    }
    {
    vector<long long> remainders_3 = {4, 4, 2};
    vector<long long> modulis_3= {5, 12, 11};
    CHECK(crt(remainders_3, modulis_3) == 244 );
    }

}

