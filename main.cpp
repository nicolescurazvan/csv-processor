// The program made in modern C++
#include "csvdataframe.hpp"

int main() {
    CSVDataFrame frame("example.csv");
    frame.print();
    std::cout << frame.get(9, "model") << std::endl;
    frame.add_column(5, "Review");
    frame.change(0, "Review", "3.5");
    frame.change(1, "Review", "4.2");
    frame.change(2, "Review", "4.1");
    frame.change(3, "Review", "2.1");
    frame.print();
    std::cout << std::endl;
    frame.delete_column("Review");
    frame.print();
    std::cout << std::endl;

    CSVDataFrame filtered(frame);
    filtered.filter("Brand", [](std::string s) -> bool {
        return (s == "Renault" || s == "Dacia" || s[0] == 'V');
    });
    filtered.print();
    std::cout << std::endl;
    filtered.filter(4, [](std::string s) -> bool {
        std::string t = s.substr(1, s.size() - 1);
        return (std::stoi(t) > 30000);
    });
    filtered.print();
    return 0;
}