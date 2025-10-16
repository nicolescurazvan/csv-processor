#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Function to split the string into tokens based on the CSV standard
std::vector<std::string> split(std::string str) {
    std::vector<std::string> tokens;
    std::string tok;
    bool inside_quotas = false;
    int i = 0, n = str.size();
    while (i < n) {
        if (str[i] == '\"' && !inside_quotas) {
            inside_quotas = true;
            i++;
        }
        else if (str[i] == '\"' && inside_quotas && str[i + 1] == '\"') {
            tok.push_back('\"');
            i += 2;
        }
        else if (str[i] == '\"' && inside_quotas) {
            inside_quotas = false;
            i++;        
        }
        else if (str[i] == ',' && !inside_quotas) {
            tokens.push_back(tok);
            tok.clear();
            i++;
        } 
        else {
            tok.push_back(str[i]);
            i++;
        }
    }
    tokens.push_back(tok);
    return tokens;
}

// Data structure for the CSV
struct CSVDataFrame {
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> header;
    bool has_header;
    int rows, cols;

    // Constructor
    CSVDataFrame(const char *path, bool head = true) {
        std::ifstream fin(path);
        std::string row;
        has_header = head;
        std::getline(fin, row);
        if (head) {
            header = split(row);
            cols = header.size();
            rows = 0;
        } else {
            data.push_back(split(row));
            cols = data[0].size();
            rows = 1;
        }
        while (std::getline(fin, row)) {
            std::vector<std::string> record = split(row);
            data.push_back(record);
            rows++;
        }
        fin.close();       
    }

    CSVDataFrame(CSVDataFrame &frm) {
        rows = frm.rows;
        cols = frm.cols;
        has_header = frm.has_header;
        if (has_header) {
            header = std::vector<std::string>(cols);
            for (int i = 0; i < cols; i++) {
                header[i] = frm.header[i];
            }
        }
        data = std::vector<std::vector<std::string>>(rows);
        for (int i = 0; i < rows; i++) {
            data[i] = std::vector<std::string>(cols);
            for (int j = 0; j < cols; j++) {
                data[i][j] = frm.data[i][j];
            }
        }
    }

    // Print. Debug function
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

    // Get function
    std::string get(int row, int col) {
        return data[row][col];
    }
    
    std::string get(int row, std::string col) {
        int i = 0;
        while (header[i] != col) {
            i++;
        }
        return data[row][i];
    }

    // Change field
    void change(int row, std::string col, std::string value) {
        int i = 0;
        while (header[i] != col) {
            i++;
        }
        data[row][i] = value;
    }

    void change(int row, int col, std::string value) {
        data[row][col] = value;
    }

    // Add record
    void add_record() {
        std::vector<std::string> record(cols);
        data.push_back(record);
        rows++;
    }

    void add_record(int pos) {
        std::vector<std::string> record(cols);
        data.insert(data.begin() + pos, record);
        rows++;
    }

    // Delete record
    void delete_record(int pos) {
        data.erase(data.begin() + pos);
        rows--;
    }

    // Add column
    void add_column(int pos, std::string name) {
        header.emplace(header.begin() + pos, name);
        cols++;
        for (int i = 0; i < rows; i++) {
            data[i].emplace(data[i].begin() + pos, "");
        }
    }

    // Delete column
    void delete_column(std::string name) {
        int i = 0;
        while (header[i] != name) {
            i++;
        }
        header.erase(header.begin() + i);
        cols--;
        for (int j = 0; j < rows; j++) {
            data[j].erase(data[j].begin() + i);
        }
    }

    // Filter
    void filter(int col, bool (*predicate)(std::string)) {
        std::vector<std::vector<std::string>> new_data;
        int new_rows = 0;
        for (int i = 0; i < rows; i++) {
            if (predicate(data[i][col])) {
                new_data.push_back(data[i]);
                new_rows++;
            }
        }
        data = new_data;
        rows = new_rows;
    }

    void filter(std::string name, bool(*predicate)(std::string)) {
        int col = 0;
        while (header[col] != name) {
            col++;
        }
        std::vector<std::vector<std::string>> new_data;
        int new_rows = 0;
        for (int i = 0; i < rows; i++) {
            if (predicate(data[i][col])) {
                new_data.push_back(data[i]);
                new_rows++;
            }
        }
        data = new_data;
        rows = new_rows;
    }

};