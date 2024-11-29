module;

#include <iostream>
#include <string>

export module assert;

export namespace assert {
    void print_file_data(int line = 0, const std::string& function = "", const std::string& file = "");

    template <typename T>
    void equal(T wanted, T got, int line, const std::string& function, const std::string& file) {
        if (wanted != got) {
            std::cout << "assertion failed: " << "expected: " << wanted << " got: " << got << std::endl;
            print_file_data(line, function, file);
            std::exit(1);
        }
    }

    template <typename T>
    void not_equal(T wanted, T got, const int line, const std::string& function, const std::string& file) {
        if (wanted == got) {
            std::cout << "assertion failed: " << "expected: " << wanted << " got: " << got << std::endl;
            print_file_data(line, function, file);
            std::exit(1);
        }
    }
}
