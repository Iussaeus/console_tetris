module;

#include <format>
#include <iostream>
#include <string>

export module utils;

namespace print {
    template <typename T>
    void print_single(T t) {
        std::cout << t;
    }

    template <typename T>
    void print_single_space(T t) {
        std::cout << t << " ";
    }

    export template <typename... Args>
    void space(Args... args) {
        ((print_single_space(args)), ...);
        std::cout << "\n";
    }

    export template <typename... Args>
    void line(Args... args) {
        ((print_single(args)), ...);
        std::cout << "\n";
    }
}

namespace assert {
    void print_file_data(int line = 0, const std::string& function = "", const std::string& file = "");
    export void condition(bool cond, const std::string& msg, int line = 0, const std::string& function = "",
                          const std::string& file = "");
}
