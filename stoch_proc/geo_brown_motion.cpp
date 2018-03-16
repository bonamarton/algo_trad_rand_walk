/*

-- c++11 --

 Geometric Brownian Motion



*/

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>

int main()
{
    using namespace std;

    double dt = 1;

    srand(time(NULL));
    mt19937 gen(rand());
    normal_distribution<double> norm_dist(0,sqrt(dt));




    return 0;
}
