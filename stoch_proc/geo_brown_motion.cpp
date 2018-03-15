/*

-- c++11 --

 Geometric Brownian Motion



*/

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

int main()
{
    using namespace std;

    double dt = 1;

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> norm_dist(0,sqrt(dt));

    for(int i=0; i<10; i++){
        cout << norm_dist(gen) << "\n";
    }

    return 0;
}
