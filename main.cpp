// The program made in modern C++
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Function to split the string into tokens based on the CSV standard
std::vector<std::string> split(std::string str, char sep) {
    std::vector<std::string> tokens;
    std::string tok;
    bool inside_quotas = false;
    int i, n = str.size();
    for (i = 0; i < n; i++) {
        if (str[i] == '\"') {
            if (str[i + 1] == '\"') {
                tok.push_back('\"');
            } else {
                inside_quotas = !inside_quotas;
            }
        }
        if (str[i] == sep && !inside_quotas) {
            tokens.push_back(tok);
            tok.clear();
        } else {
            tok.push_back(str[i]);
        }
    }
    tokens.push_back(tok);
    tok.clear();
    return tokens;
}

// Data structure for the CSV
struct CSVDataFrame {
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> header;
    bool has_header;
    int rows, cols;

    CSVDataFrame(const char *path, bool head = true) {
        std::ifstream fin(path);
        std::string row;
        has_header = head;
        std::getline(fin, row);
        if (head) {
            header = split(row, ',');
            cols = header.size();
            rows = 0;
        } else {
            data.push_back(split(row, ','));
            cols = data[0].size();
            rows = 1;
        }
        while (std::getline(fin, row)) {
            std::vector<std::string> record = split(row, ',');
            data.push_back(record);
            rows++;
        }       
    }

    void print() {
        if (has_header) {
            for (std::string field : header) {
                std::cout << field << "\t";
            }
            std::cout << std::endl << "----------------" << std::endl;
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};


int main() {
    CSVDataFrame frame("example.csv");
    frame.print();
    return 0;
}