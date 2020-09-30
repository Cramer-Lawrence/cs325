#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

vector<int> merge_sort(vector<int> in_array);
vector<int> merge_data(vector<int> vector_a, vector<int> vector_b);
void print_data(vector<int> array_data);
vector<vector<int>> pull_line_int_array(string sheet_name);
void write_output(string file_name, vector<int> out_array);


// Main function for the program
int main(){

    vector<vector<int>> in_array = pull_line_int_array("data.txt");

    ofstream out_file;
    out_file.open("mergeout.txt");

    for(int i = 0; i < in_array.size(); i++){
        print_data(in_array[i]);

        auto start_time = std::chrono::system_clock::now();
        in_array[i] = merge_sort(in_array[i]);
        auto end_time = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end_time - start_time;
        std::cout << "Time to finish operation: " << diff.count() << " seconds.\n";

        print_data(in_array[i]);
        
        for (int j = 0; j < in_array[i].size(); j++){
            out_file << to_string(in_array[i][j]) + " ";
        }
        out_file << "\n";
    }
    out_file.close();
    return 0;
}

// Sorts the data using merge sort
vector<int> merge_sort(vector<int> in_array){

    if (in_array.size() == 1){
        return in_array;
    }

    vector<int> lower_array, upper_array;

    int index = in_array.size() / 2;

    for (int i = 0; i < index; i++){
        lower_array.push_back(in_array[i]);
    }
    for (int i = index; i < in_array.size(); i++){
        upper_array.push_back(in_array[i]);
    }

    lower_array = merge_sort(lower_array);
    upper_array = merge_sort(upper_array);

    return merge_data(lower_array, upper_array);
}

vector<int> merge_data(vector<int> vector_a, vector<int> vector_b){

    vector<int> out_vector;

    while (vector_a.size() > 0 && vector_b.size() > 0){
        if (vector_a[0] > vector_b[0]){
            out_vector.push_back(vector_a[0]);
            vector_a.erase(vector_a.begin());
        }
        else{
            out_vector.push_back(vector_b[0]);
            vector_b.erase(vector_b.begin());
        }
    }
    while (vector_a.size() > 0){
        out_vector.push_back(vector_a[0]);
        vector_a.erase(vector_a.begin());
    }
    while (vector_b.size() > 0){
        out_vector.push_back(vector_b[0]);
        vector_b.erase(vector_b.begin());
    }
    return out_vector;
}

// Pulls a single line of data from the passed in sheet name
vector<vector<int>> pull_line_int_array(string sheet_name) {

    vector<int> out_data;
    string this_line;
    ifstream file_name;
    file_name.open(sheet_name);
    int index = 0;
    vector<vector<int>> data;

    while(getline(file_name, this_line)) {
        stringstream read_line(this_line);
        int number;
        while(read_line >> number){
            out_data.push_back(number);
        }
        while(out_data.size() > 0){
            index = out_data.size() - 1;
            out_data.erase(out_data.begin());
            vector<int> temp_array;
            for (int i = 0; i < index; i++){
                temp_array.push_back(out_data[i]);
            }
            out_data.erase(out_data.begin(), out_data.begin() + index);
            data.push_back(temp_array);
            index = 0;
        }
    }
    return data;
}

// simple function to print out the values in an array - mostly for debugging
void print_data(vector<int> array_data){

    for (int num : array_data){
        std::cout << num << " ";
    }
    std::cout << "\n";
}

// writes to a file
void write_output(string file_name, vector<int> array_data){


}