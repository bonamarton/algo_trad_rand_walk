/*

-- c++11 --

 Data Maker

    This program take relevant information from input file.

    Input file has a comma separated structure,
    with candle and date informations.

    Output file contains only close prices.

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <stdlib.h>

std::vector<std::string> split_string(std::string& str, const char delimeter);

int main()
{
    using namespace std;

    string input_name;
    string output_name;
    string line;
    vector<string> items;
    vector<double> close_price;

    cout << "\n Data Maker (from raw txt files) \n";
    cout << "\n Please type in input file name: ";
    cin >> input_name;

    cout << "\n\n Please type in output file name: ";
    cin >> output_name;
    cout << "\n\n";

    ifstream input_file(input_name.c_str());
    if(!input_file){ cerr << "\n Could not open input_file!\n"; return -1; }

    while(!input_file.eof()){

        getline(input_file, line);
        items = split_string(line, ',');

        if(items.size() > 1) {
                close_price.push_back(atof(items[2].c_str()));
        }
    }

    input_file.close();

    ofstream output_file(output_name.c_str());
    if(!output_file){ cerr << "\n Could not open output_file!\n"; return -1; }
    ostream_iterator<double> output_iterator(output_file, "\n");
    copy(close_price.begin(), close_price.end(), output_iterator);

    output_file.close();

    return 0;
}

std::vector<std::string> split_string(std::string& str, const char delimeter){

    std::vector<std::string> output;
    std::string item;

    for(auto ch : str){

       if(ch == delimeter) {output.push_back(item); item.clear(); }
       else {item += ch;}
    }
    output.push_back(item);

    return output;
}
