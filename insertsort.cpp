#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;

void print_data(vector<int> array_data);
vector<int> insertion_sort(vector<int> array_data);
vector<vector<int>> pull_line_int_array(string sheet_name);

// The main function of the program. Where we handle uploading the txt doc.
int main(){

    vector<vector<int>> in_array = pull_line_int_array("data.txt");

    ofstream out_file;
    out_file.open("insertout.txt");

    for(int i = 0; i < in_array.size(); i++){
        print_data(in_array[i]);

        auto start_time = std::chrono::system_clock::now();
        in_array[i] = insertion_sort(in_array[i]);
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

// Insertion sort algorithm, tracks time it takes to complete the operation
vector<int> insertion_sort(vector<int> array_data){

    for (int i = 1; i < array_data.size(); i++){
        int key = array_data[i];
        int index = i - 1;
        while (index >= 0 && array_data[index] < key){
            array_data[index + 1] = array_data[index];
            index --;
        }
        array_data[index + 1] = key;
    }

    return array_data;
}

// simple function to print out the values in an array - mostly for debugging
void print_data(vector<int> array_data){

    for (int num : array_data){
        std::cout << num << " ";
    }
    std::cout << "\n";
}