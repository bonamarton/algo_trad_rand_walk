/*

-- c++11 --

 Geometric Brownian Motion

    GBM model stochastic diff. eq.: dS(t) = mu S(t) dt + sigma S(t) dB(t)

	  Where: + S(t):  asset price
		 + mu: 	  drift
		 + sigma: volatility
		 + B(t):  standard Brownian motion (or Wiener process)

	The program make data files with GBM.

	Program input:

		+ N: 		number of data point
		+ s_0: 		starting asset price
		+ mu: 		drift
		+ sigma: 	volatility
		+ n_path: 	number of paths (every path is a single file)
		+ output_name: 	name of the output file (or files)
				(n_path > 1) --> output_name = "given" + "_serial"

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>

template<typename T>
T in_get (std::istream & in) {
    T x;
    if (!(in >> x)){
        std::cerr << "\n Error while initializing from user input.\n";
        std::exit(1);
    }
    return x;
}

int main()
{
    using namespace std;

    const double dt = 1;

    cout << "\n Geometric Brownian Motion \n\n";
    cout << "\n\n  Please type in \"N\", number of data point: ";
    const int N = in_get<int>(cin);

    cout << "\n\n  Please type in \"s_0\", starting asset price: ";
    const double s_0 = in_get<double>(cin);

    cout << "\n\n  Please type in \"mu\", drift: ";
    const double mu = in_get<double>(cin);

    cout << "\n\n  Please type in \"sigma\", volatility: ";
    const double sigma = in_get<double>(cin);

    cout << "\n\n  Please type in \"n_path\", number of paths: ";
    const int n_path = in_get<int>(cin);

    cout << "\n\n  Please type in \"output_name\", name of the output file: ";
    const string output_name = in_get<string>(cin);

    srand(time(NULL));
    mt19937 gen(rand());
    normal_distribution<double> dB(0, sqrt(dt)); // (mean, std.dev.)

    vector<double> asset_price;
    asset_price.push_back(s_0);

    double increment_factor = (mu * dt) + (sigma * dB(gen));

    for(int i=1; i<N; ++i){
        asset_price.push_back((increment_factor + 1) * asset_price.back());
    }

    for(int i=0; i<N; ++i){
        cout << "\n " << asset_price[i];
    }



    return 0;
}
