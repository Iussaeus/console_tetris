module;

#include <format>
#include <iostream>
#include <string>

export module utils;

namespace print {
    template <typename T>
    void print_single(T t) {
        std::wcout << t;
    }

    template <typename T>
    void print_single_space(T t) {
        std::wcout << t << " ";
    }

    export template <typename... Args>
    void space(Args... args) {
        ((print_single_space(args)), ...);
        std::wcout << "\n";
        std::flush(std::wcout);
    }

    export template <typename... Args>
    void line(Args... args) {
        ((print_single(args)), ...);
        std::wcout << "\n";
        std::flush(std::wcout);
    }

    export template <typename... Args>
    void format(std::format_string<Args...> fmt, Args... args) {
        print_single(std::format(fmt, std::forward<Args>(args)...));
    }
}

namespace assert {
    void print_file_data(int line = 0, const std::string& function = "", const std::string& file = "");
    export void condition(bool cond, const std::string& msg, int line = 0, const std::string& function = "",
                          const std::string& file = "");
}
