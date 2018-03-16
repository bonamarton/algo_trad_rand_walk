/*

-- c++11 --

 Geometric Brownian Motion

    GBM model stochastic diff. eq.: dS(t) = mu S(t) dt + sigma S(t) dB(t)

                                    dS(t) = [ (mu * dt) + (sigma * dB(t)) ] * S(t)
                                    S(t+dt) = S(t) + dS(t)
                                    S(t+dt) = [(mu * dt) + (sigma * dB(t)) + 1] * S(t)

	  Where: + S(t):  asset price
		 + mu: 	  drift
		 + sigma: volatility
		 + B(t):  standard Brownian motion (or Wiener process)

	The program make data files with GBM.

	Program input:

		+ N: 		     number of data point
		+ t_frame_unit   timeframe unit
		+ t_frame_factor timeframe factor
		+ s_0: 		     starting asset price
		+ mu: 		     drift
		+ sigma: 	     volatility
		+ output_name: 	 name of the output file

    !!! Time unit is one year, dt calculated from this:
            dt = one day ==> dt = 1 / number_of_days_in_one_year

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>

// Make template for reading constants from stdin.
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

    //////////// Parameters ///////////////////////////////////////////////////////

    double dt_time_unit[4];
    dt_time_unit[0] = 1.0 / (250.0 * 24.0 * 60.0 * 60.0);  // s: second
    dt_time_unit[1] = 1.0 / (250.0 * 24.0 * 60.0);         // m: minute
    dt_time_unit[2] = 1.0 / (250.0 * 24.0);                // h: hour
    dt_time_unit[3] = 1.0 / (250.0);                       // d: Day (only trading days)

    cout << "\n Geometric Brownian Motion \n\n";
    cout << "\n\n  Please type in \"N\", number of data point: ";
    const int N = in_get<int>(cin);

    cout << "\n\n  Please type in \"t_frame_unit\", timeframe unit ";
    cout << "\n  (\"0\" second, \"1\" minute, \"2\" hour, \"3\" day): ";
    const int t_frame_unit = in_get<int>(cin);
    if(t_frame_unit < 0 || t_frame_unit > 3){ cout << "wrong t_frame_unit!"; exit(1); }

    cout << "\n\n  Please type in \"t_frame_factor\", timeframe factor: ";
    const double t_frame_factor = in_get<double>(cin);

    cout << "\n\n  Please type in \"s_0\", starting asset price: ";
    const double s_0 = in_get<double>(cin);

    cout << "\n\n  Please type in \"mu\", drift: ";
    const double mu = in_get<double>(cin);

    cout << "\n\n  Please type in \"sigma\", volatility: ";
    const double sigma = in_get<double>(cin);

    cout << "\n\n  Please type in \"output_name\", name of the output file: ";
    const string output_name = in_get<string>(cin);

    //////////// Geo. Brownian Motion ////////////////////////////////////////////////

    ofstream output_file(output_name.c_str());
    if(!output_file){ cerr << "\n Could not open output_file!\n"; return -1; }

    output_file << N << " :\"N\", number of data point\n";
    output_file << mu << " :\"mu\", drift\n";
    output_file << sigma << " :\"sigma\", volatility\n\n";

    const double dt = t_frame_factor * dt_time_unit[t_frame_unit];

    // random number generator
    srand(time(NULL));
    mt19937 gen(rand());
    normal_distribution<double> dB(0, sqrt(dt)); // (mean, std.dev.)

        ///////// GBM algorithm starts here /////

    double asset_price = s_0;
    double const_var = (mu * dt) + 1;

    output_file << asset_price << "\n";
    for(int i=1; i<N; ++i){
        asset_price *= const_var + (sigma * dB(gen));
        output_file << asset_price << "\n";
    }

        /////////////////////////////////////////

    output_file.close();

    cout << "\n\n  Finished!\n\n";

    return 0;
}
