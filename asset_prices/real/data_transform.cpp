/*

-- c++11 --

 Data Maker

    This program take relevant columns from input file.

    Input file has a comma separated, fixed column structure.

    Output file contains only wanted columns, in space separated column structure.

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <stdlib.h>
#include <limits>

std::vector<std::string> split_string(std::string& str, const char delimeter);

int transform_use_cols(std::ifstream& input_file, std::ofstream& output_file, std::vector<int>& use_cols);

int transform_all_cols(std::ifstream& input_file, std::ofstream& output_file);

int main()
{
    using namespace std;

    string input_name;
    string use_cols_str;
    string output_name;

    int column = 0;
    vector<int> use_cols;

    cout << "\n Data Maker (from raw txt files) \n\n";
    cout << "\n  Please type in input file name: ";
    cin >> input_name;

    cout << "\n\n  Please type in wanted columns (\"0 1 3\" or \"-1\" means all): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, use_cols_str);

    cout << "\n\n  Please type in output file name: ";
    cin >> output_name;

    istringstream cols(use_cols_str);
    while (cols >> column) { use_cols.push_back(column); }

    ifstream input_file(input_name.c_str());
    if(!input_file){ cerr << "\n Could not open input_file!\n"; return 1; }

    ofstream output_file(output_name.c_str());
    if(!output_file){ cerr << "\n Could not open output_file!\n"; return 1; }

    if(use_cols[0] == -1){
        transform_all_cols(input_file, output_file);
    }
    else{
        transform_use_cols(input_file, output_file, use_cols);
    }

    input_file.close();
    output_file.close();

    cout << "\n\n  Finished!\n\n";

    return 0;
}

std::vector<std::string> split_string(std::string& str, const char delimiter){

    // Split a string along the given delimiter.
    // Return value is a string vector with parts of the string.

    std::vector<std::string> output;
    std::string item;

    for(auto ch : str){

       if(ch == delimiter) {output.push_back(item); item.clear(); }
       else {item += ch;}
    }
    output.push_back(item);

    return output;
}

int transform_use_cols(std::ifstream& input_file, std::ofstream& output_file, std::vector<int>& use_cols){

    // Transform the comma separated input file into space separated,
    // output file contains only given columns.

    using namespace std;

    int n_cols = use_cols.size();

    int i = 0;

    string line;
    vector<string> items;

    while(!input_file.eof()){

        getline(input_file, line);
        items = split_string(line, ',');

        if(items.size() > 1) {

            for(i=0; i<n_cols-1; ++i){
                output_file << items[use_cols[i]] << " ";
            }
            output_file << items[use_cols[i]] << "\n";
        }
    }

    return 0;
}

int transform_all_cols(std::ifstream& input_file, std::ofstream& output_file){

    // Transform the comma separated input file into space separated,
    // output file contains all columns.

    using namespace std;

    int n_items = 0;
    int i = 0;

    string line;
    vector<string> items;

    while(!input_file.eof()){

        getline(input_file, line);
        items = split_string(line, ',');
        n_items = items.size();

        if(n_items > 1) {

            for(i=0; i<n_items-1; ++i){
                output_file << items[i] << " ";
            }
            output_file << items[i] << "\n";
        }
    }

    return 0;
}
